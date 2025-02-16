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

uint32_t ByteArray_addItem(ByteArray *arr, const uint8_t *src) {
    uint32_t newIndex = arr->length;

    // resize
    if (arr->capacity < arr->length + 1) {
        uint32_t oldCapacity = arr->capacity;
        arr->capacity = GLOWED_CAPACITY(oldCapacity);
        arr->ptr = GLOW_MEM(uint8_t, arr->ptr, oldCapacity, arr->capacity);
    }

    *(arr->ptr + arr->length) = *src;
    arr->length++;
    return newIndex;
}

uint32_t ByteArray_addItems(ByteArray *arr, const uint8_t *src, uint32_t length) {
    uint32_t head = arr->length;
    for (uint32_t i = 0; i < length; i++) {
        ByteArray_addItem(arr, src);
        src++;
    }
    return head;
}

uint32_t ByteArray_addFromArray(ByteArray *arr, const ByteArray *src, uint32_t srcOffset, uint32_t length) {
    uint32_t head = arr->length;
    uint8_t temp;
    for (uint32_t i = 0; i < length; i++) {
        if (!ByteArray_getItem(src, srcOffset + i, &temp)) {
            exit(1);
        }
        ByteArray_addItem(arr, &temp);
    }
    return head;
}

bool ByteArray_getItem(const ByteArray *arr, uint32_t index, uint8_t *out_item) {
    if (index >= arr->length) {
        return false;
    }
    *out_item = *(arr->ptr + index);
    return true;
}

bool ByteArray_getItems(const ByteArray *arr, uint32_t index, uint8_t *out_item, uint32_t length) {
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
