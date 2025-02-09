#include "byteArray.h"
#include "alloc.h"

static void clear(ByteArray *arr) {
    arr->capacity = 0;
    arr->length = 0;
    arr->ptr = NULL;
}

void ByteArray_init(ByteArray *arr) {
    clear(arr);
}

void ByteArray_free(ByteArray *arr) {
    FREE_MEM(uint8_t, arr->ptr, arr->capacity);
    clear(arr);
}

uint16_t ByteArray_addItem(ByteArray *arr, const uint8_t *src) {
    uint16_t newIndex = arr->length;

    // resize
    if (arr->capacity < arr->length + 1) {
        uint16_t oldCapacity = arr->capacity;
        arr->capacity = GLOWED_CAPACITY(oldCapacity);
        arr->ptr = GLOW_MEM(uint8_t, arr->ptr, oldCapacity, arr->capacity);
    }

    *(arr->ptr + arr->length) = *src;
    arr->length++;
    return newIndex;
}

uint16_t ByteArray_addItems(ByteArray *arr, const uint8_t *src, uint16_t length) {
    uint16_t head = arr->length;
    for (int i = 0; i < length; i++) {
        ByteArray_addItem(arr, src);
        src++;
    }
    return head;
}

bool ByteArray_getItem(ByteArray *arr, uint16_t index, uint8_t *out_item) {
    if (index >= arr->length) {
        return false;
    }
    *out_item = *(arr->ptr + index);
    return true;
}

bool ByteArray_getItems(ByteArray *arr, uint16_t index, uint8_t *out_item, uint16_t length) {
    if (index + length > arr->length || length < 1) {
        return false;
    }
    uint8_t *stop = arr->ptr + index + length;
    uint8_t *ptr = arr->ptr + index;
    while (ptr < stop) {
        *out_item = *ptr;
        out_item++;
        ptr++;
    }
    return true;
}
