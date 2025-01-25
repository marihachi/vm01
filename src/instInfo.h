#ifndef VM01_INST_INFO_H
#define VM01_INST_INFO_H

#include "common.h"

typedef struct {
    int addr;
    int line;
    int column;
} InstInfo;

void InstInfo_init(InstInfo *info, int addr);
void InstInfo_setLocation(InstInfo *info, int line, int column);

#endif
