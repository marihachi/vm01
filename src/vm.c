#include <stdio.h>
#include "debug.h"
#include "vm.h"

// スタックはアドレスが減る方向に伸びます。

VM vm;

void VM_init() {
    vm.sp = (uint8_t *)vm.stack + sizeof(vm.stack);
}

void VM_free() {
}

static void push(const uint8_t *src, int length) {
    // TODO: 境界チェック
    uint8_t *stop = vm.sp;
    vm.sp -= length;
    uint8_t *wrPtr = vm.sp;
    while (wrPtr < stop) {
        *wrPtr = *src;
        src++;
        wrPtr++;
    }
}

static void pop(uint8_t *out_ptr, int length) {
    // TODO: 境界チェック
    uint8_t *stop = vm.sp + length;
    while (vm.sp < stop) {
        *out_ptr = *vm.sp;
        out_ptr++;
        vm.sp++;
    }
}

void syscallHandler() {
#define READ_UINT8() (*vm.pc)
#define READ_UINT16() (*(uint16_t *)vm.pc)
#define FORWARD_8() (vm.pc++)
#define FORWARD_16() (vm.pc += 2)
    uint8_t code;
    int16_t value16;
    code = READ_UINT8();
    FORWARD_8();
    if (code == 1) {
        value16 = 0;
        pop((uint8_t *)&value16, 2);
        printf("%d\n", value16);
    }
#undef READ_UINT8
#undef READ_UINT16
#undef FORWARD_8
#undef FORWARD_16
}

static ExecResult run() {
    // This function is written at a lower level because it is performance critical.
#define READ_UINT8() (*vm.pc)
#define READ_UINT16() (*(uint16_t *)vm.pc)
#define FORWARD_8() (vm.pc++)
#define FORWARD_16() (vm.pc += 2)
    uint8_t opcode;
    int16_t value16, left16, right16;
    uint16_t addr;

FETCH_POINT:
#ifdef DEBUG_TRACE_EXECUTION
    uint8_t *debugPtr;
    printf("[DEBUG] stack(sp=0x%04X):", (int)(vm.sp - (uint8_t *)vm.stack));
    debugPtr = vm.sp;
    while (debugPtr < vm.stack + sizeof(vm.stack)) {
        printf(" %02X", *debugPtr);
        debugPtr++;
    }
    printf("\n");
    printf("[DEBUG] pc: ");
    Debug_printInst(vm.program, (int)(vm.pc - vm.program->code.ptr));
    printf("[DEBUG] ----\n");
#endif
    opcode = READ_UINT8();
    FORWARD_8();
    switch (opcode) {
        case OP_NOP: goto FETCH_POINT;
        case OP_ADD: goto OP_ADD_POINT;
        case OP_SUB: goto OP_SUB_POINT;
        case OP_MUL: goto OP_MUL_POINT;
        case OP_DIV: goto OP_DIV_POINT;
        case OP_REM: goto OP_REM_POINT;
        case OP_STORE: goto OP_STORE_POINT;
        case OP_STORE_Z: goto OP_STORE_Z_POINT;
        case OP_CALL: goto OP_CALL_POINT;
        case OP_RETURN: goto OP_RETURN_POINT;
        case OP_RETURN_I: goto OP_RETURN_I_POINT;
        case OP_SYSCALL: goto OP_SYSCALL_POINT;
    }
    return EXEC_RESULT_ERROR;

OP_ADD_POINT:
    pop((uint8_t *)&right16, 2);
    pop((uint8_t *)&left16, 2);
    value16 = left16 + right16;
    push((uint8_t *)&value16, 2);
    goto FETCH_POINT;

OP_SUB_POINT:
    pop((uint8_t *)&right16, 2);
    pop((uint8_t *)&left16, 2);
    value16 = left16 - right16;
    push((uint8_t *)&value16, 2);
    goto FETCH_POINT;

OP_MUL_POINT:
    pop((uint8_t *)&right16, 2);
    pop((uint8_t *)&left16, 2);
    value16 = left16 * right16;
    push((uint8_t *)&value16, 2);
    goto FETCH_POINT;

OP_DIV_POINT:
    pop((uint8_t *)&right16, 2);
    pop((uint8_t *)&left16, 2);
    value16 = left16 / right16;
    push((uint8_t *)&value16, 2);
    goto FETCH_POINT;

OP_REM_POINT:
    pop((uint8_t *)&right16, 2);
    pop((uint8_t *)&left16, 2);
    value16 = left16 % right16;
    push((uint8_t *)&value16, 2);
    goto FETCH_POINT;

OP_STORE_POINT:
    addr = READ_UINT16();
    FORWARD_16();
    if (!ByteArray_getItems(&vm.program->constantPool, addr, (uint8_t *)&value16, 2)) {
        return EXEC_RESULT_ERROR;
    }
    push((uint8_t *)&value16, 2);
    goto FETCH_POINT;

OP_STORE_Z_POINT:
    value16 = 0;
    push((uint8_t *)&value16, 2);
    goto FETCH_POINT;

OP_CALL_POINT:
    // TODO
    goto FETCH_POINT;

OP_RETURN_POINT:
    // TODO
    return EXEC_RESULT_OK;

OP_RETURN_I_POINT:
    pop((uint8_t *)&value16, 2);
    // TODO
    return EXEC_RESULT_OK;

OP_SYSCALL_POINT:
    syscallHandler();
    goto FETCH_POINT;

#undef READ_UINT8
#undef READ_UINT16
#undef FORWARD_8
#undef FORWARD_16
}

ExecResult VM_exec(Program *program) {
    vm.program = program;
    vm.pc = vm.program->code.ptr;
    return run();
}
