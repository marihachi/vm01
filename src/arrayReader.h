#ifndef VM01_ARRAY_READER_H
#define VM01_ARRAY_READER_H

#include "common.h"
#include "byteArray.h"

typedef struct {
    const ByteArray *array;
    uint8_t *current;
} ArrayReader;

void ArrayReader_init(ArrayReader *reader, const ByteArray *array);
void ArrayReader_seek(ArrayReader *reader, uint32_t offset);
uint32_t ArrayReader_read(ArrayReader *reader, uint8_t *buf, uint32_t bufSize);
bool ArrayReader_readByte(ArrayReader *reader, uint8_t *out_value);
uint32_t ArrayReader_forward(ArrayReader *reader, uint32_t length);
bool ArrayReader_forwardByte(ArrayReader *reader);

#endif
