#include "code.h"

void Code_init(Code *code) {
    Uint8Array_init(&code->stream);
    ValueArray_init(&code->constantPool);
    code->readOffset = 0;
}

int Code_writeStream(Code *code, uint8_t byte) {
    return Uint8Array_addItem(&code->stream, byte);
}

bool Code_readStream(Code *code, uint8_t *out_byte) {
    bool result = Uint8Array_getItem(&code->stream, code->readOffset, out_byte);
    if (result) {
        code->readOffset++;
    }
    return result;
}

int Code_addConstant(Code *code, Value value) {
    return ValueArray_addItem(&code->constantPool, value);
}

void Code_free(Code *code) {
    Uint8Array_free(&code->stream);
    ValueArray_free(&code->constantPool);
}
