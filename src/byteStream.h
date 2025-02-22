#ifndef VM01_BYTE_STREAM_H
#define VM01_BYTE_STREAM_H

#include "common.h"
#include "byteArray.h"

typedef struct {
    const ByteArray *array;
    uint8_t *current;
} ByteStream;

void ByteStream_init(ByteStream *stream, const ByteArray *array);
void ByteStream_seek(ByteStream *stream, uint32_t offset);
bool ByteStream_readByte(ByteStream *stream, uint8_t *out_value);
bool ByteStream_forwardByte(ByteStream *stream);

#endif
