#ifndef VM01_CODE_H
#define VM01_CODE_H

#include "common.h"
#include "uint8Array.h"
#include "valueArray.h"
#include "instInfoArray.h"

#define END_OF_CODE(code, offset) \
    ((offset) >= (code)->stream.length)

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    Uint8Array stream;
    ValueArray constantPool;
    InstInfoArray info;
} Code;

void Code_init(Code *code);
void Code_addByte(Code *code, uint8_t byte);
void Code_SetLocation(Code *code, int line, int column);
int Code_addConstant(Code *code, Value value);
void Code_free(Code *code);

#endif
