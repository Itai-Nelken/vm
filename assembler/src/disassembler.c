#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "disassembler.h"

const char *instructions[] = {
    "PUSH",   // 0
    "POP",    // 1
    "PEEK",   // 2
    "ADD",    // 3
    "SUB",    // 4
    "MUL",    // 5
    "DIV",    // 6
    "SET",    // 7
    "PSET",   // 8
    "GET",    // 9
    "MOV",    // 10
    "JMP",    // 11
    "JEQ",    // 12
    "JNE",    // 13
    "JLT",    // 14
    "JGT",    // 15
    "NOP",    // 16
    "HLT",    // 17
    "UNKNOWN" // 18
};
const char *instr2str(Instruction i) {
    switch(i) {
        case PUSH:
            return instructions[PUSH];
            break;
        case POP:
            return instructions[POP];
            break;
        case PEEK:
            return instructions[PEEK];
            break;
        case ADD:
            return instructions[ADD];
            break;
        case SUB:
            return instructions[SUB];
            break;
        case MUL:
            return instructions[MUL];
            break;
        case DIV:
            return instructions[DIV];
            break;
        case SET:
            return instructions[SET];
            break;
        case PSET:
            return instructions[PSET];
            break;
        case GET:
            return instructions[GET];
            break;
        case MOV:
            return instructions[MOV];
            break;
        case JMP:
            return instructions[JMP];
            break;
        case JEQ:
            return instructions[JEQ];
            break;
        case JNE:
            return instructions[JNE];
            break;
        case JLT:
            return instructions[JLT];
            break;
        case JGT:
            return instructions[JGT];
            break;
        case NOP:
            return instructions[NOP];
            break;
        case HLT:
            return instructions[HLT];
            break;
        default:
            return instructions[18];
    }
}

const char *registers[] = {
	"A",      // 0
	"B",      // 1
	"C",      // 2
	"D",      // 3
	"E",      // 4
	"F",      // 5
	"PC",     // 6
	"SP",     // 7
	"UNKNOWN" // 8
};
const char *reg2str(Register r) {
	switch(r) {
		case A: // 0
			return registers[A];
		case B: // 1
			return registers[B];
		case C: // 2
			return registers[C];
		case D: // 3
			return registers[D];
		case E: // 4
			return registers[E];
		case F: // 5
			return registers[F];
		case SP: // 6
			return registers[SP];
		case PC: // 7
			return registers[PC];
		default:
			return registers[8];
	}
}
int str2reg(const char *reg) {
    if(!strcasecmp(reg, "SP")) {
        return SP;
    } else if(!strcasecmp(reg, "PC")) {
        return PC;
    }
    switch(tolower(reg[0])) {
        case 'a':
            return A;
        case 'b':
            return B;
        case 'c':
            return C;
        case 'd':
            return D;
        case 'e':
            return E;
        case 'f':
            return F;
        default:
            return -1;
    }
}

void disassemble(FILE *in) {
    struct operation op;
    int exit=0;

    fread(&op, sizeof(struct operation), 1, in);
    if(op.instruction != -1) {
    	fprintf(stderr, "ERROR: unrecognized binary format!\n");
	return;
    }
    while(exit==0 && !feof(in)) {
        switch(op.instruction) {
            case S_START:
                printf("START:\n");
                break;
            case S_END:
                puts("END");
                exit=1;
                continue;
            case PUSH:
                printf("\t0x%X PUSH %d\n", PUSH, op.arg1);
                break;
            case POP:
                printf("\t0x%X POP\n", POP);
                break;
            case PEEK:
                printf("\t0x%X PEEK\n", PEEK);
                break;
            case ADD:
                printf("\t0x%X ADD\n", ADD);
                break;
            case SUB:
                printf("\t0x%X SUB\n", SUB);
                break;
            case MUL:
                printf("\t0x%X MUL\n", MUL);
                break;
            case DIV:
                printf("\t0x%X DIV\n", DIV);
                break;
            case SET:
                printf("\t0x%X SET %s %d\n", SET, reg2str(op.arg1), op.arg2);
                break;
            case PSET:
                printf("\t0x%X PSET %s\n", PSET, reg2str(op.arg1));
                break;
            case GET:
                printf("\t0x%X GET %s\n", GET, reg2str(op.arg1));
                break;
            case MOV:
                printf("\t0x%X MOV %s %s\n", MOV, reg2str(op.arg1), reg2str(op.arg2));
                break;
            case JMP:
                printf("\t0x%X JMP %d\n", JMP, op.arg1);
                break;
            case JEQ:
                printf("\t0x%X JEQ %d\n", JEQ, op.arg1);
                break;
            case JNE:
                printf("\t0x%X JNE %d\n", JNE, op.arg1);
                break;
            case JLT:
                printf("\t0x%X JLT %d\n", JLT, op.arg1);
                break;
            case JGT:
                printf("\t0x%X JGT %d\n", JGT, op.arg1);
                break;
            case NOP:
                printf("\t0x%X NOP\n", NOP);
                break;
            case HLT:
                printf("\t0x%X HLT\n", HLT);
                break;
            default:
                printf("\tUNKOWN\n");
                break;
        }
        fread(&op, sizeof(struct operation), 1, in);
    }
}
