#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "Array.h"
#include "vm.h"

VM *vmInit() {
    VM *new=malloc(sizeof(VM));

    // zero all registers
    for(int reg=0; reg<REG_COUNT; reg++) {
        new->registers[reg]=0;
    }
    // set the stack pointer to -1 (stack empty)
    new->registers[SP]=-1;

    // zero the stack
    for(int i=0; i<STACK_SIZE; i++) {
        new->stack[i]=0;
    }

    new->isRunning=1;
    new->program=initArray(16, 8);
    return new;
}

void vmDestroy(VM *v) {
    destroyArray(v->program);
    free(v);
}

int loadBinary(const char *binaryname, Array *program) {
    struct operation op;
    FILE *f=fopen(binaryname, "rb");
    if(!f) {
        perror("loadBinary(): fopen()");
        return 1;
    }
    fread(&op, sizeof(struct operation), 1, f);
    if(op.instruction!=S_START) {
        fprintf(stderr, "ERROR: unknown binary format!\n");
        return 1;
    }
    while(op.instruction!=S_END) {
        if(feof(f)) {
            fprintf(stderr, "ERROR: reached end of file but no end symbol found!\n");
            return 1;
        }
        fread(&op, sizeof(struct operation), 1, f);
    }
    rewind(f);
    fread(&op, sizeof(struct operation), 1, f); // advance the file stream to the first instruction (after S_START).
    
    // load the binary into a dynamic array of the opcodes+operands
    for(;;) {
        fread(&op, sizeof(struct operation), 1, f);
        if(op.instruction==S_END) {
            break;
        }
        arrayPush(program, &op);
    }
    fclose(f);
    return 0;
}


static const char *instr2str(Instruction i) {
    switch(i) {
        case PUSH: return "PUSH";
        case POP: return "POP";
        case PEEK: return "PEEK";
        case ADD: return "ADD";
        case SUB: return "SUB";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case SET: return "SET";
        case PSET: return "PSET";
        case GET: return "GET";
        case MOV: return "MOV";
        case JMP: return "JMP";
        case JEQ: return "JEQ";
        case JNE: return "JNE";
        case JGT: return "JGT";
        case NOP: return "NOP";
        case HLT: return "HLT";
        default:
            break;
    }
    return "UNKNOWN";
}

static const char *reg2str(Register r) {
    switch(r) {
        case A: return "A";
        case B: return "B";
        case C: return "C";
        case D: return "D";
        case E: return "E";
        case F: return "F";
        case SP: return "SP";
        case PC: return "PC";
        case TM: return "TM";
        default:
            break;
    }
    return "UNKNOWN";
}

static void dumpRegisters(VM *vm, FILE *to) {
    for(int i=0; i<REG_COUNT; i++) {
        fprintf(to, "Register %s contains: %d\n", reg2str(i), vm->registers[i]);
    }
}

void runtimeError(VM *vm, struct operation *op, const char *message, int exitcode) {
    fprintf(stderr, "\033[1;31mRUNTIME ERROR!\033[0m\n=============\n");
    fprintf(stderr, "At instruction: 0x%X (%s), operands: %d, %d:\n", op->instruction, instr2str(op->instruction), op->arg1, op->arg2);
    fprintf(stderr, "Error message: %s\n", message);
    fprintf(stderr, "\nREGISTER DUMP\n=============\n");
    dumpRegisters(vm, stderr);
    fprintf(stderr, "\nSTACK DUMP\n==========\n");
    stackDump(vm, stderr);

    // clean up
    vmDestroy(vm);
    exit(exitcode);
}

