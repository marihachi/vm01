#include <stdio.h>
#include <stdlib.h>
#include "program.h"
#include "binaryFile.h"
#include "arrayReader.h"

#ifdef DEBUG_TRACE_DECODE
#include "debug.h"
#endif

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

static bool decode(Program *program, const ByteArray *src) {
    ProgramHeader *header;
    ArrayReader reader;
    uint32_t readLength, readResult, length;
    uint8_t buf[64];

    length = 0;
    header = &program->header;

    ArrayReader_init(&reader, src);

    // file header
    #ifdef DEBUG_TRACE_DECODE
    printf("-- file header --\n");
    #endif
    readResult = ArrayReader_read(&reader, (uint8_t *)header, sizeof(ProgramHeader));
    if (readResult < sizeof(ProgramHeader)) {
        printf("invalid file header\n");
        return false;
    }
    #ifdef DEBUG_TRACE_DECODE
    printf("magic code: %c%c%c%c\n", header->magicCode[0], header->magicCode[1], header->magicCode[2] ,header->magicCode[3]);
    printf("constants block offset: 0x%04X\n", header->constantOffset);
    printf("metadata block offset: 0x%04X\n", header->metadataOffset);
    printf("code block offset: 0x%04X\n", header->programOffset);
    #endif
    if (header->magicCode[0] != 'V' || header->magicCode[1] != 'M' || header->magicCode[2] != '0' || header->magicCode[3] != '1' ||
        header->constantOffset >= src->length ||
        header->metadataOffset >= src->length ||
        header->programOffset >= src->length
    ) {
        printf("invalid file header\n");
        return false;
    }

    // constants block
    #ifdef DEBUG_TRACE_DECODE
    printf("-- constants block --\n");
    #endif
    ArrayReader_seek(&reader, header->constantOffset);
    readResult = ArrayReader_read(&reader, (uint8_t *)&length, sizeof(length));
    if (readResult < sizeof(length)) {
        printf("invalid constants header\n");
        return false;
    }
    #ifdef DEBUG_TRACE_DECODE
    printf("block size 0x%04X\n", length);
    #endif
    while (length > 0) {
        readLength = length < sizeof(buf) ? length : sizeof(buf);
        readResult = ArrayReader_read(&reader, buf, readLength);
        if (readResult == 0) {
            printf("invalid constants block\n");
            return false;
        }
        ByteArray_addItems(&program->constantPool, buf, readResult);
        length -= readResult;
    }

    // metadata block
    #ifdef DEBUG_TRACE_DECODE
    printf("-- metadata block --\n");
    #endif
    ArrayReader_seek(&reader, header->metadataOffset);
    readResult = ArrayReader_read(&reader, (uint8_t *)&length, sizeof(length));
    if (readResult < sizeof(length)) {
        printf("invalid metadata header\n");
        return false;
    }
    #ifdef DEBUG_TRACE_DECODE
    printf("block size 0x%04X\n", length);
    #endif
    while (length > 0) {
        readLength = length < sizeof(buf) ? length : sizeof(buf);
        readResult = ArrayReader_read(&reader, buf, readLength);
        if (readResult == 0) {
            printf("invalid metadata block\n");
            return false;
        }
        ByteArray_addItems(&program->metadata, buf, readResult);
        length -= readResult;
    }

    // code block
    #ifdef DEBUG_TRACE_DECODE
    printf("-- code block --\n");
    #endif
    ArrayReader_seek(&reader, header->programOffset);
    readResult = ArrayReader_read(&reader, (uint8_t *)&length, sizeof(length));
    if (readResult < sizeof(length)) {
        printf("invalid code header\n");
        return false;
    }
    #ifdef DEBUG_TRACE_DECODE
    printf("block size 0x%04X\n", length);
    #endif
    while (length > 0) {
        readLength = length < sizeof(buf) ? length : sizeof(buf);
        readResult = ArrayReader_read(&reader, buf, readLength);
        if (readResult == 0) {
            printf("invalid code block\n");
            return false;
        }
        ByteArray_addItems(&program->code, buf, readResult);
        length -= readResult;
    }

    #ifdef DEBUG_TRACE_DECODE
    printf("\n");
    #endif

    return true;
}

bool Program_loadFile(Program *program, const char *path) {
    bool result = true;
    ByteArray fileData;

    ByteArray_init(&fileData);

    if (!binaryFile_readToEnd(path, &fileData)) {
        result = false;
        goto finally;
    }

    if (!decode(program, &fileData)) {
        result = false;
        goto finally;
    }

finally:
    ByteArray_free(&fileData);

    return result;
}
