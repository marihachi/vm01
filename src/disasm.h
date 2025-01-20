#ifndef VM_DISASM_H
#define VM_DISASM_H

#include "common.h"
#include "code.h"

void disasm_disassembleCode(Code *code);
void disasm_disassembleInst(Code *code);

#endif
