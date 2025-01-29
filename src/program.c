#include "program.h"
#include "value.h"
#include "instInfo.h"

void Program_init(Program *program) {
    Uint8Array_init(&program->codeArray);
    Uint8Array_init(&program->constantPool);
    InstInfoArray_init(&program->info);
}

uint16_t Program_addByte(Program *program, uint8_t value) {
    return Uint8Array_addItem(&program->codeArray, value);
}

uint16_t Program_addBytes(Program *program, const uint8_t *value, int length) {
    return Uint8Array_addItems(&program->codeArray, value, length);
}

void Program_addInfo(Program *program, InstInfo *info) {
    InstInfoArray_addItem(&program->info, *info);
}

uint16_t Program_addConstant(Program *program, const uint8_t *value, int length) {
    return Uint8Array_addItems(&program->constantPool, value, length);
}

void Program_free(Program *program) {
    Uint8Array_free(&program->codeArray);
    Uint8Array_free(&program->constantPool);
    InstInfoArray_free(&program->info);
}
