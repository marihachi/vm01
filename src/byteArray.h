#ifndef VM01_SPAN_ARRAY_H
#define VM01_SPAN_ARRAY_H

#include "common.h"

typedef struct {
    uint16_t length;
    uint16_t capacity;
    uint8_t *ptr;
} ByteArray;

void ByteArray_init(ByteArray *arr);

void ByteArray_free(ByteArray *arr);

/**
 * @returns index of the item
*/
uint16_t ByteArray_addItem(ByteArray *arr, const uint8_t *src);

/**
 * @returns index of the head item
*/
uint16_t ByteArray_addItems(ByteArray *arr, const uint8_t *src, uint16_t length);

bool ByteArray_getItem(ByteArray *arr, uint16_t index, uint8_t *out_item);

bool ByteArray_getItems(ByteArray *arr, uint16_t index, uint8_t *out_item, uint16_t length);

#endif
