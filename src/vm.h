#ifndef VM01_VM_H
#define VM01_VM_H

#include "common.h"
#include "code.h"

typedef struct {
    Code *code;
    uint8_t *ip;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void VM_init();
void VM_free();
InterpretResult VM_interpret(Code *code);

#endif
