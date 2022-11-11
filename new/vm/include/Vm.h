#ifndef VM_H
#define VM_H

#include <stdbool.h>
#include <stdint.h>

#define STACK_SIZE 256

typedef struct vm {
    bool is_running;
    uint32_t stack[STACK_SIZE];
    struct {
        uint16_t sp;
        uint16_t pc;
    } regs;
} Vm;

void vmInit(Vm *vm);
void vmFree(Vm *vm);
void vmExecute(Vm *vm);

#endif // VM_H
