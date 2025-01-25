#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "value.h"
#include "valueArray.h"

static InstInfo *findInstInfo(Program *program, int offset) {
    int i = 0;
    InstInfo *ptr = NULL;
    while (i < program->info.length) {
        ptr = &program->info.ptr[i];
        if (ptr->addr >= offset) {
            break;
        }
        i++;
    }
    if (ptr != NULL && ptr->addr == offset) {
        return ptr;
    } else {
        return NULL;
    }
}

static void printLocation(Program *program, int instOffset) {
    InstInfo *info = findInstInfo(program, instOffset);
    if (info == NULL) {
        printf("instruction info not found\n");
        return;
    }
    printf("(%d:%d)", info->line, info->column);
}

static int constantInstruction(Program *program, int instOffset) {
    uint8_t address;
    if (!Uint8Array_getItem(&program->codeArray, instOffset + 1, &address)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    printf("OP_CONSTANT 0x%02X ", address);
    Value value;
    if (!ValueArray_getItem(&program->constantPool, address, &value)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    Value_print(value);
    printf(" ");
    printLocation(program, instOffset);
    printf("\n");
    return instOffset + 2;
}

void Debug_printProgram(Program *program) {
    printf("== BEGIN PROGRAM ==\n");
    int instOffset = 0;
    while (!END_OF_SECTION(program, instOffset)) {
        instOffset = Debug_printInst(program, instOffset);
    }
    printf("== END PROGRAM ==\n");
}

int Debug_printInst(Program *program, int instOffset) {
    printf("0x%04X ", instOffset);

    uint8_t opcode;
    if (!Uint8Array_getItem(&program->codeArray, instOffset, &opcode)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    switch (opcode) {
        case OP_CONSTANT:
            return constantInstruction(program, instOffset);
        case OP_PRINT_NUM:
            printf("OP_PRINT_NUM ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_RETURN:
            printf("OP_RETURN ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        default:
            printf("unknown opcode 0x%02X ", opcode);
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
    }
}
