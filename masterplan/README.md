# Agri3D System Master Plan & Architecture Guide

Welcome to the **Agri3D Cartesian Gantry System (Mark 2)** master plan repository. This directory serves as the documentation and design hub for the entire project.

> Last updated: July 2026 — Joshua & Kent, AGRI_3D Mark 2

---

## 1. System Topology

The system is split into three decoupled tiers:

```mermaid
graph TD
    subgraph Client [Client Tier]
        F[Flutter Application]
    end
    subgraph Master [Master Tier]
        E[ESP32-S3 AI Master]
    end
    subgraph Motion [Motion Tier]
        N[Arduino Nano Slave]
    end

    F <--> |MessagePack over WebSockets| E
    E <--> |ASCII G-Code and Telemetry over UART| N
```

---

## 2. Project Directory Structure

```text
AGRI_3D-App_Mark2/
├── masterplan/                 # High-level architecture, design specifications, and guides
│   └── README.md               # This file
│
├── communication/              # MessagePack contract schema and compilation tools
│   ├── protocol_schema.json    # The human-readable communication schema (source of truth)
│   └── sync_contracts.py       # Code generator: C++ structs + Dart model classes
│
├── AI-Agri3D/                  # ESP32-S3 Master controller firmware (FreeRTOS/PlatformIO)
│   └── lib/
│       ├── agri3d_ai/          # Edge Impulse FOMO crop-weed detection
│       ├── agri3d_fuzzy/       # Mamdani Fuzzy dosing logic
│       └── xgboost_model/      # Compiled XGBoost regression model
│
├── GRBL-AGRI3D/                # Arduino Nano motion controller firmware (GRBL Fork)
│   └── src/
│       ├── machine_config.h    # Single source of truth for all GRBL $ settings
│       ├── tmc_config.c        # TMC2209 UART-mode driver configuration
│       ├── tmc_report.c        # Custom telemetry injector (|TMC:...|RELAYS:...)
│       └── relays.c            # M100-M107 relay/actuator M-code handlers
│
└── agri3d_flutter/             # Cross-platform Flutter user interface application
    ├── lib/
    │   ├── models/             # Generated from sync_contracts.py -- DO NOT hand-edit
    │   ├── providers/          # Riverpod state providers
    │   └── screens/            # UI screens
    └── pubspec.yaml
```

---

## 3. State-Centric Architecture & State Blockers

Both the Master (ESP32-S3) and the Slave (Arduino Nano) are designed as **State-Centric State Machines** to ensure safety, predictable behavior, and clean recovery paths. Every subsystem has an explicit **blocker table** — a contract of what is allowed and what is rejected in each state.

---

### A. Arduino Nano (Motion Engine) States

The Nano operates standard GRBL states: `IDLE`, `RUN`, `HOLD`, `JOG`, `HOME`, `ALARM`.

```mermaid
stateDiagram-v2
    [*] --> IDLE : Boot + Homing Complete
    IDLE --> RUN : G-code move command
    IDLE --> JOG : Jog command
    IDLE --> HOME : Homing cycle ($H)
    RUN --> HOLD : Feed Hold (!)
    RUN --> ALARM : Limit / StallGuard trigger
    JOG --> IDLE : Jog cancel
    HOLD --> RUN : Cycle Start (~)
    HOLD --> IDLE : Reset
    HOME --> IDLE : Homing success
    HOME --> ALARM : Limit not found / stall
    ALARM --> IDLE : Unlock ($X) + Home ($H)
```

#### Nano State Blocker Table

If a command arrives outside its allowed states, the Nano must **log a warning** and **silently discard** it. Never partially execute a blocked command.

| State    | Move Commands | M100-M105 Relays  | M106/M107 Head State | Status Poll (?) |
|----------|--------------|-------------------|-----------------------|-----------------|
| `IDLE`   | YES          | YES               | YES                   | YES             |
| `RUN`    | YES          | **BLOCKED**       | YES                   | YES             |
| `HOLD`   | Queued       | YES               | YES                   | YES             |
| `JOG`    | YES          | **BLOCKED**       | YES                   | YES             |
| `HOME`   | **BLOCKED**  | **BLOCKED**       | **BLOCKED**           | YES             |
| `ALARM`  | **BLOCKED**  | **BLOCKED**       | **BLOCKED**           | YES             |

