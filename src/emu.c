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
	new->program_size=getProgSize(prog);
	new->program=malloc(new->program_size*sizeof(int));
	progcpy(new->program, prog, new->program_size);

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

void rm_all_chars(char* str, char c) { // magic!
    char *pr = str, *pw = str; // pr = read pointer, pw = write pointer
    while(*pr) {
        *pw = *pr++;
        pw += (*pw != c); // if true, 0. else 1
    }
    *pw = '\0';
}

void run_from_file(const char *filename) {
	long size=0;
	char *buffer;
	FILE *f=fopen(filename, "r");
	if(!f) {
		perror("run_from_file(): fopen()");
		return;
	}

	fseek(f, 0, SEEK_END);
	size=ftell(f);
	rewind(f);

	buffer=malloc(size*sizeof(char));
	fread(buffer, sizeof(char), size*sizeof(char), f);
	rm_all_chars(buffer, '\n');
	fclose(f);

	int x, *prog=malloc(strlen(buffer)*sizeof(int));
	for(int i=0; (size_t)i<strlen(buffer); i++) {
		x=buffer[i]-'0';
		if(x==-38) continue;
		prog[i]=x;
	}
	run(prog);
	free(prog);
	free(buffer);
}
