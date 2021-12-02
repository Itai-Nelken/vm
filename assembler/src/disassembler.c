#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "disassembler.h"

const char *instr2str(Instruction i) {
    switch(i) {
        case PUSH:
            return "PUSH";
            break;
        case POP:
            return "POP";
            break;
        case PEEK:
            return "PEEK";
            break;
        case ADD:
            return "ADD";
            break;
        case SUB:
            return "SUB";
            break;
        case MUL:
            return "MUL";
            break;
        case DIV:
            return "DIV";
            break;
        case SET:
            return "SET";
            break;
        case PSET:
            return "PSET";
            break;
        case GET:
            return "GET";
            break;
        case MOV:
            return "MOV";
            break;
        case JMP:
            return "JMP";
            break;
        case JEQ:
            return "JEQ";
            break;
        case JNE:
            return "JNE";
            break;
        case JLT:
            return "JLT";
            break;
        case JGT:
            return "JGT";
            break;
        case NOP:
            return "NOP";
            break;
        case HLT:
            return "HLT";
            break;
        default:
            return "UNKNOWN";
    }
}

const char *reg2str(Register r) {
	switch(r) {
		case A:
			return "A";
		case B:
			return "B";
		case C:
			return "C";
		case D:
			return "D";
		case E:
			return "E";
		case F:
			return "F";
		case SP:
			return "SP";
		case PC:
			return "PC";
        case TM:
            return "TM";
		default:
			return "UNKNOWN";
	}
}

int str2reg(const char *reg) {
    if(!strcasecmp(reg, "SP")) {
        return SP;
    } else if(!strcasecmp(reg, "PC")) {
        return PC;
    } else if(!strcasecmp(reg, "TM")) {
        return TM;
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
    int exit = 0, pc = 0;

    fread(&op, sizeof(struct operation), 1, in);
    if(op.instruction != S_START) {
    	fprintf(stderr, "ERROR: unrecognized binary format!\n");
	    return;
    }
    while(exit == 0 && !feof(in)) {
        switch(op.instruction) {
            case S_START:
                printf("START:\n");
                pc--;
                break;
            case S_END:
                printf("END\n");
                exit = 1;
                continue;
            case PUSH:
                printf("\t%2d: 0x%X PUSH %d\n", pc, PUSH, op.arg1);
                break;
            case POP:
                printf("\t%2d: 0x%X POP\n", pc, POP);
                break;
            case PEEK:
                printf("\t%2d: 0x%X PEEK\n", pc, PEEK);
                break;
            case ADD:
                printf("\t%2d: 0x%X ADD\n", pc, ADD);
                break;
            case SUB:
                printf("\t%2d: 0x%X SUB\n", pc, SUB);
                break;
            case MUL:
                printf("\t%2d: 0x%X MUL\n", pc, MUL);
                break;
            case DIV:
                printf("\t%2d: 0x%X DIV\n", pc, DIV);
                break;
            case SET:
                printf("\t%2d: 0x%X SET R%s %d\n", pc, SET, reg2str(op.arg1), op.arg2);
                break;
            case PSET:
                printf("\t%2d: 0x%X PSET R%s\n", pc, PSET, reg2str(op.arg1));
                break;
            case GET:
                printf("\t%2d: 0x%X GET R%s\n", pc, GET, reg2str(op.arg1));
                break;
            case MOV:
                printf("\t%2d: 0x%X MOV R%s R%s\n", pc, MOV, reg2str(op.arg1), reg2str(op.arg2));
                break;
            case JMP:
                printf("\t%2d: 0x%X JMP %d\n", pc, JMP, op.arg1);
                break;
            case JEQ:
                printf("\t%2d: 0x%X JEQ %d\n", pc, JEQ, op.arg1);
                break;
            case JNE:
                printf("\t%2d: 0x%X JNE %d\n", pc, JNE, op.arg1);
                break;
            case JLT:
                printf("\t%2d: 0x%X JLT %d\n", pc, JLT, op.arg1);
                break;
            case JGT:
                printf("\t%2d: 0x%X JGT %d\n", pc, JGT, op.arg1);
                break;
            case NOP:
                printf("\t%2d: 0x%X NOP\n", pc, NOP);
                break;
            case HLT:
                printf("\t%2d: 0x%X HLT\n", pc, HLT);
                break;
            default:
                printf("\t%2d: UNKNOWN\n", pc);
                break;
        }
        fread(&op, sizeof(op), 1, in);
        pc++;
    }
}
