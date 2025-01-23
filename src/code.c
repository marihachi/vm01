#include "code.h"
#include "value.h"
#include "instInfo.h"

void Code_init(Code *code) {
    Uint8Array_init(&code->stream);
    ValueArray_init(&code->constantPool);
    InstInfoArray_init(&code->info);
}

void Code_addByte(Code *code, uint8_t byte) {
    Uint8Array_addItem(&code->stream, byte);
}

void Code_SetLocation(Code *code, int line, int column) {
    InstInfo info;
    info.offset = code->stream.length - 1;
    info.line = line;
    info.column = column;
    InstInfoArray_addItem(&code->info, info);
}

int Code_addConstant(Code *code, Value value) {
    return ValueArray_addItem(&code->constantPool, value);
}

void Code_free(Code *code) {
    Uint8Array_free(&code->stream);
    ValueArray_free(&code->constantPool);
    InstInfoArray_free(&code->info);
}
