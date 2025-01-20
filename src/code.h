#ifndef VM_CODE_H
#define VM_CODE_H

#include "common.h"
#include "uint8Array.h"
#include "valueArray.h"
#include "instInfoArray.h"

#define END_OF_CODE(code) \
    ((code)->readOffset >= (code)->stream.length)

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int readOffset;
    Uint8Array stream;
    ValueArray constantPool;
    InstInfoArray info;
} Code;

void Code_init(Code *code);
void Code_writeStream(Code *code, uint8_t byte);
void Code_SetLocation(Code *code, int line, int column);
bool Code_readStream(Code *code, uint8_t *out_byte);
void Code_free(Code *code);
int Code_addConstant(Code *code, Value value);

#endif
