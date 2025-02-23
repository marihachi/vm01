#include <stdio.h>
#include "binaryFile.h"

bool binaryFile_readToEnd(const char *path, ByteArray *byteArray) {
    uint8_t buf[1024];
    uint32_t count;
    bool success = true;

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return false;
    }

    while (!feof(file)) {
        count = (uint32_t)fread(buf, 1, sizeof(buf), file);
        if (ferror(file)) {
            success = false;
            goto finally;
        }
        ByteArray_addItems(byteArray, buf, count);
    }

finally:
    fclose(file);

    return success;
}
