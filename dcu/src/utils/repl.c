// dcu/src/utils/repl.c
#include "repl.h"
#include "pico/stdio.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// conservative input limits
#define LINE_MAX 64
#define ARGV_MAX 8
#define PROMPT   "DCU> " // shell-style prompt

static int read_line(char *buf, int max) {
    int len = 0;
    printf(PROMPT);
    stdio_flush();

    while (1) {
        int c = getchar();
        if (c == '\r' || c == '\n') { // user finished typing command
            putchar('\n');
            buf[len] = '\0';
            return len;
        }

        // backspace / DEL handling
        if ((c == '\b' || c == 0x7f) && len >0) {
            len--; // make our length shorter
            printf("\b \b");
            stdio_flush();
            continue; // skip to next loop iteration
        }

        // isprint() checks if character can be printed
        // if it is: we print the value and store it
        if (isprint(c) && len < max - 1) {
            buf[len++] = (char) c;
            putchar(c);
            fflush(stdout);
        }
    }
}

static int tokenize(char *line, char **argv, int max_argc) {
    int argc = 0;
    char *p = line; // p acts as our cursor so we can step through the string

    while (*p) {
        while (*p == ' ') p++; // skip spaces between words
        if (!*p) break; // if we hit the end of the string, we're done

        if (argc >= max_argc) break; // don't allow argv[] to overflow

        argv[argc++] = p; // record where the word starts
        
        while (*p && *p != ' ') p++; // advance past the word
        if (*p) *p++ = '\0'; // replace the space with '\0' and move on
    }
    return argc; // return the amount of arguments
}

// print all commands for reference
static void cmd_help(const repl_cmd_t *cmds, size_t n) {
    for (size_t i = 0; i < n; i++) { // loop through all commands
        // left align string to 12 char wide column
        printf(" %-12s %s\n", cmds[i].name, cmds[i].help);
    }
}

void repl_run(const repl_cmd_t *cmds, size_t n_cmds) {
    char line[LINE_MAX];  // our command buffer is the size of LINE_MAX
    char *argv[ARGV_MAX]; // our argv buffer is the size of ARGV_MAX
    
    while (1) {
        if (read_line(line, LINE_MAX) == 0) {
            continue;
        }

        int argc = tokenize(line, argv, ARGV_MAX);

        // check for help command
        if (strcmp(argv[0], "help") == 0) {
            cmd_help(cmds, n_cmds); // print help to user
            continue;
        }
        
        bool matched = 0;
        // check if user input matches a command
        for (size_t i = 0; i < n_cmds; i++) {
            if (strcmp(argv[0], cmds[i].name) == 0) {
                cmds[i].fn(argc, argv); // run the user's command
                matched = true;
                break;
            }
        }
        if (!matched) {
            printf("unknown command: %s (try 'help')\n", argv[0]);
        }
    }
}

