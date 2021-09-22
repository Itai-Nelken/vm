#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "common.h"
#include "emu.h"
#include "cpu.h"

void rm_all_chars(char* str, char c) {
    char *pr = str, *pw = str; // pr = read pointer, pw = write pointer
    while(*pr) {
        *pw = *pr++;
        pw += (*pw != c); // if true, 0. else 1
    }
    *pw = '\0';
}

void disassemble(int *prog) {
	const char *instr;
	for(int i=0; i<getProgSize(prog); i++) {
		instr=instr2str(prog[i]);
		if(!strcmp(instr, "PUSH")||!strcmp(instr, "JMP")) {
			printf("%s %d\n", instr, prog[++i]);
		} else if(!strcmp(instr, "SET")) {
			int reg=prog[++i];
			printf("%s %s %d\n", instr, reg2str(reg), prog[++i]);
		} else if(!strcmp(instr, "MOV")) {
			int dest_reg=prog[++i];
			printf("%s %s %s\n", instr, reg2str(dest_reg), reg2str(prog[++i]));
		} else if(!strcmp(instr, "PSET")||!strcmp(instr, "GET")) {
			printf("%s %s\n", instr, reg2str(prog[++i]));
		} else {
			puts(instr);
		}
	}
}

void disassembleFromFile(const char *filename) {
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
				if(x==-38) continue;
				prog[i]=x;
				break;
		}
	}
	disassemble(prog);
	free(prog);
	free(buffer);
}

int program[] = {
	SET, A, 5,
	SET, B, 6,
	GET, A,
	GET, B,
	ADD,
	PEEK,
	PUSH, 9,
	ADD,
	PEEK,
	POP,
	END
}; // output: 11\n20

struct option long_options[] = {
	{"disassemble", required_argument, NULL, 'd'},
	{"help", no_argument, NULL, 'h'},
	{0, 0, NULL, 0}
};

int main(int argc, char **argv) {
	if(argc<2) {
		fprintf(stderr, "ERROR: insufficient arguments provided!\nUse \"--help\" argument for help.\n");
		return 1;
	}
	
	int opt;
	opt=getopt_long(argc, argv, "d:h", long_options, NULL);
	if(opt!=-1) {
		switch(opt) {
			case 'd':
				disassembleFromFile(optarg);
				break;
			case 'h':
				printf("USAGE: %s [-h|-d <vm binary>] <vm binary>\n", argv[0]);
				break;
			default:
				break;
		}
	} else {
		run_from_file(argv[1]);
	}

	return 0;
}
