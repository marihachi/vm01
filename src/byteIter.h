#ifndef VM01_BYTE_ITER_H
#define VM01_BYTE_ITER_H

#include "common.h"
#include "byteArray.h"

typedef struct {
    const ByteArray *array;
    uint8_t *current;
} ByteIter;

void ByteIter_init(ByteIter *iter, const ByteArray *array);
bool ByteIter_iterate(ByteIter *iter, uint8_t *out_value);

#endif
