#include <stdlib.h>
#include "memory.h"

void *memory_reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }
    void *resultPointer = realloc(pointer, newSize);
    if (resultPointer == NULL) {
        exit(1);
    }
    return resultPointer;
}
