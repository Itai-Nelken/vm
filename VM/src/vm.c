#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "list.h"
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

    new->progHead=NULL;
    return new;
}

void vmDestroy(VM *v) {
    listDestroy(v->progHead);
    free(v);
}

int loadBinary(const char *binaryname, programNode **head) {
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
            fprintf(stderr, "ERROR: reached end of file bur no end symbol found!\n");
            return 1;
        }
        fread(&op, sizeof(struct operation), 1, f);
    }
    rewind(f);
    fread(&op, sizeof(struct operation), 1, f); // advance the file stream to the first instruction (after S_START).
    
    // load the binary into a linked list of the opcodes+operands
    for(;;) {
        fread(&op, sizeof(struct operation), 1, f);
        if(op.instruction==S_END) {
            break;
        }
        listInsert(head, &op);
    }
    fclose(f);
    return 0;
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
        fprintf(stderr, "stackPush(): stack is full!\n");
        return 1;
    }
    v->stack[++(v->registers[SP])]=data;
    return 0;
}

int stackPop(VM *v) {
    if(!stackEmpty(v)) {
        fprintf(stderr, "stackPop(): stack is empty!\n");
        return -1;
    }
    return v->stack[--(v->registers[SP])+1];
}

int stackPeek(VM *v) {
    if(!stackEmpty(v)) {
        fprintf(stderr, "stackPeek(): stack is empty!\n");
        return -1;
    }
    return v->stack[(v->registers[SP])];
}

int stackDump(VM *v) {
    if(!stackEmpty(v)) {
        fprintf(stderr, "stackDump(): stack is empty!\n");
        return 1;
    }
    for(int i=(v->registers[SP]); i>=0; --i) {
        printf("[%d] %d%s\n", i, v->stack[i], (v->registers[SP])==i ? " <-- SP" : "");
    }
    return 0;
}