> **ALARM Rule**: On entering `ALARM`, the Nano must atomically: (1) stop all motion, (2) force all relay pins LOW (OFF), (3) set `head_is_down = true` (conservative assumption), and (4) send an alarm report over serial.

---

### B. ESP32-S3 (Orchestration Engine) States

```mermaid
stateDiagram-v2
    [*] --> IDLE

    IDLE --> HOMING : Start Homing
    HOMING --> IDLE : Homing Complete / Success
    HOMING --> ALARM_RECOVERY : Limit Triggered / Stall

    IDLE --> SCANNING : Trigger Scan
    SCANNING --> IDLE : Scan Complete
    SCANNING --> RAIN_PAUSED : Rain Detected
    SCANNING --> ALARM_RECOVERY : Hardware Error / Stall

    IDLE --> AUTONOMOUS : Start Routine
    AUTONOMOUS --> IDLE : Routine Complete
    AUTONOMOUS --> RAIN_PAUSED : Rain Detected
    AUTONOMOUS --> ALARM_RECOVERY : Hardware Error / Stall

    RAIN_PAUSED --> AUTONOMOUS : Rain Cleared
    RAIN_PAUSED --> IDLE : Aborted by User

    ALARM_RECOVERY --> IDLE : UNLOCK + HOME confirmed
```

#### ESP32 Operation State Blocker Table

The ESP32 checks its own `OperationState` **before** forwarding any command to the Nano. If blocked, it replies to Flutter with a `CMD_REJECTED` MessagePack message including a reason code — **never silently discard operator commands**.

| State              | Send G-Code to Nano   | Trigger Relays     | WebSocket Commands      | Start AI Scan   | Start Routine   | Camera Stream |
|--------------------|----------------------|--------------------|--------------------------|----------------|----------------|---------------|
| `IDLE`             | YES                  | YES                | YES (all)               | YES            | YES            | YES           |
| `HOMING`           | YES (homing only)    | **BLOCKED**        | YES (status only)       | **BLOCKED**    | **BLOCKED**    | YES           |
| `SCANNING`         | YES (scan moves)     | **BLOCKED**        | YES (status + abort)    | Already running| **BLOCKED**    | YES           |
| `AUTONOMOUS`       | YES (routine only)   | YES (routine steps)| YES (status + abort)    | **BLOCKED**    | Already running| YES           |
| `RAIN_PAUSED`      | **BLOCKED**          | **BLOCKED**        | YES (status + abort)    | **BLOCKED**    | **BLOCKED**    | YES           |
| `ALARM_RECOVERY`   | **BLOCKED**          | **BLOCKED**        | YES (status + unlock)   | **BLOCKED**    | **BLOCKED**    | **BLOCKED**   |

---

### C. Flutter App Connection States

Flutter must maintain its own connection state machine. The UI reflects the **real** connection state — never assume connectivity.

#### Flutter Connection State Blocker Table

| State          | Show Controls     | Send Commands     | Show Live Data    | Auto-Reconnect |
|----------------|-------------------|-------------------|-------------------|----------------|
| `Disconnected` | Hidden            | **BLOCKED**       | Hidden            | YES (searching)|
| `Connecting`   | Hidden            | **BLOCKED**       | Hidden            | —              |
| `Connected`    | YES               | YES               | YES               | —              |
| `Reconnecting` | YES (greyed out)  | Queued locally    | Stale data shown  | YES (active)   |

> **Anti-Ghost Rule**: If Flutter receives no `STATE_UPDATE` or telemetry for **5 seconds**, it must automatically transition to `Reconnecting`, close the stale socket, and restart mDNS/UDP discovery. Never leave a zombie connection open.

> **Debounce Rule**: All motion buttons must be debounced with a minimum 300ms cooldown after any tap to prevent duplicate command flooding.

---

### D. Master Safety Rules

