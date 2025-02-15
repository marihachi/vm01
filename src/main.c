﻿#include <stdio.h>
#include "common.h"
#include "program.h"
#include "instInfo.h"
#include "vm.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    VM_init();
    Program program;
    int16_t value;

    Program_init(&program);

    // constant: 0x0000
    value = 700;
    ByteArray_addItems(&program.constantPool, (uint8_t *)&value, 2);

    // constant: 0x0002
    value = 400;
    ByteArray_addItems(&program.constantPool, (uint8_t *)&value, 2);

    // constant: 0x0004
    value = 5;
    ByteArray_addItems(&program.constantPool, (uint8_t *)&value, 2);

    uint8_t programCode[] = {
        0x19,             // 0x00000000: STORE_Z
        0x18, 0x00, 0x00, // 0x00000001: STORE 0x0000
        0x18, 0x02, 0x00, // 0x00000004: STORE 0x0002
        0x11,             // 0x00000007: SUB
        0x18, 0x04, 0x00, // 0x00000008: STORE 0x0004
        0x12,             // 0x0000000B: MUL
        0x11,             // 0x0000000C: SUB
        0x30, 0x01,       // 0x0000000D: SYSCALL 0x01
        0x28,             // 0x0000000F: RETURN
        0x00,             // 0x00000010: NOP
        0x00,             // 0x00000011: NOP
    };
    ByteArray_addItems(&program.code, programCode, sizeof(programCode));

    uint8_t metadata[] = {
        0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, // 0x00000000 (1:7)
        0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, // 0x00000001 (1:10)
        0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, // 0x00000004 (1:16)
        0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, // 0x00000007 (1:14)
        0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, // 0x00000008 (1:23)
        0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, // 0x0000000B (1:21)
        0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, // 0x0000000C (1:7)
        0x0D, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // 0x0000000D (1:1)
        0x0F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // 0x0000000F (2:1)
    };
    ByteArray_addItems(&program.metadata, metadata, sizeof(metadata));

    Debug_printProgram(&program);
    printf("\n");
    printf("Executing ...\n");
    ExecResult result = VM_exec(&program);
    printf("Result code %d.\n", result);
    VM_free();
    Program_free(&program);

    return 0;
}
