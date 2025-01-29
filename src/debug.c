#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "value.h"

static InstInfo *findInstInfo(Program *program, uint32_t offset) {
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

static int pushInstruction(Program *program, int instOffset) {
    uint16_t address;
    if (!Uint8Array_getItems(&program->codeArray, instOffset + 1, 2, (uint8_t *)&address)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    printf("PUSH 0x%02X ", address);
    int32_t value;
    if (!Uint8Array_getItems(&program->constantPool, address, 4, (uint8_t *)&value)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    Value_print(value);
    printf(" ");
    printLocation(program, instOffset);
    printf("\n");
    return instOffset + 2;
}

static int syscallInstruction(Program *program, int instOffset) {
    uint8_t subCode;
    if (!Uint8Array_getItem(&program->codeArray, instOffset + 1, &subCode)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    printf("SYSCALL 0x%02X ", subCode);
    printLocation(program, instOffset);
    printf("\n");
    if (subCode == 1) {
        return instOffset + 2;
    } else {
        return instOffset + 1;
    }
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
        case OP_NOP:
            printf("NOP ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_ADD:
            printf("ADD ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_SUB:
            printf("SUB ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_MUL:
            printf("MUL ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_DIV:
            printf("DIV ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_REM:
            printf("REM ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_STORE:
            return pushInstruction(program, instOffset);
        case OP_CALL:
            return instOffset + 2;
        case OP_RETURN:
            printf("RETURN ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
        case OP_RETURN_I:
            return instOffset + 1;
        case OP_SYSCALL:
            return syscallInstruction(program, instOffset);
        default:
            printf("unknown opcode 0x%02X ", opcode);
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
    }
}
