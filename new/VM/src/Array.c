#include <stdlib.h>
#include "common.h"
// relative path because the name 'memory.h' conflicts with libc memory.h
#include "../include/memory.h"
#include "Array.h"

void arrayPrintData(Data d) {
    printf("%d", d);
}

Array *newArray(size_t initial_size) {
    Array *a = allocm(sizeof(*a));
    a->current = -1;
    if(initial_size > 0) {
        a->data = allocm(sizeof(Data) * initial_size);
        a->has_allocated = true;
        a->size = initial_size;
    } else {
        a->data = NULL;
        a->has_allocated = false;
        a->size = 0;
    }
    return a;
}

void freeArray(Array *a) {
    if(a->has_allocated) {
        freem(a->data);
    }
    freem(a);
    a = NULL;
}

void arrayAppend(Array *a, Data value) {
    if(!a->has_allocated) {
        a->size = ARRAY_DEFAULT_INITIAL_SIZE;
        a->data = allocm(sizeof(Data) * a->size);
        a->has_allocated = true;
    }
    if(a->current + 1 > a->size) {
        a->size *= ARRAY_DEFAULT_STEP;
        a->data = reallocm(a->data, a->size);
    }
    a->data[++a->current] = value;
}

void arrayGet(Array *a, int index, Data *dest) {
    ASSERT(index >= 0);

    *dest = a->data[index];
}

void arrayDump(Array *a) {
    if(a->current == 0) {
        printf("[0]: %d\n", a->data[0]);
    } else if(a->current == -1) {
        LOGWARN("array is empty!");
    } else {
        for(int i = 0; i < a->current; i++) {
            printf("[%d]: ");
            arrayPrintData(a->data[i]);
            printf("\n");
        }
    }
}
