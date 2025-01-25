#ifndef VM01_INST_INFO_ARRAY_H
#define VM01_INST_INFO_ARRAY_H

#include "common.h"
#include "instInfo.h"

typedef struct {
    int length;
    int capacity;
    InstInfo *ptr;
} InstInfoArray;

void InstInfoArray_init(InstInfoArray *arr);
int InstInfoArray_addItem(InstInfoArray *arr, InstInfo item);
bool InstInfoArray_getItem(InstInfoArray *arr, int index, InstInfo *out_item);
void InstInfoArray_free(InstInfoArray *arr);

#endif
