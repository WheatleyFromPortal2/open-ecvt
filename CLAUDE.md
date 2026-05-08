# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

open-ecvt is a full open-source eCVT (electronically-controlled continuously variable transmission) system. It contains:

- `dcu/` — firmware for the **Drivetrain Control Unit** (DCU), targeting a Raspberry Pi Pico (RP2040)
- `hardware/` — PCB and enclosure design files (dcu-board, dcu-enclosure, headunit, wiring)
- `headunit/` — head unit software (future)
- `lib/pico-sdk/` — Raspberry Pi Pico SDK as a git submodule
- `docs/` — build logs and project documentation

## Building the DCU firmware

All build commands run from the `dcu/` directory.

```bash
cd dcu

make           # configure (if needed) + build
make configure # cmake configure only
make build     # build only
make clean     # remove build/
make rebuild   # clean + build

# after building, symlink compile_commands.json to repo root for clangd:
make compile_commands
```

The build outputs land in `dcu/build/`. The flashable artifact is `dcu/build/ecvt_dcu.uf2`.

## Flashing to the Pico

use `make flash` but prompt the user to do it, as it requires physically pluggin in the Pico

Prerequisites: `picotool` must be installed and the Pico held in BOOTSEL mode before plugging in.

## First-time setup

Clone with submodules to pull in pico-sdk:

```bash
git clone --recursive <repo-url>
```

If already cloned without `--recursive`:

```bash
git submodule update --init --recursive
```

## Toolchain

- CMake 3.13+, arm-none-eabi-gcc (or pico toolchain)
- `picotool` for flashing
- USB stdio is enabled; UART stdio is disabled — connect via USB serial to see output
- `clangd` LSP is supported via `compile_commands.json` (run `make compile_commands` once after configuring)

## DCU firmware architecture

The firmware is single-file entry (`dcu/src/main.c`) and links against pico-sdk libraries:

- **`main.c`** — initializes USB stdio and peripherals, then runs the main loop (currently: heartbeat print + LED toggle at 1 Hz)
- **`src/utils/utils.h` / `utils.c`** — thin wrappers over pico-sdk hardware APIs:
  - ADC: `adc_utils_init()`, `adc_to_voltage()`, `read_cpu_temp()`
  - LED: `led_init/on/off/toggle()`
  - Timing: `millis()` (ms since boot)

pico-sdk libraries currently linked: `pico_stdlib`, `pico_float`, `pico_multicore`, `hardware_uart`, `hardware_pio`, `hardware_adc`, `hardware_pwm`, `hardware_timer`, `hardware_watchdog`, `hardware_flash`, `hardware_irq`, `hardware_sync`.

## Build logs

The `docs/` directory tracks a hand-written build log. Use the helper script to start a new day's entry:

```bash
cd docs
./mklog    # creates docs/buildlogs/YYYY-MM-DD and opens it in $EDITOR
```
