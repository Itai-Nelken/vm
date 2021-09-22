#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

STACKcontext *stackInit(size_t size, int *sp) {
    STACKcontext *new=malloc(sizeof(STACKcontext));
    new->data=calloc(size, sizeof(int));
    new->dataSize=size;
    *sp=-1;
    new->sp=sp;
    return new;
}
void stackDestroy(STACKcontext *c) {
    free(c->data);
    free(c);
}

// 0: full, 1: not full
int stackFull(STACKcontext *c) {
    return *(c->sp)+1 > c->dataSize ? 0 : 1;
}

// 0: empty, 1: not empty
int stackEmpty(STACKcontext *c) {
    return *(c->sp)<0 ? 0 : 1;
}

int stackPush(STACKcontext *c, int data) {
    if(!stackFull(c)) {
        fprintf(stderr, "stackPush(): stack is full!\n");
        return 1;
    }
    c->data[++*(c->sp)]=data;
    return 0;
}

int stackPop(STACKcontext *c) {
    if(!stackEmpty(c)) {
        fprintf(stderr, "stackPop(): stack is empty!\n");
        return -1;
    }
    return c->data[--*(c->sp)+1];
}

int stackPeek(STACKcontext *c) {
    if(!stackEmpty(c)) {
        fprintf(stderr, "stackPeek(): stack is empty!\n");
        return -1;
    }
    return c->data[*(c->sp)];
}

int stackDump(STACKcontext *c) {
    if(!stackEmpty(c)) {
        fprintf(stderr, "stackDump(): stack is empty!\n");
        return 1;
    }
    for(int i=*(c->sp); i>=0; --i) {
        printf("[%d] %d%s\n", i, c->data[i], *(c->sp)==i ? " <-- SP" : "");
    }
    return 0;
}