1. **Rain Gating**: Rain sensor or weather API precipitation triggers immediate `Feed Hold` to Nano, raises NPK probe, enters `RAIN_PAUSED`.
2. **Watchdog Check**: Nano not responding for 4+ poll cycles (50ms in motion, 250ms idle) triggers `ALARM_RECOVERY` and halts all automated tasks.
3. **Client Disconnection**: WebSocket link broken disables live camera stream and pauses non-autonomous tasks.
4. **Singleton WebSocket**: All secondary connection attempts are rejected immediately with a `SINGLE_CLIENT_ONLY` binary payload.
5. **Ping-Pong Watchdog**: 2-second ping interval. 10 consecutive failed pongs forces socket close and resets all state variables to idle defaults.
6. **Serial Flush**: UART RX/TX buffers are flushed on Nano connect AND alarm recovery to clear ghost commands.

---

## 4. Z-Axis Ground Interlock (Plant Safety Critical)

> **Mark 1 Problem**: No software lock prevented XY movement when the head was near ground level. A mis-timed XY jog dragged the nozzle across the soil and damaged plants.

### Three-Layer Ground Interlock

#### Layer 1 -- GRBL Firmware (`motion_control.c`)

Inject into `mc_line()` before executing any move:

```c
// Time Complexity: O(1) -- single position comparison
// Space Complexity: O(1) -- no allocations
if (agri3d_is_xy_move(target)) {
    if (sys_position[Z_AXIS] < (Z_SAFE_TRAVEL_MM * settings.steps_per_mm[Z_AXIS])
        || agri3d_head_is_down()) {
        system_set_exec_alarm(EXEC_ALARM_HARD_LIMIT);
        report_feedback_message(MESSAGE_PROGRAM_END);
        return; // DROP the move entirely
    }
}
```

#### Layer 2 -- Custom M-Codes `M106` / `M107`

| M-Code | Meaning           | Effect                                     |
|--------|-------------------|--------------------------------------------|
| `M106` | Head **raised**   | Clears interlock latch -- XY now permitted |
| `M107` | Head **lowered**  | Sets interlock latch -- XY now BLOCKED     |

> **Boot Default**: `head_is_down = true` on power-on. XY moves are BLOCKED until homing completes and the ESP32 explicitly issues `M106`.

#### Layer 3 -- ESP32 Master Sequence

```
CORRECT sequence:
  G91 G0 Z5         (Raise head above safe height)
  M106              (Declare head raised)
  G90 G0 X100 Y50   (XY travel -- now allowed)
  G91 G0 Z-5       (Lower head to work position)
  M107              (Declare head down)

WRONG (Mark 1 pattern):
  G0 X100 Y50       (XY move with Z unknown -- plant drag risk)
```

---

## 5. Canonical Machine Configuration (`machine_config.h`)

All GRBL `$` settings live in **one file**: `GRBL-AGRI3D/src/machine_config.h`. Never hardcode machine parameters anywhere else.

Key constants defined here:
- Steps/mm per axis (`$100`-`$102`)
- Max feed rates (`$110`-`$112`)
- Acceleration (`$120`-`$122`)
- Travel limits (`$130`-`$132`)
- `DIR_INVERT_MASK` -- which motors are wired backwards
- `LIMIT_PINS_INVERT` -- always 0 (use NC switches only)
- `HOMING_DIR_INVERT` -- Z homes upward on our machine
- `Z_SAFE_TRAVEL_MM` -- ground interlock threshold
- `AGRI3D_CONFIG_VERSION` -- bump this when hardware changes

On boot, firmware checks the stored config version byte in EEPROM. If it doesn't match `AGRI3D_CONFIG_VERSION`, all settings are re-written automatically. **No more lost configs after reflashing.**

> **NC Switch Rule**: ALWAYS use Normally Closed (NC) limit switches. A broken wire on NC looks triggered -- machine stops. A broken wire on NO looks untriggered -- machine drives into the frame.

---

## 6. Communication Architecture

### A. ESP32-S3 to Flutter (MessagePack over WebSocket)

- **Protocol**: MessagePack frames with integer keys (`{0: wifiState, 1: x}`)
- **Schema**: `communication/protocol_schema.json` is the single source of truth
- **Code Gen**: Run `sync_contracts.py` to regenerate C++ and Dart contracts -- never hand-write protocol classes
- **CRC16**: Every frame carries a Modbus CRC16 checksum. Mismatched frames are dropped immediately
- **Debug Mode**: `#define DEBUG_MSGPACK` on the ESP32 pretty-prints all payloads to the Serial console

