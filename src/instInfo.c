#include "instInfo.h"

void InstInfo_init(InstInfo *info, int addr) {
    info->addr = addr;
}

void InstInfo_setLocation(InstInfo *info, int line, int column) {
    info->line = line;
    info->column = column;
}
