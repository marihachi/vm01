#include "instInfo.h"

void InstInfo_init(InstInfo *info, uint32_t addr) {
    info->addr = addr;
}

void InstInfo_setLocation(InstInfo *info, uint32_t line, uint32_t column) {
    info->line = line;
    info->column = column;
}
