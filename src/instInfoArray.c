#include "instInfoArray.h"
#include "memory.h"

void InstInfoArray_init(InstInfoArray *arr) {
    arr->capacity = 0;
    arr->length = 0;
    arr->ptr = NULL;
}

int InstInfoArray_addItem(InstInfoArray *arr, InstInfo item) {
    if (arr->capacity < arr->length + 1) {
        int oldCapacity = arr->capacity;
        arr->capacity = GLOWED_CAPACITY(oldCapacity);
        arr->ptr = GLOW_MEM(InstInfo, arr->ptr, oldCapacity, arr->capacity);
    }
    arr->ptr[arr->length] = item;
    arr->length++;
    return arr->length - 1;
}

bool InstInfoArray_getItem(InstInfoArray *arr, int index, InstInfo *out_item) {
    if (index >= arr->length) {
        return false;
    }
    *out_item = arr->ptr[index];
    return true;
}

void InstInfoArray_free(InstInfoArray *arr) {
    FREE_MEM(InstInfo, arr->ptr, arr->capacity);
    InstInfoArray_init(arr);
}
