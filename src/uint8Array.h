#ifndef VM01_UINT8_ARRAY_H
#define VM01_UINT8_ARRAY_H

#include "common.h"

typedef struct {
    uint16_t length;
    uint16_t capacity;
    uint8_t *ptr;
} Uint8Array;

void Uint8Array_init(Uint8Array *arr);

/**
 * @returns index of the item
*/
uint16_t Uint8Array_addItem(Uint8Array *arr, uint8_t item);

uint16_t Uint8Array_addItems(Uint8Array *arr, const uint8_t *item, int length);

bool Uint8Array_getItem(Uint8Array *arr, uint16_t index, uint8_t *out_item);

bool Uint8Array_getItems(Uint8Array *arr, uint16_t index, int length, uint8_t *out_items);

void Uint8Array_free(Uint8Array *arr);

#endif
