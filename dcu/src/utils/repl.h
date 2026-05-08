// dcu/utils/repl.h
#ifndef REPL_H
#define REPL_H

#include <stddef.h>

typedef void (*repl_cmd_fn_t)(int argc, char **argv);

typedef struct {
    const char       *name;
    const char       *help;
    repl_cmd_fn_t    fn;    // function pointer that we run when the command is issued
} repl_cmd_t;

// blocks forever, reading lines and then dispatching commands
void repl_run(const repl_cmd_t *cmds, size_t n_cmds);

#endif
