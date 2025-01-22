#ifndef VM01_INST_INFO_H
#define VM01_INST_INFO_H

#include "common.h"

typedef struct {
    int offset;
    int line;
    int column;
} InstInfo;

#endif
