#ifndef VM01_PROGRAM_H
#define VM01_PROGRAM_H

#include "common.h"
#include "byteArray.h"
#include "instInfo.h"

#define END_OF_SECTION(program, offset) \
    ((offset) >= (program)->code.length)

typedef enum {
    OP_NOP = 0x00,
    OP_ADD = 0x10,
    OP_SUB = 0x11,
    OP_MUL = 0x12,
    OP_DIV = 0x13,
    OP_REM = 0x14,
    OP_STORE = 0x18,
    OP_STORE_Z = 0x19,
    OP_CALL = 0x1C,
    OP_RETURN = 0x20,
    OP_RETURN_I = 0x21,
    OP_SYSCALL = 0x24,
} OpCode;

typedef struct {
    ByteArray code;
    ByteArray constantPool;
    ByteArray metadata;
} Program;

void Program_init(Program *program);
void Program_free(Program *program);

#endif
