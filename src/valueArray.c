#include "valueArray.h"
#include "memory.h"

void ValueArray_init(ValueArray *arr) {
    arr->capacity = 0;
    arr->length = 0;
    arr->ptr = NULL;
}

int ValueArray_addItem(ValueArray *arr, Value item) {
    if (arr->capacity < arr->length + 1) {
        int oldCapacity = arr->capacity;
        arr->capacity = GLOWED_CAPACITY(oldCapacity);
        arr->ptr = GLOW_MEM(Value, arr->ptr, oldCapacity, arr->capacity);
    }
    arr->ptr[arr->length] = item;
    arr->length++;
    return arr->length - 1;
}

bool ValueArray_getItem(ValueArray *arr, int index, Value *out_item) {
    if (index >= arr->length) {
        return false;
    }
    *out_item = arr->ptr[index];
    return true;
}

void ValueArray_free(ValueArray *arr) {
    FREE_MEM(Value, arr->ptr, arr->capacity);
    ValueArray_init(arr);
}
