#ifndef VM01_PROGRAM_H
#define VM01_PROGRAM_H

#include "common.h"
#include "byteArray.h"

#define END_OF_CODE(program, offset) \
    ((offset) >= (program)->code.length)

typedef enum {
    OP_NOP = 0x00,      // operands: -
    // 0x01 - 0x07
    // 0x08 - 0x0F
    OP_ADD = 0x10,      // operands: -
    OP_SUB = 0x11,      // operands: -
    OP_MUL = 0x12,      // operands: -
    OP_DIV = 0x13,      // operands: -
    OP_REM = 0x14,      // operands: -
    // 0x15 - 0x17
    OP_STORE = 0x18,    // operands: constant offset(2 bytes)
    OP_STORE_Z = 0x19,  // operands: -
    // 0x1A - 0x1F
    OP_CALL = 0x20,
    // 0x21 - 0x27
    OP_RETURN = 0x28,   // operands: -
    OP_RETURN_I = 0x29,
    // 0x2A - 0x2F
    OP_SYSCALL = 0x30,  // operands: subcode (1 byte) + syscall args
    // 0x31 - 0x38
} OpCode;

// size limit 64
typedef struct {
    uint8_t magicCode[4];
    uint32_t constantOffset;
    uint32_t metadataOffset;
    uint32_t programOffset;
} ProgramHeader;

typedef struct {
    uint32_t addr;
    uint32_t line;
    uint32_t column;
} InstInfo;

typedef struct {
    ProgramHeader header;
    ByteArray code;
    ByteArray constantPool;
    ByteArray metadata;
} Program;

void Program_init(Program *program);
void Program_free(Program *program);
bool Program_loadFile(Program *program, const char *path);

#endif
