#include <stdio.h>
#include "common.h"
#include "code.h"
#include "disasm.h"

int main(int argc, const char* argv[]) {
    Code code;

    Code_init(&code);
    int poolAddress = Code_addConstant(&code, 1.2);
    Code_writeStream(&code, OP_CONSTANT);
    Code_SetLocation(&code, 1, 1);
    Code_writeStream(&code, poolAddress);
    Code_writeStream(&code, OP_RETURN);
    Code_SetLocation(&code, 2, 1);
    disasm_disassembleCode(&code);
    Code_free(&code);

    return 0;
}
