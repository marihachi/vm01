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
    Program_addConstant(&program, (uint8_t *)&value, 2);

    // constant: 0x0002
    value = 400;
    Program_addConstant(&program, (uint8_t *)&value, 2);

    // constant: 0x0004
    value = 5;
    Program_addConstant(&program, (uint8_t *)&value, 2);

    uint8_t programCode[] = {
        0x06, 0x00, 0x00, // 0x00000000: STORE 0x0000
        0x06, 0x02, 0x00, // 0x00000003: STORE 0x0002
        0x02,             // 0x00000006: SUB
        0x06, 0x04, 0x00, // 0x00000007: STORE 0x0004
        0x03,             // 0x0000000A: MUL
        0x0A, 0x01,       // 0x0000000B: SYSCALL 0x01
        0x08,             // 0x0000000D: RETURN
        0x00,             // 0x0000000E: NOP
        0x00,             // 0x0000000F: NOP
    };
    ByteArray_addItems(&program.codeArray, programCode, sizeof(programCode));

    uint8_t metadata[] = {
        0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, // 0x00000000 (1:12)
        0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, // 0x00000003 (1:18)
        0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, // 0x00000006 (1:16)
        0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, // 0x00000007 (1:7)
        0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, // 0x0000000A (1:9)
        0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // 0x0000000B (1:1)
    };
    ByteArray_addItems(&program.infos, metadata, sizeof(metadata));

    Debug_printProgram(&program);
    printf("\n");
    printf("Executing ...\n");
    ExecResult result = VM_exec(&program);
    printf("Result code %d.\n", result);
    VM_free();
    Program_free(&program);

    return 0;
}
