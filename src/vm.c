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

void syscallHandler() {
#define READ_BYTE() (*vm.pc++)
    uint8_t code, value;
    code = READ_BYTE();
    if (code == 1) {
        pop(&value, 1);
        printf("%d\n", value);
    }
#undef READ_BYTE
}

static ExecResult run() {
    // This function is written at a lower level because it is performance critical.
#define READ_UINT8() (*vm.pc)
#define READ_UINT16() (*(uint16_t *)vm.pc)
#define FORWARD_8() (vm.pc++)
#define FORWARD_16() (vm.pc += 2)
#define CONSTANT_AT(index) (vm.program->constantPool.ptr[index])
    uint8_t opcode, value, left, right;
    uint16_t addr;
FETCH_POINT:
#ifdef DEBUG_TRACE_EXECUTION
    printf("[DEBUG] pc: ");
    Debug_printInst(vm.program, (int)(vm.pc - vm.program->codeArray.ptr));
    printf("[DEBUG] sp: 0x%04X\n", (int)(vm.sp - (uint8_t *)vm.stack));
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
        case OP_CALL: goto OP_CALL_POINT;
        case OP_RETURN: goto OP_RETURN_POINT;
        case OP_RETURN_I: goto OP_RETURN_I_POINT;
        case OP_SYSCALL: goto OP_SYSCALL_POINT;
    }
    return EXEC_RESULT_ERROR;

OP_ADD_POINT:
    pop(&right, 1);
    pop(&left, 1);
    value = left + right;
    push(&value, 1);
    goto FETCH_POINT;

OP_SUB_POINT:
    pop(&right, 1);
    pop(&left, 1);
    value = left - right;
    push(&value, 1);
    goto FETCH_POINT;

OP_MUL_POINT:
    pop(&right, 1);
    pop(&left, 1);
    value = left * right;
    push(&value, 1);
    goto FETCH_POINT;

OP_DIV_POINT:
    pop(&right, 1);
    pop(&left, 1);
    value = left / right;
    push(&value, 1);
    goto FETCH_POINT;

OP_REM_POINT:
    pop(&right, 1);
    pop(&left, 1);
    value = left % right;
    push(&value, 1);
    goto FETCH_POINT;

OP_STORE_POINT:
    addr = READ_UINT16();
    FORWARD_16();
    value = CONSTANT_AT(addr);
    push(&value, 1);
    goto FETCH_POINT;

OP_CALL_POINT:
    // TODO
    goto FETCH_POINT;

OP_RETURN_POINT:
    // TODO
    return EXEC_RESULT_OK;

OP_RETURN_I_POINT:
    pop(&value, 1);
    // TODO
    return EXEC_RESULT_OK;

OP_SYSCALL_POINT:
    syscallHandler();
    goto FETCH_POINT;

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
