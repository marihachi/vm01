#include <stdio.h>
#include "disasm.h"
#include "value.h"
#include "valueArray.h"

static void constantInstruction(Code *code) {
    uint8_t address;
    if (!Code_readStream(code, &address)) {
        printf("fetch failed\n");
        return;
    }
    printf("OP_CONSTANT %d ", address);
    Value value;
    if (!ValueArray_getItem(&code->constantPool, address, &value)) {
        printf("fetch failed\n");
        return;
    }
    Value_print(value);
    printf("\n");
}

void disasm_disassembleCode(Code *code) {
    printf("== BEGIN PROGRAM ==\n");
    while (!END_OF_CODE(code)) {
        disasm_disassembleInst(code);
    }
    printf("== END PROGRAM ==\n");
}

void disasm_disassembleInst(Code *code) {
    printf("%04d ", code->readOffset);
    uint8_t opcode;

    if (!Code_readStream(code, &opcode)) {
        printf("fetch failed\n");
        return;
    }
    switch (opcode) {
        case OP_CONSTANT:
            constantInstruction(code);
            return;
        case OP_RETURN:
            printf("OP_RETURN\n");
            return;
        default:
            printf("unknown opcode %d\n", opcode);
            return;
    }
}