static void eval(VM *vm, struct operation *op) {
    switch(op->instruction) {
        case PUSH:
            stackPush(vm, op->arg1);
            break;
        case POP:
            stackPop(vm);
            break;
        case PEEK:
            printf("%d\n", stackPeek(vm));
            break;
        case ADD:
            stackPush(vm, stackPop(vm)+stackPop(vm));
            break;
        case SUB: {
            int a=stackPop(vm);
            stackPush(vm, stackPop(vm)-a);
            break;
        }
        case MUL:
            stackPush(vm, stackPop(vm)*stackPop(vm));
            break;
        case DIV: {
            int a=stackPop(vm);
	    if(a == 0) {
		runtimeError(vm, op, "division by zero!", 1);
	    }
            stackPush(vm, stackPop(vm)/a);
            break;
        }
        case SET:
            vm->registers[op->arg1]=op->arg2;
            break;
        case PSET:
            vm->registers[op->arg1]=stackPop(vm);
            break;
        case GET:
            stackPush(vm, vm->registers[op->arg1]);
            break;
        case MOV:
            vm->registers[op->arg1]=vm->registers[op->arg2];
            break;
        case JMP:
            vm->registers[PC]=op->arg1-1; // -1 because main loop increments it
            break;
        case JEQ:
            if(stackPop(vm) == stackPop(vm)) {
                vm->registers[PC]=op->arg1-1;
            }
            break;
        case JNE:
            if(stackPop(vm) != stackPop(vm)) {
                vm->registers[PC]=op->arg1-1;
            }
            break;
        case JLT: {
            int a=stackPop(vm);
            if(stackPop(vm) < a) {
                vm->registers[PC]=op->arg1-1;
            }
            break;
        }
        case JGT: {
            int a=stackPop(vm);
            if(stackPop(vm) > a) {
                vm->registers[PC]=op->arg1-1;
            }
            break;
        }
        case NOP:
            break;
        case HLT:
            printf("Program halted\n");
            vm->isRunning=0;
            break;
        default:
	    runtimeError(vm, op, "Unknown OpCode!", 1);
	    // not reached
            break;
    }
}

void timerTick(VM *vm) {
    if(vm->registers[TM] > 0) vm->registers[TM]--;
}

void exec(VM *vm) {
    int *pc = &(vm->registers[PC]);
    for(; *pc < (int)vm->program->current && vm->isRunning != 0; (*pc)++) {
        eval(vm, &(vm->program->data[*pc]));
        timerTick(vm);
    }
}

// 0: full, 1: not full
static int stackFull(VM *v) {
    return v->registers[SP]+1 > STACK_SIZE ? 0 : 1;
}

// 0: empty, 1: not empty
static int stackEmpty(VM *v) {
    return v->registers[SP] < 0 ? 0 : 1;
}

int stackPush(VM *v, int data) {
    if(!stackFull(v)) {
        //fprintf(stderr, "stackPush(): stack is full!\n");
        runtimeError(v, &(v->program->data[v->registers[PC]]), "stack is full!", 1);
        return 1;
    }
    v->stack[++(v->registers[SP])]=data;
    return 0;
}

int stackPop(VM *v) {
    if(!stackEmpty(v)) {
        //fprintf(stderr, "stackPop(): stack is empty!\n");
        runtimeError(v, &(v->program->data[v->registers[PC]]), "stack is empty!", 1);
        return -1; // unreachable
    }
    return v->stack[--(v->registers[SP])+1];
}

int stackPeek(VM *v) {
    if(!stackEmpty(v)) {
        //fprintf(stderr, "stackPeek(): stack is empty!\n");
        runtimeError(v, &(v->program->data[v->registers[PC]]), "stack is empty!", 1);
	return -1; // unreachable
    }
    return v->stack[(v->registers[SP])];
}

void /*int*/ stackDump(VM *v, FILE *to) {
    if(!stackEmpty(v)) {
        fprintf(to, "[EMPTY]\n");
        //fprintf(stderr, "stackDump(): stack is empty!\n");
        //return 1;
    }
    for(int i=(v->registers[SP]); i>=0; --i) {
        fprintf(to, "[%d] %d%s\n", i, v->stack[i], (v->registers[SP])==i ? " <-- SP" : "");
    }
    //return 0;
}
