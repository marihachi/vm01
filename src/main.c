#include <stdio.h>
#include "common.h"
#include "code.h"
#include "disasm.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
    VM_init();
    Code code;
    int constantAddr;

    Code_init(&code);
    Code_addByte(&code, OP_CONSTANT);
    Code_SetLocation(&code, 1, 1);
    constantAddr = Code_addConstant(&code, 2.3);
    Code_addByte(&code, constantAddr);
    Code_addByte(&code, OP_RETURN);
    Code_SetLocation(&code, 2, 1);
    disasm_disassembleCode(&code);
    printf("executing...\n");
    InterpretResult result = VM_interpret(&code);
    printf("Result code %d.\n", result);
    VM_free();
    Code_free(&code);

    return 0;
}
