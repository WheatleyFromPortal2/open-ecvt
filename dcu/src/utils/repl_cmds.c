// dcu/utils/repl_cmds.c
#include "repl_cmds.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdio.h"

// get cpu temp
static void cmd_temp(int argc, char **argv) {
    printf("cpu temp: %d C\n", read_cpu_temp());
}

// get uptime in millis
static void cmd_uptime(int argc, char **argv) {
    printf("uptime: %u ms\n", millis());
}

// set LED value
static void cmd_led(int argc, char **argv) {
    // if the user didn't include an argument, print the value of LED
    if (argc < 2) {
        printf("led: %d\n", get_led());
        return;
    }
    // check argument to run command
    if      (strcmp(argv[1], "on")     == 0) led_on();
    else if (strcmp(argv[1], "off")    == 0) led_off();
    else if (strcmp(argv[1], "toggle") == 0) led_toggle();
    else printf("unknown: %s\n", argv[1]);
}

static void cmd_reboot(int argc, char **argv) {
    printf("rebooting...\n");
    stdio_flush();
    reboot();
}

static void cmd_bootsel(int argc, char **argv) {
    printf("entering BOOTSEL mode...\n");
    stdio_flush();
    bootsel();
}

// define our set of commands and their corresponding function
const repl_cmd_t cmds[] = {
    { "temp",    "read CPU temperature",       cmd_temp    },
    { "uptime",  "display ms since boot",      cmd_uptime  },
    { "led",     "led <on|off|toggle>",        cmd_led     },
    { "reboot",  "reboot the DCU",             cmd_reboot  },
    { "bootsel", "reboot into USB flash mode", cmd_bootsel },
};

// calculate length of commands list using total and element sizes
const size_t n_cmds = sizeof(cmds) / sizeof(cmds[0]);

