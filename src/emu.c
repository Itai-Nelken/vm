#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "emu.h"

void progcpy(int *dest, int *src, int dest_size) {
    while(*src != END && dest_size-- != 0) {
        *dest++ = *src++;
    }
}

EMU_context *emu_init(int *prog) {
    EMU_context *new=malloc(sizeof(EMU_context));
    new->isRunning=1;
    if(prog!=NULL) {
        new->program_size=getProgSize(prog);
        new->program=malloc(new->program_size*sizeof(int));
        progcpy(new->program, prog, new->program_size);
    }

    return new;
}

void EMU_free(EMU_context *c) {
    free(c->program);
    free(c);
}

int getProgSize(int *prog) {
    int size;
    for(size=0; prog[size]!=END; size++);
    return size;
}

void run(int *prog) {
    EMU_context *context=emu_init(prog);
    int *pc=&(context->registers[PC]);
    for(*pc=0; *pc<getProgSize(prog) && context->isRunning != 0; ++*pc) {
        exec(context, prog[*pc]);
    }
    EMU_free(context);
}

void run_from_file(const char *filename) {
    int instruction;
    FILE *f=fopen(filename, "r");
    if(!f) {
        perror("run_from_file(): fopen()");
        return;
    }



    EMU_context *context=emu_init(NULL);
    while((instruction=fgetc(f))!=EOF) {
        if(context->isRunning==0) break;
        instruction = (char)instruction - '0';
        if(instruction==-38) continue;
        exec(context, instruction);
        printf("%d\n", instruction);
    }
    EMU_free(context);
}
