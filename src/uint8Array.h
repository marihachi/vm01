#ifndef VM_UINT8_ARRAY_H
#define VM_UINT8_ARRAY_H

#include "common.h"

typedef struct {
    int length;
    int capacity;
    uint8_t *ptr;
} Uint8Array;

void Uint8Array_init(Uint8Array *arr);
int Uint8Array_addItem(Uint8Array *arr, uint8_t item);
bool Uint8Array_getItem(Uint8Array *arr, int index, uint8_t *out_item);
void Uint8Array_free(Uint8Array *arr);

#endif
