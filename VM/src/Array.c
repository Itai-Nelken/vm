#include <stdio.h>
#include <stdlib.h>
#include "Array.h"

Array *initArray(size_t initial_size, size_t step) {
    Array *new=malloc(sizeof(*new));
    new->data=malloc(sizeof((*new->data))*initial_size);
    new->size=initial_size;
    new->step=step;
    new->current=0;

    return new;
}

void destroyArray(Array *a) {
    free(a->data);
    free(a);
}

void arrayPush(Array *a, struct operation *op) {
    if(a->current == a->size) {
        a->size += a->step;
        a->data=realloc(a->data, sizeof(*(a->data))*a->size);
    }
    a->data[a->current].instruction=op->instruction;
    a->data[a->current].arg1=op->arg1;
    a->data[(a->current)++].arg2=op->arg2;
}

void arrayPop(Array *a) {
    a->current--;
}

int arrayGet(Array *a, uint index, struct operation *op) {
    if(index > a->size) {
        fprintf(stderr, "ERROR: arrayGet(): invalid index '%u'!\n", index);
        return 1;
    }
    op->instruction=a->data[index].instruction;
    op->arg1=a->data[index].arg1;
    op->arg2=a->data[index].arg2;
    return 0;
}

void dumpArray(Array *a) {
    for(uint index=0; index<(a->current); index++) {
        printf("[%u] %d %d %d\n", index, a->data[index].instruction, a->data[index].arg1, a->data[index].arg2);
    }
}
