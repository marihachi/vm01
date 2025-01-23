#include <stdio.h>
#include <stdlib.h>
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

static int constantInstruction(Code *code, int instOffset) {
    uint8_t address;
    if (!Uint8Array_getItem(&code->stream, instOffset + 1, &address)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    printf("OP_CONSTANT %d ", address);
    Value value;
    if (!ValueArray_getItem(&code->constantPool, address, &value)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    Value_print(value);
    printf(" ");
    printLocation(code, instOffset);
    printf("\n");
    return instOffset + 2;
}

void disasm_disassembleCode(Code *code) {
    printf("== BEGIN PROGRAM ==\n");
    int instOffset = 0;
    while (!END_OF_CODE(code, instOffset)) {
        instOffset = disasm_disassembleInst(code, instOffset);
    }
    printf("== END PROGRAM ==\n");
}

int disasm_disassembleInst(Code *code, int instOffset) {
    printf("%04d ", instOffset);

    uint8_t opcode;
    if (!Uint8Array_getItem(&code->stream, instOffset, &opcode)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    switch (opcode) {
        case OP_CONSTANT:
            return constantInstruction(code, instOffset);
        case OP_RETURN:
            printf("OP_RETURN ");
            printLocation(code, instOffset);
            printf("\n");
            return instOffset + 1;
        default:
            printf("unknown opcode %d ", opcode);
            printLocation(code, instOffset);
            printf("\n");
            return instOffset + 1;
    }
}
