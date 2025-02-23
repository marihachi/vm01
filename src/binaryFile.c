#include <stdio.h>
#include "binaryFile.h"

bool binaryFile_readToEnd(const char *path, ByteArray *byteArray) {
    uint8_t buf[1024];
    uint32_t count;
    bool success = true;

    FILE *stream = fopen(path, "rb");
    if (stream == NULL) {
        return false;
    }

    while (!feof(stream)) {
        count = (uint32_t)fread(buf, 1, sizeof(buf), stream);
        if (ferror(stream)) {
            success = false;
            goto finally;
        }
        ByteArray_addItems(byteArray, buf, count);
    }

finally:
    fclose(stream);

    return success;
}
