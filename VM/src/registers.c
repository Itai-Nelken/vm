#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "registers.h"

REGScontext *registersInit() {
    REGScontext *new=malloc(sizeof(REGScontext));
    return new;
}

void registersDestroy(REGScontext *c) {
    free(c);
}

int registersSet(REGScontext *c, Register r, int data) {
    switch(r) {
        case A:
            c->A=data;
            break;
        case B:
            c->B=data;
            break;
        case C:
            c->C=data;
            break;
        case D:
            c->D=data;
            break;
        case E:
            c->E=data;
            break;
        case F:
            c->F=data;
            break;
        case SP:
            c->SP=data;
            break;
        case PC:
            c->PC=data;
            break;
        default:
            return -1;
    }
    return 0;
}

int registersGet(REGScontext *c, Register r) {
    switch(r) {
        case A:
            return c->A;
        case B:
            return c->B;
        case C:
            return c->C;
        case D:
            return c->D;
        case E:
            return c->E;
        case F:
            return c->F;
        case SP:
            return c->SP;
        case PC:
            return c->PC;
        default:
            return -1;
    }
}

void registersDump(REGScontext *c) {
    printf("A: %d\nB: %d\nC: %d\nD: %d\nE: %d\nF: %d\nSP: %d\nPC: %d\n", c->A, c->B, c->C, c->D, c->E, c->F, c->SP, c->PC);
}
