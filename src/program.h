#ifndef VM01_PROGRAM_H
#define VM01_PROGRAM_H

#include "common.h"
#include "byteArray.h"
#include "instInfo.h"

#define END_OF_CODE(program, offset) \
    ((offset) >= (program)->code.length)

typedef enum {
    OP_NOP = 0x00,
    // 0x01 - 0x07
    // 0x08 - 0x0F
    OP_ADD = 0x10,
    OP_SUB = 0x11,
    OP_MUL = 0x12,
    OP_DIV = 0x13,
    OP_REM = 0x14,
    // 0x15 - 0x17
    OP_STORE = 0x18,
    OP_STORE_Z = 0x19,
    // 0x1A - 0x1F
    OP_CALL = 0x20,
    // 0x21 - 0x27
    OP_RETURN = 0x28,
    OP_RETURN_I = 0x29,
    // 0x2A - 0x2F
    OP_SYSCALL = 0x30,
    // 0x31 - 0x38
} OpCode;

// size limit 64
typedef struct {
    uint32_t constantOffset;
    uint32_t metadataOffset;
    uint32_t programOffset;
} ProgramHeader;

typedef struct {
    ProgramHeader header;
    ByteArray code;
    ByteArray constantPool;
    ByteArray metadata;
} Program;

void Program_init(Program *program);
void Program_free(Program *program);
bool Program_load(Program *program, ByteArray *src);

#endif
