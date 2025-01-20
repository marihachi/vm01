#ifndef VM_CODE_H
#define VM_CODE_H

#include "common.h"
#include "uint8Array.h"
#include "valueArray.h"

#define END_OF_CODE(code) \
    ((code)->readOffset >= (code)->stream.length)

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int line;
    int column;
} CodeLocation;

typedef struct {
    int readOffset;
    Uint8Array stream;
    ValueArray constantPool;
} Code;

void Code_init(Code *code);
int Code_writeStream(Code *code, uint8_t byte);
bool Code_readStream(Code *code, uint8_t *out_byte);
void Code_free(Code *code);
int Code_addConstant(Code *code, Value value);

#endif
