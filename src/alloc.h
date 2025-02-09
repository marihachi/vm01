#ifndef VM01_ALLOC_H
#define VM01_ALLOC_H

#include "common.h"

#define GLOWED_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GLOW_MEM(type, ptr, oldLen, newLen) \
    (type *)reallocMem(ptr, sizeof(type) * (oldLen), sizeof(type) * (newLen))

#define FREE_MEM(type, ptr, oldLen) \
    (type *)reallocMem(ptr, sizeof(type) * (oldLen), 0)

void *reallocMem(void *ptr, size_t oldSize, size_t newSize);

#endif
