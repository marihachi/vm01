#include "program.h"

void Program_init(Program *program) {
    ByteArray_init(&program->codeArray);
    ByteArray_init(&program->constantPool);
    ByteArray_init(&program->infos);
}

uint16_t Program_addConstant(Program *program, const uint8_t *value, uint16_t length) {
    return ByteArray_addItems(&program->constantPool, value, length);
}

void Program_free(Program *program) {
    ByteArray_free(&program->codeArray);
    ByteArray_free(&program->constantPool);
    ByteArray_free(&program->infos);
}
