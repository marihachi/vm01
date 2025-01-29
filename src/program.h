#ifndef VM01_PROGRAM_H
#define VM01_PROGRAM_H

#include "common.h"
#include "uint8Array.h"
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
    Uint8Array constantPool;
    InstInfoArray info;
} Program;

void Program_init(Program *program);
uint16_t Program_addByte(Program *program, uint8_t value);
uint16_t Program_addBytes(Program *program, const uint8_t *value, int length);
void Program_addInfo(Program *program, InstInfo *info);
uint16_t Program_addConstant(Program *program, const uint8_t *value, int length);
void Program_free(Program *program);

#endif
