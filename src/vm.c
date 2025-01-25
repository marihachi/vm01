#include <stdio.h>
#include "debug.h"
#include "vm.h"

// スタックはアドレスが減る方向に伸びます。

VM vm;

void VM_init() {
    vm.sp = (uint8_t *)vm.stack + STACK_SIZE;
}

void VM_free() {
}

static void push(const uint8_t *ptr, int length) {
    uint8_t *stop = vm.sp;
    vm.sp -= length;
    uint8_t *wrPtr = vm.sp;
    while (wrPtr < stop) {
        *wrPtr = *ptr;
        ptr++;
        wrPtr++;
    }
}

static void pop(uint8_t *ptr, int length) {
    uint8_t *stop = vm.sp + length;
    while (vm.sp < stop) {
        *ptr = *vm.sp;
        ptr++;
        vm.sp++;
    }
}

static ExecResult run() {
    // This function is written at a lower level because it is performance critical.
#define READ_BYTE() (*vm.pc++)
#define CONSTANT_AT(index) (vm.program->constantPool.ptr[index])
    double doubleValue;
FETCH_POINT:
#ifdef DEBUG_TRACE_EXECUTION
    printf("[DEBUG] pc: ");
    Debug_printInst(vm.program, (int)(vm.pc - vm.program->codeArray.ptr));
    printf("[DEBUG] sp: 0x%04X\n", (int)(vm.sp - (uint8_t *)vm.stack));
#endif
    switch (READ_BYTE()) {
        case OP_CONSTANT: goto OP_CONSTANT_POINT;
        case OP_PRINT_NUM: goto OP_PRINT_NUM_POINT;
        case OP_RETURN: goto OP_RETURN_POINT;
    }
    return EXEC_RESULT_ERROR;

OP_CONSTANT_POINT:
    doubleValue = CONSTANT_AT(READ_BYTE());
    push((uint8_t *)&doubleValue, sizeof(doubleValue));
    goto FETCH_POINT;

OP_PRINT_NUM_POINT:
    pop((uint8_t *)&doubleValue, sizeof(doubleValue));
    printf("%g\n", doubleValue);
    goto FETCH_POINT;

OP_RETURN_POINT:
    return EXEC_RESULT_OK;

#undef READ_BYTE
#undef GET_CONSTANT
#undef PUSH_BYTE
#undef POP_BYTE
}

ExecResult VM_exec(Program *program) {
    vm.program = program;
    vm.pc = vm.program->codeArray.ptr;
    return run();
}
