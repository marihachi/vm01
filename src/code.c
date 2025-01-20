#include "code.h"
#include "value.h"
#include "instInfo.h"

void Code_init(Code *code) {
    Uint8Array_init(&code->stream);
    ValueArray_init(&code->constantPool);
    InstInfoArray_init(&code->info);
    code->readOffset = 0;
}

void Code_writeStream(Code *code, uint8_t byte) {
    Uint8Array_addItem(&code->stream, byte);
}

void Code_SetLocation(Code *code, int line, int column) {
    InstInfo info;
    info.offset = code->stream.length - 1;
    info.line = line;
    info.column = column;
    InstInfoArray_addItem(&code->info, info);
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
    InstInfoArray_free(&code->info);
}
