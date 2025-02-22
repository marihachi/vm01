#ifndef VM01_BYTE_ARRAY_H
#define VM01_BYTE_ARRAY_H

#include "common.h"

typedef struct {
    uint32_t length;
    uint32_t capacity;
    uint8_t *ptr;
} ByteArray;

void ByteArray_init(ByteArray *arr);

void ByteArray_free(ByteArray *arr);

/**
 * @returns index of the item
*/
uint32_t ByteArray_addItem(ByteArray *arr, const uint8_t *src);

/**
 * @returns index of the head item
*/
uint32_t ByteArray_addItems(ByteArray *arr, const uint8_t *src, uint32_t length);

bool ByteArray_getItem(const ByteArray *arr, uint32_t index, uint8_t *out_item);

bool ByteArray_getItems(const ByteArray *arr, uint32_t index, uint8_t *out_item, uint32_t length);

void ByteArray_clear(ByteArray *arr);

#endif
