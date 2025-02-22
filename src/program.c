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
    uint32_t offset;
    ProgramHeader *header;
    uint32_t length = 0;

    header = &program->header;
    offset = 0;

    // program header

    if (!ByteArray_getItems(src, offset, (uint8_t *)header, sizeof(ProgramHeader))) {
        printf("invalid program header\n");
        return false;
    }

    if (header->constantOffset >= src->length ||
        header->metadataOffset >= src->length ||
        header->programOffset >= src->length
    ) {
        printf("invalid program header\n");
        return false;
    }

    // constant pool

    offset = header->constantOffset;
    if (!ByteArray_getItems(src, offset, (uint8_t *)&length, sizeof(length))) {
        printf("invalid constant header\n");
        return false;
    }
    offset += sizeof(length);
    if (!ByteArray_addFromArray(&program->constantPool, src, offset, length)) {
        printf("invalid constant block\n");
        return false;
    }

    // metadata

    offset = header->metadataOffset;
    if (!ByteArray_getItems(src, offset, (uint8_t *)&length, sizeof(length))) {
        printf("invalid metadata header\n");
        return false;
    }
    offset += sizeof(length);
    if (!ByteArray_addFromArray(&program->metadata, src, offset, length)) {
        printf("invalid metadata block\n");
        return false;
    }

    // code

    offset = header->programOffset;
    if (!ByteArray_getItems(src, offset, (uint8_t *)&length, sizeof(length))) {
        printf("invalid code header\n");
        return false;
    }
    offset += sizeof(length);
    if (!ByteArray_addFromArray(&program->code, src, offset, length)) {
        printf("invalid code block\n");
        return false;
    }

    return true;
}
