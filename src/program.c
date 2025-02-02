#include "program.h"

void Program_init(Program *program) {
    SpanArray_init(&program->codeArray, 1);
    SpanArray_init(&program->constantPool, 1);
    SpanArray_init(&program->infos, 1);
}

uint16_t Program_addConstant(Program *program, const uint8_t *value, uint16_t length) {
    return SpanArray_addItems(&program->constantPool, value, length);
}

void Program_free(Program *program) {
    SpanArray_free(&program->codeArray);
    SpanArray_free(&program->constantPool);
    SpanArray_free(&program->infos);
}
