#include <stdio.h>
#include "disasm.h"
#include "value.h"
#include "valueArray.h"

static InstInfo *findInstInfo(Code *code, int offset) {
    int i = 0;
    InstInfo *ptr = NULL;
    while (i < code->info.length) {
        ptr = &code->info.ptr[i];
        if (ptr->offset >= offset) {
            break;
        }
        i++;
    }
    if (ptr != NULL && ptr->offset == offset) {
        return ptr;
    } else {
        return NULL;
    }
}

static void printLocation(Code *code, int instOffset) {
    InstInfo *info = findInstInfo(code, instOffset);
    if (info == NULL) {
        printf("instruction info not found\n");
        return;
    }
    printf("(%d:%d)", info->line, info->column);
}

static void constantInstruction(Code *code, int instOffset) {
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
    printf(" ");
    printLocation(code, instOffset);
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
    int instOffset = code->readOffset;
    printf("%04d ", instOffset);

    uint8_t opcode;
    if (!Code_readStream(code, &opcode)) {
        printf("fetch failed\n");
        return;
    }
    switch (opcode) {
        case OP_CONSTANT:
            constantInstruction(code, instOffset);
            return;
        case OP_RETURN:
            printf("OP_RETURN ");
            printLocation(code, instOffset);
            printf("\n");
            return;
        default:
            printf("unknown opcode %d ", opcode);
            printLocation(code, instOffset);
            printf("\n");
            return;
    }
}
