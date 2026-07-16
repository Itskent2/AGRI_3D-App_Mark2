# Agri3D Active Task List

## Instructions
- This file tracks the active development phases of the GRBL-AGRI3D rewrite.
- All tasks must follow the format:
  Phase x:
  1. Task
  1.1 Subtask
  1.1.1 Detail
- Once all tasks in a phase are complete, move the entire phase section to `task_archive.md`.

---

Phase 3: Clean Re-implementation of GRBL-AGRI3D
1. Initialize the new, clean Arduino Nano firmware under `GRBL-AGRI3D/`
   1.1 Import essential GRBL files (excluding door opening, parking, coolant/spindle if unnecessary)
   1.2 Define the clean `machine_config.h` as the single source of truth
2. Implement Core Safety & Motion Controls
   2.1 Implement Z-axis ground interlock in `mc_line()` (Layer 1 safety)
   2.2 Implement custom M-codes `M106`/`M107` (Layer 2 safety)
3. Implement TMC2209 Driver Configuration & Telemetry
   3.1 Port UART-mode configuration (`tmc_config.c`)
   3.2 Integrate TMC diagnostic report in status query responses
4. Implement Relay/Actuator Controls (M100-M105)
   4.1 Implement pin mapping and handlers for actuators
   4.2 Enforce state locks (reject relay commands in ALARM or during active motion)

Phase 4: Verification and Testing
1. Compile and Flash Nano Firmware
   1.1 Set up compilation using Arduino IDE / PlatformIO
   1.2 Resolve compiler errors and optimize memory usage (keep planner buffer size = 2)
2. Functional Verification
   2.1 Test status polling, state transitions, and gantry soft limits
   2.2 Validate hard limits, Z interlocks, and relay safety locks
