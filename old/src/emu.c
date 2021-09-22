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
		switch(buffer[i]) {
			case 'a':
			case 'A':
				prog[i]=JMP;
				break;
			case 'b':
			case 'B':
				prog[i]=MOV;
				break;
			case 'c':
			case 'C':
				prog[i]=NOP;
				break;
			case 'd':
			case 'D':
				prog[i]=HLT;
				break;
			case 'e':
			case 'E':
				prog[i]=END;
				break;
			default:
				x=buffer[i]-'0';
				prog[i]=x;
				break;
		}
	}
	run(prog);
	free(prog);
	free(buffer);
}