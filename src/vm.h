#ifndef VM01_VM_H
#define VM01_VM_H

#include "common.h"
#include "program.h"

#define STACK_SIZE 256

typedef struct {
    Program *program;
    uint8_t stack[STACK_SIZE];

    // registers
    uint8_t *pc;
    uint8_t *sp;
} VM;

typedef enum {
    EXEC_RESULT_OK,
    EXEC_RESULT_ERROR,
} ExecResult;

void VM_init();
void VM_free();
ExecResult VM_exec(Program *program);

#endif
