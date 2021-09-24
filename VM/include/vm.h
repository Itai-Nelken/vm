#ifndef VM_H
#define VM_H
#include "common.h"
#include "list.h"

typedef struct vm {
    int stack[STACK_SIZE];
    int registers[REG_COUNT];
    programNode *progHead;
} VM;

VM *vmInit();
void vmDestroy();

int loadBinary(const char *binaryname, programNode **head);

int stackPush(VM *v, int data);
int stackPop(VM *v);
int stackPeek(VM *v);
int stackDump(VM *v);

#endif // VM_H
