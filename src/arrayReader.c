#include <stdio.h>
#include "arrayReader.h"

#ifdef DEBUG_TRACE_ARRAY_READER
#include "debug.h"
#endif

void ArrayReader_init(ArrayReader *reader, const ByteArray *array) {
    reader->array = array;
    reader->current = array->ptr;
}

void ArrayReader_seek(ArrayReader *reader, uint32_t offset) {
    reader->current = reader->array->ptr + offset;
}

uint32_t ArrayReader_read(ArrayReader *reader, uint8_t *buf, uint32_t bufSize) {
    uint8_t *begin = reader->current;
    uint8_t *end = reader->current + bufSize;
    uint8_t *arrayEnd = reader->array->ptr + reader->array->length;
    // 読み取りサイズより配列の残りサイズの方が小さくなれば、配列の残りサイズ分だけ読み取る
    if (end > arrayEnd) {
        end = arrayEnd;
    }
    while (reader->current < end) {
        buf[reader->current - begin] = *reader->current;
        reader->current++;
    }
    uint32_t length = (uint32_t)(reader->current - begin);
    #ifdef DEBUG_TRACE_ARRAY_READER
    printf("read data (offset = 0x%04X, length = 0x%04X):\n", (uint32_t)(begin - reader->array->ptr), length);
    Debug_printBuf(buf, length);
    #endif
    return length;
}

bool ArrayReader_readByte(ArrayReader *reader, uint8_t *out_value) {
    if (reader->current < reader->array->ptr + reader->array->length) {
        *out_value = *reader->current;
        reader->current++;
        return true;
    } else {
        return false;
    }
}

uint32_t ArrayReader_forward(ArrayReader *reader, uint32_t length) {
    uint8_t *begin = reader->current;
    uint8_t *end = reader->current + length;
    uint8_t *arrayEnd = reader->array->ptr + reader->array->length;
    if (end > arrayEnd) {
        end = arrayEnd;
    }
    reader->current = end;
    return (uint32_t)(reader->current - begin);
}

bool ArrayReader_forwardByte(ArrayReader *reader) {
    if (reader->current < reader->array->ptr + reader->array->length) {
        reader->current++;
        return true;
    } else {
        return false;
    }
}
