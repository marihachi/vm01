#include <stdio.h>
#include "disasm.h"
#include "vm.h"

VM vm;

void VM_init() {
}

void VM_free() {
}

static InterpretResult run() {
    // This function is written at a lower level because it is performance critical.
#define READ_BYTE() (*vm.ip++)
#define GET_CONSTANT(index) (vm.code->constantPool.ptr[index])
    Value constant;
FETCH_POINT:
#ifdef DEBUG_TRACE_EXECUTION
    disasm_disassembleInst(vm.code, (int)(vm.ip - vm.code->stream.ptr));
#endif
    switch (READ_BYTE()) {
        case OP_CONSTANT: goto OP_CONSTANT_POINT;
        case OP_RETURN: goto OP_RETURN_POINT;
    }
    return INTERPRET_RUNTIME_ERROR;

OP_CONSTANT_POINT:
    constant = GET_CONSTANT(READ_BYTE());
    Value_print(constant);
    printf("\n");
    goto FETCH_POINT;

OP_RETURN_POINT:
    return INTERPRET_OK;

#undef READ_BYTE
#undef GET_CONSTANT
}

InterpretResult VM_interpret(Code *code) {
    vm.code = code;
    vm.ip = vm.code->stream.ptr;
    return run();
}
