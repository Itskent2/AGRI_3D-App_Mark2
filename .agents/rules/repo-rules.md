---
trigger: always_on
description: Repository rules and coding guidelines for Agri3D Cartesian Gantry System Mark 2
---

# Agri3D Project Rules & Coding Guidelines

These rules are enforced on all code modifications, refactorings, and design decisions within the Agri3D project.

---

## 1. Algorithmic Complexity Documentation Rule
For **every** function, class, or script written, modified, or refactored, you MUST explicitly document and explain the **Time Complexity** and **Space Complexity** in Big-O notation ($O(N)$) in the function's header comment.
*   **Time Complexity**: Describe the worst-case execution time as a function of input size (e.g. $O(N)$ for linear sweeps, $O(N \log N)$ for sorting).
*   **Space Complexity**: Describe the auxiliary memory allocation (excluding inputs) as a function of input size (e.g. $O(1)$ for in-place buffers, $O(N)$ for heap-allocated message queues).

---

## 2. Strict Statefulness & Anti-Ghosting Rules

To eliminate ghost WebSocket connections, phantom serial commands, and unpredictable gantry behaviors, all subsystems must implement state-centric communication.

### A. ESP32 ↔ Flutter WebSocket Integrity
1.  **Singleton Connection Policy**: The ESP32-S3 WebSocket server must strictly allow only **one** client connection at a time.
    *   If a new client attempts to connect while an active client exists, the server must explicitly reject the new connection with a binary `SINGLE_CLIENT_ONLY` payload and immediately close the socket.
    *   On client disconnect, all active operations (e.g., JPEG streaming, active scans) must be atomically cancelled, and variables reset to their default idle values.
2.  **Ping-Pong Watchdog**:
    *   A ping loop must run every 2 seconds.
    *   If a client misses 10 consecutive pongs, the ESP32 must assume a ghost connection has occurred, forcefully close the socket, and clean up the active client state.

### B. ESP32 ↔ Arduino Nano Serial (G-Code) Flow Control
1.  **Atomic Command-Response**: The ESP32 must never send a G-code command if another command is currently executing. It must wait for the Nano to respond with `ok` or `error:N` (or a timeout).
2.  **Clear Rx Buffer on Reset**: When reconnecting to the Nano or recovering from an alarm state, the ESP32 must flush the UART RX/TX ring buffers to clear residual bytes and prevent executing ghost commands left in the buffer.
3.  **Nano State Locks**:
    *   The Nano must reject any relay or actuator commands (e.g. `M100`-`M105`) if the current motion state is not `IDLE` or `HOLD`.
    *   On entering `ALARM` state, the Nano must immediately force all tool relays open (OFF) and ignore further movement G-codes until an explicit unlock (`$X`) or homing (`$H`) command is received.

### C. Flutter App Telemetry Synchronization
1.  **Connection Watchdog**: The Flutter app must run a local timer. If it does not receive a `STATE_UPDATE` or telemetry packet for 5 seconds, it must transition the UI to "Disconnected", close its WebSocket channel, and trigger mDNS/UDP auto-discovery to prevent phantom connection states.
2.  **Outbox Queueing**: Flutter must queue outbound commands and serializes them in order. Duplicate commands (e.g. double-tapping a button) must be debounced at the UI level.

---

## 3. Data Integrity & Verification
*   **CRC16 Checksums**: Every MessagePack payload sent between ESP32 and Flutter must contain a Modbus CRC16 checksum in the header. If the calculated checksum does not match, the packet must be dropped immediately without processing to avoid "ghost" instructions caused by transmission corruption.
*   **NVS Dimension Checks**: Gantry coordinates received from status polls must be validated against the soft limits cached in NVS. If coordinates exceed limits, trigger an immediate emergency halt.

## 4. READ THE MASTERPLAN ALWAYS
