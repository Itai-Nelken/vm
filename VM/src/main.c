#include <stdio.h>
#include "common.h"
#include "stack.h"
#include "registers.h"

int main(void) {
    REGScontext *regs=registersInit();
    STACKcontext *stack=stackInit(10, &(regs->SP));

    registersSet(regs, A, 10);
    registersSet(regs, B, 5);
    stackPush(stack, registersGet(regs, A));
    stackPush(stack, registersGet(regs, B));

    puts("--------");
    stackDump(stack);
    puts("--------");
    registersDump(regs);
    stackDestroy(stack);
    registersDestroy(regs);
    return 0;
}

/*
struct operation op;
    int exit=0;
    FILE *in=fopen("in.vm", "rb");

    // check for start symbol
    fread(&op, sizeof(struct operation), 1, in);
    if(op.instruction!=-1) {
        fprintf(stderr, "ERROR: unrecognized executable format!\n");
        return 1;
    }
    while(fread(&op, sizeof(struct operation), 1, in)!=0 && exit==0) {
        switch(op.instruction) {
            case PUSH:
                printf("PUSH %d\n", op.arg1);
                break;
            case PEEK:
                puts("PEEK");
                break;
            case ADD:
                puts("ADD");
                break;
            case S_END:
                exit=1;
                break;
            default:
                break;
        }
    }
*/
