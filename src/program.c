#include "program.h"

void Program_init(Program *program) {
    ByteArray_init(&program->code);
    ByteArray_init(&program->constantPool);
    ByteArray_init(&program->metadata);
}

void Program_free(Program *program) {
    ByteArray_free(&program->code);
    ByteArray_free(&program->constantPool);
    ByteArray_free(&program->metadata);
}
