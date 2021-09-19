#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower()
#include <unistd.h> // getopt()

#define ERROR(R, ...) do {            \
		fprintf(stderr, __VA_ARGS__); \
		exit(R);                      \
	} while(0);

int str2reg(char *r) {
	switch(tolower(r[0])) {
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		case 'd':
			return 3;
		case 'e':
			return 4;
		case 'f':
			return 5;
	}
	if(!strcasecmp(r, "PC")) {
		return 6;
	} else if(!strcasecmp(r, "SP")) {
		return 7;
	} else {
		return -1;
	}
}

int assemble(const char *infile, const char *outfile) {
	int ret_val=0, was_end=0;
	char buffer[100]={0}, *bp;
	const char *separator=" ";
	unsigned int line=0;
	FILE *in, *out;

	in=fopen(infile, "r");
	if(!in) ERROR(1, "ERROR: fopen(\"%s\", \"r\") failed!\n", infile);
	out=fopen(outfile, "w");
	if(!out) ERROR(1, "ERROR: fopen(\"%s\", \"w\") failed!\n", outfile);

	while(fgets(buffer, 100, in)!=NULL) {
		line++;
		if(buffer[0]=='\n') continue;
		buffer[strcspn(buffer, "\n")]=0; // strcspn() returns the amount of characters until its 2nd argument ('\n' in this case)
		
		bp=strtok(buffer, separator);
		if(bp!=NULL) {
			
			if(!strcmp(bp, ";")) { // comments
				continue;
			} else if(!strcasecmp(bp, "POP")) { // no argument instructions
				fprintf(out, "1");
				continue;
			} else if(!strcasecmp(bp, "PEEK")) {
				fprintf(out, "2");
				continue;
			} else if(!strcasecmp(bp, "ADD")) {
				fprintf(out, "3");
				continue;
			} else if(!strcasecmp(bp, "SUB")) {
				fprintf(out, "4");
				continue;
			} else if(!strcasecmp(bp, "MUL")) {
				fprintf(out, "5");
				continue;
			} else if(!strcasecmp(bp, "DIV")) {
				fprintf(out, "6");
				continue;
			} else if(!strcasecmp(bp, "NOP")) {
				fprintf(out, "b");
				continue;
			} else if(!strcasecmp(bp, "HLT")) {
				fprintf(out, "c");
				continue;
			} else if(!strcasecmp(bp, "END")) {
				was_end=1;
				fprintf(out, "d");
				continue;
			} else if(!strcasecmp(bp, "PUSH")) { // single argument instructions
				bp=strtok(NULL, separator);
				fprintf(out, "0%d", atoi(bp));
				continue;
			} else if(!strcasecmp(bp, "JMP")) {
				bp=strtok(NULL, separator);
				fprintf(out, "a%d", atoi(bp));
				continue;
			} else if(!strcasecmp(bp, "PSET")) {
				bp=strtok(NULL, separator);
				int reg=str2reg(bp);
				if(reg==-1) {
					fprintf(stderr, "ERROR: register '%s' doesn't exist!\n", bp);
					ret_val=1;
					goto cleanup;
				}
				fprintf(out, "8%d", reg);
				continue;
			} else if(!strcasecmp(bp, "GET")) {
				bp=strtok(NULL, separator);
				int reg=str2reg(bp);
				if(reg==-1) {
					fprintf(stderr, "ERROR: register '%s' doesn't exist!\n", bp);
					ret_val=1;
					goto cleanup;
				}
				fprintf(out, "9%d", reg);
			} else if(!strcasecmp(bp, "SET")) { // 2 argument instructions
				bp=strtok(NULL, separator);
				int reg=str2reg(bp);
				bp=strtok(NULL, separator);
				fprintf(out, "7%d%d", reg, atoi(bp));
			} else {
				fprintf(stderr, "ERROR: unknown instruction \"%s\" in line %d!\n", bp, line);
				ret_val=1;
				goto cleanup;
			}
		}
	}

	if(was_end==0) {
		fprintf(out, "d\n");
	}

cleanup:
	fclose(out);
	fclose(in);
	if(ret_val==1) remove(outfile);

	return ret_val;
}


int main(int argc, char **argv) {
	if(argc < 2) ERROR(1, "ERROR: no arguments provided!\n");
	int opt, ret_val=0;
	char *outfile=NULL, *infile=malloc(strlen(argv[1])*sizeof(char)+1);
	strncpy(infile, argv[1], strlen(argv[1])*sizeof(char)+1);
	
	while((opt=getopt(argc, argv, "o:h")) != -1) {
		switch(opt) {
			case 'h':
				printf("USAGE %s <infile> [-o|h|v]\n  -o <outfile> : name to use for output file, default is 'as.out.vm'.\n  -h : this help.\n", argv[0]);
				ret_val=1;
				goto clean;
			case 'o':
				outfile=optarg;
				break;
			default:
				ret_val=1;
				goto clean;
		}
	}

	if(outfile==NULL) {
		ret_val=assemble(infile, "as.out.vm");
	} else {
		ret_val=assemble(infile, outfile);
	}
clean:
	free(infile);
	return ret_val;
}

// PUSH, // 0 PUSH <value>
// POP,  // 1
// PEEK, // 2
// ADD,  // 3
// SUB,  // 4
// MUL,  // 5
// DIV,  // 6
// SET,  // 7 SET <reg> <val>
// PSET, // 8 PSET <reg>
// GET,  // 9 GET <reg>
// JMP,  // a JMP <pc val>
// NOP,  // b
// HLT,  // c
// END   // d

// A,  // 0
// B,  // 1
// C,  // 2
// D,  // 3
// E,  // 4
// F,  // 5
// PC, // 6
// SP  // 7
