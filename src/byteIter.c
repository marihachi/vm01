#include "byteIter.h"

void ByteIter_init(ByteIter *iter, const ByteArray *array) {
    iter->array = array;
    iter->current = array->ptr;
}

bool ByteIter_iterate(ByteIter *iter, uint8_t *out_value) {
    if (iter->current < iter->array->ptr + iter->array->length) {
        *out_value = *iter->current;
        iter->current++;
        return true;
    } else {
        return false;
    }
}
