﻿#include <stdio.h>
#include "common.h"
#include "program.h"
#include "vm.h"

#ifdef DEBUG_PRINT_CODE
#include "debug.h"
#endif

int main(int argc, const char* argv[]) {
    Program program;
    Program_init(&program);

    if (argc < 2) {
        printf("no input file\n");
        return 1;
    }

    const char *filepath = argv[1];

    if (!Program_loadFile(&program, filepath)) {
        printf("failed to load the input file\n");
        return 1;
    }

#ifdef DEBUG_PRINT_CODE
    Debug_printProgram(&program);
    printf("\n");
#endif

    VM_init();
    ExecResult result = VM_exec(&program);
    VM_free();

    Program_free(&program);

    return (result == EXEC_RESULT_OK) ? 0 : 1;
}
