#include "uint8Array.h"
#include "memory.h"

void Uint8Array_init(Uint8Array *arr) {
    arr->capacity = 0;
    arr->length = 0;
    arr->ptr = NULL;
}

int Uint8Array_addItem(Uint8Array *arr, uint8_t item) {
    if (arr->capacity < arr->length + 1) {
        int oldCapacity = arr->capacity;
        arr->capacity = GLOWED_CAPACITY(oldCapacity);
        arr->ptr = GLOW_MEM(uint8_t, arr->ptr, oldCapacity, arr->capacity);
    }
    arr->ptr[arr->length] = item;
    arr->length++;
    return arr->length - 1;
}

bool Uint8Array_getItem(Uint8Array *arr, int index, uint8_t *out_item) {
    if (index >= arr->length) {
        return false;
    }
    *out_item = arr->ptr[index];
    return true;
}

void Uint8Array_free(Uint8Array *arr) {
    FREE_MEM(uint8_t, arr->ptr, arr->capacity);
    Uint8Array_init(arr);
}
