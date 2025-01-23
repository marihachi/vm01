#ifndef VM01_DISASM_H
#define VM01_DISASM_H

#include "common.h"
#include "code.h"

void disasm_disassembleCode(Code *code);

/**
 * @returns offset of the next instruction
*/
int disasm_disassembleInst(Code *code, int instOffset);

#endif
