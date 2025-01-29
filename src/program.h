#ifndef VM01_PROGRAM_H
#define VM01_PROGRAM_H

#include "common.h"
#include "uint8Array.h"
#include "valueArray.h"
#include "instInfoArray.h"

#define END_OF_SECTION(program, offset) \
    ((offset) >= (program)->codeArray.length)

typedef enum {
    OP_NOP,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_REM,
    OP_STORE,
    OP_CALL,
    OP_RETURN,
    OP_RETURN_I,
    OP_SYSCALL,
} OpCode;

typedef struct {
    Uint8Array codeArray;
    ValueArray constantPool;
    InstInfoArray info;
} Program;

void Program_init(Program *program);
int Program_addByte(Program *program, uint8_t byte);
void Program_addInfo(Program *program, InstInfo *info);
int Program_addConstant(Program *program, Value value);
void Program_free(Program *program);

#endif
