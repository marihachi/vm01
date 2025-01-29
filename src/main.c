#include <stdio.h>
#include "common.h"
#include "program.h"
#include "instInfo.h"
#include "vm.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    VM_init();
    Program program;
    InstInfo info;
    int constantAddr, codeAddr;

    Program_init(&program);

    codeAddr = Program_addByte(&program, OP_STORE);
    InstInfo_init(&info, codeAddr);
    InstInfo_setLocation(&info, 1, 1);
    Program_addInfo(&program, &info);
    constantAddr = Program_addConstant(&program, 4);
    Program_addByte(&program, constantAddr);

    codeAddr = Program_addByte(&program, OP_STORE);
    InstInfo_init(&info, codeAddr);
    InstInfo_setLocation(&info, 2, 1);
    Program_addInfo(&program, &info);
    constantAddr = Program_addConstant(&program, 1);
    Program_addByte(&program, constantAddr);

    codeAddr = Program_addByte(&program, OP_SUB);
    InstInfo_init(&info, codeAddr);
    InstInfo_setLocation(&info, 3, 1);
    Program_addInfo(&program, &info);

    codeAddr = Program_addByte(&program, OP_STORE);
    InstInfo_init(&info, codeAddr);
    InstInfo_setLocation(&info, 4, 1);
    Program_addInfo(&program, &info);
    constantAddr = Program_addConstant(&program, 2);
    Program_addByte(&program, constantAddr);

    codeAddr = Program_addByte(&program, OP_MUL);
    InstInfo_init(&info, codeAddr);
    InstInfo_setLocation(&info, 5, 1);
    Program_addInfo(&program, &info);

    // syscall: print
    codeAddr = Program_addByte(&program, OP_SYSCALL);
    InstInfo_init(&info, codeAddr);
    InstInfo_setLocation(&info, 6, 1);
    Program_addInfo(&program, &info);
    Program_addByte(&program, 1);

    codeAddr = Program_addByte(&program, OP_RETURN);
    InstInfo_init(&info, codeAddr);
    InstInfo_setLocation(&info, 7, 1);
    Program_addInfo(&program, &info);

    //Debug_printProgram(&program);
    //printf("\n");
    printf("Executing ...\n");
    ExecResult result = VM_exec(&program);
    printf("Result code %d.\n", result);
    VM_free();
    Program_free(&program);

    return 0;
}
