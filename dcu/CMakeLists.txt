# Pull in the SDK — path relative to this file
cmake_minimum_required(VERSION 3.13)

include(${CMAKE_CURRENT_LIST_DIR}/../lib/pico-sdk/pico_sdk_init.cmake)

project(ecvt_dcu C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

add_executable(ecvt_dcu
    src/main.c
    src/utils/utils.c
)

target_include_directories(ecvt_dcu PRIVATE
    src/
)

target_link_libraries(ecvt_dcu
    pico_stdlib
    pico_multicore
    hardware_uart
    hardware_pio
    hardware_adc
    hardware_pwm
    hardware_timer
    hardware_watchdog
    hardware_flash
    hardware_irq
    hardware_sync
)

pico_enable_stdio_usb(ecvt_dcu  1)
pico_enable_stdio_uart(ecvt_dcu 0)

pico_add_extra_outputs(ecvt_dcu)
