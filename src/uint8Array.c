#include "uint8Array.h"
#include "memory.h"

void Uint8Array_init(Uint8Array *arr) {
    arr->capacity = 0;
    arr->length = 0;
    arr->ptr = NULL;
}


uint16_t Uint8Array_addItem(Uint8Array *arr, uint8_t item) {
    if (arr->capacity < arr->length + 1) {
        uint16_t oldCapacity = arr->capacity;
        arr->capacity = GLOWED_CAPACITY(oldCapacity);
        arr->ptr = GLOW_MEM(uint8_t, arr->ptr, oldCapacity, arr->capacity);
    }
    arr->ptr[arr->length] = item;
    arr->length++;
    return arr->length - 1;
}

uint16_t Uint8Array_addItems(Uint8Array *arr, const uint8_t *item, int length) {
    uint16_t address = 0;
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            address = Uint8Array_addItem(arr, *item);
        } else {
            Uint8Array_addItem(arr, *item);
        }
        item++;
    }
    return address;
}

bool Uint8Array_getItem(Uint8Array *arr, uint16_t index, uint8_t *out_item) {
    if (index >= arr->length) {
        return false;
    }
    *out_item = arr->ptr[index];
    return true;
}

bool Uint8Array_getItems(Uint8Array *arr, uint16_t index, int length, uint8_t *out_items) {
    if (index + length > arr->length) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        *out_items = arr->ptr[index + i];
        out_items++;
    }
    return true;
}

void Uint8Array_free(Uint8Array *arr) {
    FREE_MEM(uint8_t, arr->ptr, arr->capacity);
    Uint8Array_init(arr);
}
