#ifndef VM01_MEMORY_H
#define VM01_MEMORY_H

#include "common.h"

#define GLOWED_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GLOW_MEM(type, ptr, oldLen, newLen) \
    (type *)memory_reallocate(ptr, sizeof(type) * (oldLen), sizeof(type) * (newLen))

#define FREE_MEM(type, ptr, oldLen) \
    (type *)memory_reallocate(ptr, sizeof(type) * (oldLen), 0)

void *memory_reallocate(void *ptr, size_t oldSize, size_t newSize);

#endif
