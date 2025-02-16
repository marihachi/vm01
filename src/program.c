#include "program.h"
#include <stdio.h>

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

bool Program_load(Program *program, ByteArray *src) {
    bool success;
    uint32_t offset;
    ProgramHeader *header;

    header = &program->header;
    offset = 0;

    success = ByteArray_getItems(src, offset, (uint8_t *)header, sizeof(ProgramHeader));
    if (!success) {
        return false;
    }
    offset = sizeof(ProgramHeader);

    if (header->constantLength > 0) {
        ByteArray_addFromArray(&program->constantPool, src, offset, header->constantLength);
        offset += header->constantLength;
    }

    if (header->metadataLength > 0) {
        ByteArray_addFromArray(&program->metadata, src, offset, header->metadataLength);
        offset += header->metadataLength;
    }

    ByteArray_addFromArray(&program->code, src, offset, header->programLength);
    offset += header->programLength;

    return true;
}