#### MessagePack Key Registry

| Key | Field            | Type   | Notes                         |
|-----|------------------|--------|-------------------------------|
| `0` | `wifiState`      | uint8  | 0=Disconnected, 1=AP, 2=STA   |
| `1` | `operationState` | uint8  | ESP32 OperationState enum     |
| `2` | `nanoState`      | uint8  | Maps to GRBL state            |
| `3` | `mpos_x`         | float  | Machine X position (mm)       |
| `4` | `mpos_y`         | float  | Machine Y position (mm)       |
| `5` | `mpos_z`         | float  | Machine Z position (mm)       |
| `10`| `SCAN_START`     | uint8  | ESP32 to Flutter notification |
| `11`| `SCAN_COMPLETE`  | uint8  | Includes bounding box array   |
| `12`| `UPLOAD_SCAN_START`| uint8| Flutter triggers cloud upload |
| `20`| `DOSING_COMMAND` | uint8  | Fuzzy output to relay command |

### B. ESP32-S3 to Arduino Nano (ASCII G-Code over UART)

- **Baud Rate**: 115200
- **Extended Status Format**: `<State|MPos:x,y,z|TMC:a,b,c,d|RELAYS:r1,r2>`
- **Flow Control**: Atomic command-response -- wait for `ok` or `error:N` before sending next command

---

## 7. Code Quality Rules (Mandatory for All Files)

### Big-O Documentation
Every function, class, or script must include in its header comment:
```c
// Time Complexity:  O(n) -- iterates over all relay channels
// Space Complexity: O(1) -- no heap allocation
```

### Naming Conventions

| Layer         | Convention       | Example                    |
|---------------|------------------|----------------------------|
| C/C++ functions | `snake_case`   | `tmc_get_stall_status()`   |
| Dart classes  | `PascalCase`     | `MotionStatusMessage`      |
| Dart variables| `camelCase`      | `wifiState`                |
| MessagePack keys | Integer constants | `const int KEY_WIFI_STATE = 0` |
| FreeRTOS tasks | `UPPER_SNAKE_CASE` | `TASK_SERIAL_HANDLER`   |

### No Magic Numbers
```c
// BAD
if (sys.state == 3) { ... }

// GOOD
if (sys.state == STATE_IDLE) { ... }
```

---

## 8. Development Workflow

1. **Define protocol changes in `protocol_schema.json` first** -- before writing any code
2. **Run `sync_contracts.py`** to regenerate C++ and Dart contracts
3. **Implement firmware** (ESP32 / Nano) against the generated headers
4. **Implement Flutter UI** against the generated Dart models
5. **Test communication** with a local WebSocket mock before touching hardware
6. **Document Big-O** before merging any PR

---

## 9. Priority Checklist

| Priority   | Task                                                                  |
|------------|-----------------------------------------------------------------------|
| CRITICAL   | Switch to MessagePack + CRC16                                        |
| CRITICAL   | Singleton WebSocket + ping watchdog                                  |
| CRITICAL   | Nano relay state guards (IDLE/HOLD only)                             |
| CRITICAL   | Z-axis ground interlock in `mc_line()`                               |
| CRITICAL   | Boot default: `head_is_down = true` until homing                    |
| CRITICAL   | ESP32 operation state blocker table enforced                         |
| CRITICAL   | Flutter connection state machine (no zombie sockets)                 |
| HIGH       | `machine_config.h` single source of truth                           |
| HIGH       | Auto-write EEPROM on boot with version check                        |
| HIGH       | NC limit switches only -- rewire any NO switches                    |
| HIGH       | Direction flag commissioning checklist (do once, document)          |
| HIGH       | FreeRTOS task isolation on ESP32                                     |
| HIGH       | Serial flush on connect/alarm                                        |
| HIGH       | Riverpod state management in Flutter                                 |
| MEDIUM     | Modularize AI subsystem headers (ai, fuzzy, xgboost)                |
| MEDIUM     | Delete A4988 legacy configs                                          |
| MEDIUM     | `CMD_REJECTED` MessagePack error responses from ESP32               |
| LOW        | Big-O documentation sweep                                            |
| LOW        | Flutter outdoor UI polish (dark mode, 56dp touch targets)           |

