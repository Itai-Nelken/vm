#include <string.h> // memset
#include <stdbool.h>
#include <stdint.h>
#include "common.h"
#include "OpCodes.h"
#include "Vm.h"

void vmInit(Vm *vm) {
    memset(vm->stack, 0, STACK_SIZE);
    vm->regs.sp = 0;
    vm->regs.pc = 0;
    vm->is_running = false;
}

void vmFree(Vm *vm) {
    memset(vm->stack, 0, STACK_SIZE);
    vm->regs.sp = 0;
    vm->regs.pc = 0;
    vm->is_running = false;
}

static OpCode next_op(Vm *vm) {
    // TODO: actually get the ops from the program.
    static OpCode ops[] = {
        ENCODE_OP_WITH_ARG(OP_PUSH_CONST, 42),
        ENCODE_OP(OP_HLT)
    };
    VERIFY(vm->regs.pc < sizeof(ops)/sizeof(ops[0]));
    return ops[vm->regs.pc++];
}

static void push(Vm *vm, uint32_t value) {
    VERIFY(vm->regs.sp < STACK_SIZE);
    vm->stack[vm->regs.sp++] = value;
}

static uint32_t pop(Vm *vm) {
    VERIFY(vm->regs.sp > 0);
    return vm->stack[--vm->regs.sp];
}

static void execute_op(Vm *vm, OpCode op) {
    switch(DECODE_OP(op)) {
        case OP_PUSH_CONST:
            push(vm, DECODE_ARG(op));
            break;
        case OP_POP:
            pop(vm);
            break;
        case OP_HLT:
            vm->is_running = false;
            break;
        default:
            UNREACHABLE();
    }
}

void vmExecute(Vm *vm) {
    vm->is_running = true;
    while(vm->is_running) {
        OpCode op = next_op(vm);
        execute_op(vm, op);
    }
}
