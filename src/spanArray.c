#include "spanArray.h"
#include "memory.h"

static void clear(SpanArray *arr) {
    arr->capacity = 0;
    arr->length = 0;
    arr->ptr = NULL;
}

void SpanArray_init(SpanArray *arr, uint16_t elSize) {
    arr->elSize = elSize;
    clear(arr);
}

void SpanArray_free(SpanArray *arr) {
    FREE_MEM(uint8_t, arr->ptr, arr->capacity);
    clear(arr);
}

uint16_t SpanArray_addItem(SpanArray *arr, const uint8_t *src) {
    uint16_t newIndex = arr->length;
    for (int i = 0; i < arr->elSize; i++) {
        if (arr->capacity < arr->length + i + 1) {
            uint16_t oldCapacity = arr->capacity;
            arr->capacity = GLOWED_CAPACITY(oldCapacity);
            arr->ptr = GLOW_MEM(uint8_t, arr->ptr, arr->elSize * oldCapacity, arr->elSize * arr->capacity);
        }
        arr->ptr[arr->elSize * arr->length + i] = *src;
        src++;
    }
    arr->length++;
    return newIndex;
}

uint16_t SpanArray_addItems(SpanArray *arr, const uint8_t *src, uint16_t length) {
    uint16_t newIndex = arr->length;
    for (int i = 0; i < length; i++) {
        SpanArray_addItem(arr, src);
        src += arr->elSize;
    }
    return newIndex;
}

bool SpanArray_getItem(SpanArray *arr, uint16_t index, uint8_t *out_item) {
    if (index >= arr->length) {
        return false;
    }
    for (int i = 0; i < arr->elSize; i++) {
        *out_item = arr->ptr[arr->elSize * index + i];
        out_item++;
    }
    return true;
}

bool SpanArray_getItems(SpanArray *arr, uint16_t index, uint8_t *out_item, uint16_t length) {
    for (int i = 0; i < length; i++) {
        if (!SpanArray_getItem(arr, index + i, out_item)) {
            return false;
        }
        out_item += arr->elSize;
    }
    return true;
}
