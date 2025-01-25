#include "program.h"
#include "value.h"
#include "instInfo.h"

void Program_init(Program *program) {
    Uint8Array_init(&program->codeArray);
    ValueArray_init(&program->constantPool);
    InstInfoArray_init(&program->info);
}

int Program_addByte(Program *program, uint8_t byte) {
    return Uint8Array_addItem(&program->codeArray, byte);
}

void Program_addInfo(Program *program, InstInfo *info) {
    InstInfoArray_addItem(&program->info, *info);
}

int Program_addConstant(Program *program, Value value) {
    return ValueArray_addItem(&program->constantPool, value);
}

void Program_free(Program *program) {
    Uint8Array_free(&program->codeArray);
    ValueArray_free(&program->constantPool);
    InstInfoArray_free(&program->info);
}
