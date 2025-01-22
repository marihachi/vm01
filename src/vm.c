#include "vm.h"

VM vm;

void VM_init() {
}

void VM_free() {
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
    uint8_t inst;

FETCH_POINT:
    inst = READ_BYTE();
    switch (inst) {
        case OP_CONSTANT: goto OP_CONSTANT_POINT;
        case OP_RETURN: goto OP_RETURN_POINT;
    }
    return INTERPRET_RUNTIME_ERROR;

OP_CONSTANT_POINT:
    READ_BYTE();
    goto FETCH_POINT;

OP_RETURN_POINT:
    return INTERPRET_OK;

#undef READ_BYTE
}

InterpretResult VM_interpret(Code *code) {
    vm.code = code;
    vm.ip = vm.code->stream.ptr;
    return run();
}
