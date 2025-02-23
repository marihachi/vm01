#include <stdio.h>
#include "byteStream.h"

#ifdef DEBUG_TRACE_READ_STREAM
#include "debug.h"
#endif

void ByteStream_init(ByteStream *stream, const ByteArray *array) {
    stream->array = array;
    stream->current = array->ptr;
}

void ByteStream_seek(ByteStream *stream, uint32_t offset) {
    stream->current = stream->array->ptr + offset;
}

uint32_t ByteStream_read(ByteStream *stream, uint8_t *buf, uint32_t bufSize) {
    uint8_t *begin = stream->current;
    uint8_t *end = stream->current + bufSize;
    uint8_t *arrayEnd = stream->array->ptr + stream->array->length;
    // 読み取りサイズより配列の残りサイズの方が小さくなれば、配列の残りサイズ分だけ読み取る
    if (end > arrayEnd) {
        end = arrayEnd;
    }
    while (stream->current < end) {
        buf[stream->current - begin] = *stream->current;
        stream->current++;
    }
    uint32_t length = (uint32_t)(stream->current - begin);
    #ifdef DEBUG_TRACE_READ_STREAM
    printf("read data (offset = 0x%04X, length = 0x%04X):\n", (uint32_t)(begin - stream->array->ptr), length);
    Debug_printBuf(buf, length);
    #endif
    return length;
}

bool ByteStream_readByte(ByteStream *stream, uint8_t *out_value) {
    if (stream->current < stream->array->ptr + stream->array->length) {
        *out_value = *stream->current;
        stream->current++;
        return true;
    } else {
        return false;
    }
}

uint32_t ByteStream_forward(ByteStream *stream, uint32_t length) {
    uint8_t *begin = stream->current;
    uint8_t *end = stream->current + length;
    uint8_t *arrayEnd = stream->array->ptr + stream->array->length;
    if (end > arrayEnd) {
        end = arrayEnd;
    }
    stream->current = end;
    return (uint32_t)(stream->current - begin);
}

bool ByteStream_forwardByte(ByteStream *stream) {
    if (stream->current < stream->array->ptr + stream->array->length) {
        stream->current++;
        return true;
    } else {
        return false;
    }
}
