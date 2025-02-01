#include "instInfo.h"

void InstInfo_init(InstInfo *info) {
}

void InstInfo_setLocation(InstInfo *info, uint32_t addr, uint32_t line, uint32_t column) {
    info->addr = addr;
    info->line = line;
    info->column = column;
}
