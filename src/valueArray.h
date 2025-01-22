#ifndef VM01_VALUE_ARRAY_H
#define VM01_VALUE_ARRAY_H

#include "common.h"
#include "value.h"

typedef struct {
    int length;
    int capacity;
    Value *ptr;
} ValueArray;

void ValueArray_init(ValueArray *arr);
int ValueArray_addItem(ValueArray *arr, Value item);
bool ValueArray_getItem(ValueArray *arr, int index, Value *out_item);
void ValueArray_free(ValueArray *arr);

#endif
