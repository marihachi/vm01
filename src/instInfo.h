#ifndef VM01_INST_INFO_H
#define VM01_INST_INFO_H

#include "common.h"

typedef struct {
    uint32_t addr;
    uint32_t line;
    uint32_t column;
} InstInfo;

void InstInfo_init(InstInfo *info, uint32_t addr);
void InstInfo_setLocation(InstInfo *info, uint32_t line, uint32_t column);

#endif
