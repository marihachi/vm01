#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "value.h"

static InstInfo *findInstInfo(Program *program, uint32_t offset) {
    InstInfo *ptr;
    uint32_t i = 0;
    while (i < program->metadata.length) {
        ptr = (InstInfo *)&program->metadata.ptr[sizeof(InstInfo) * i];
        if (ptr->addr == offset) {
            return ptr;
        }
        i++;
    }
    return NULL;
}

static void printLocation(Program *program, int instOffset) {
    InstInfo *info = findInstInfo(program, instOffset);
    if (info != NULL) {
        printf("(%d:%d)", info->line, info->column);
    }
}

static int storeInstruction(Program *program, int instOffset) {
    uint16_t address;
    if (!ByteArray_getItems(&program->code, instOffset + 1, (uint8_t *)&address, 2)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    printf("PUSH 0x%02X ", address);
    int16_t value;
    if (!ByteArray_getItems(&program->constantPool, address, (uint8_t *)&value, 2)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    printf("%d ", value);
    printLocation(program, instOffset);
    printf("\n");
    return instOffset + 3;
}

static int syscallInstruction(Program *program, int instOffset) {
    uint8_t subCode;
    if (!ByteArray_getItem(&program->code, instOffset + 1, &subCode)) {
        printf("ERROR: OUT_OF_RANGE_ACCESS\n");
        exit(1);
    }
    printf("SYSCALL 0x%02X ", subCode);
    printLocation(program, instOffset);
    printf("\n");
    return instOffset + 2;
}

void Debug_printProgram(Program *program) {
    printf("== BEGIN PROGRAM ==\n");
    uint32_t instOffset = 0;
    while (!END_OF_CODE(program, instOffset)) {
        instOffset = Debug_printInst(program, instOffset);
    }
    printf("== END PROGRAM ==\n");
}

int Debug_printInst(Program *program, int instOffset) {
    printf("0x%04X ", instOffset);

    uint8_t opcode;
    if (!ByteArray_getItem(&program->code, instOffset, &opcode)) {
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
            return storeInstruction(program, instOffset);
        case OP_STORE_Z:
            printf("STORE_Z ");
            printLocation(program, instOffset);
            printf("\n");
            return instOffset + 1;
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
