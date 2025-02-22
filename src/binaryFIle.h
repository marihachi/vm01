#ifndef VM01_BINARY_FILE_H
#define VM01_BINARY_FILE_H

#include "common.h"
#include "byteArray.h"

bool binaryFile_readToEnd(const char *path, ByteArray *byteArray);

#endif
