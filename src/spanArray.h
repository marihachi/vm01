#ifndef VM01_SPAN_ARRAY_H
#define VM01_SPAN_ARRAY_H

#include "common.h"

typedef struct {
    uint16_t length;
    uint16_t capacity;
    uint16_t elSize;
    uint8_t *ptr;
} SpanArray;

void SpanArray_init(SpanArray *arr, uint16_t elSize);

void SpanArray_free(SpanArray *arr);

/**
 * elSizeで指定されたサイズのバイト列を配列に追加します。
 * @returns index of the item
*/
uint16_t SpanArray_addItem(SpanArray *arr, const uint8_t *src);

uint16_t SpanArray_addItems(SpanArray *arr, const uint8_t *src, uint16_t length);

/**
 * elSizeで指定されたサイズのバイト列を配列から取得します。
*/
bool SpanArray_getItem(SpanArray *arr, uint16_t index, uint8_t *out_item);

bool SpanArray_getItems(SpanArray *arr, uint16_t index, uint8_t *out_item, uint16_t length);

#endif
