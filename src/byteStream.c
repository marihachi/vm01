#include "byteStream.h"

void ByteStream_init(ByteStream *stream, const ByteArray *array) {
    stream->array = array;
    stream->current = array->ptr;
}

void ByteStream_seek(ByteStream *stream, uint32_t offset) {
    stream->current = stream->array->ptr + offset;
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

bool ByteStream_forwardByte(ByteStream *stream) {
    if (stream->current < stream->array->ptr + stream->array->length) {
        stream->current++;
        return true;
    } else {
        return false;
    }
}
