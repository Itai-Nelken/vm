#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "common.h"

// instruction names for instr2str()
const char *instrutions[] = {
	"PUSH",  // 0
	"POP",   // 1
	"PEEK",  // 2
	"ADD",   // 3
	"SUB",   // 4
	"MUL",   // 5
	"DIV",   // 6
	"SET",   // 7
	"PSET",  // 8
	"GET",   // 9
	"JMP",   // 10
	"NOP",   // 11
	"HLT",   // 12
	"END",   // 13
	"UNKOWN" // 14
};
const char *instr2str(Instruction i) {
	switch(i) {
		case PUSH:
			return instrutions[0];
		case POP:
			return instrutions[1];
		case PEEK:
			return instrutions[2];
		case ADD:
			return instrutions[3];
		case SUB:
			return instrutions[4];
		case MUL:
			return instrutions[5];
		case DIV:
			return instrutions[6];
		case SET:
			return instrutions[7];
		case PSET:
			return instrutions[8];
		case GET:
			return instrutions[9];
		case JMP:
			return instrutions[10];
		case NOP:
			return instrutions[11];
		case HLT:
			return instrutions[12];
		case END:
			return instrutions[13];
		default:
			return instrutions[14];
	}
}

const char *registers[] = {
	"A",     // 0
	"B",     // 1
	"C",     // 2
	"D",     // 3
	"E",     // 4
	"F",     // 5
	"PC",    // 6
	"SP",    // 7
	"UNKNOWN" // 8
};
const char *reg2str(Register r) {
	switch(r) {
		case A:
			return registers[0];
		case B:
			return registers[1];
		case C:
			return registers[2];
		case D:
			return registers[3];
		case E:
			return registers[4];
		case F:
			return registers[5];
		case PC:
			return registers[6];
		case SP:
			return registers[7];
		default:
			return registers[8];
	}
}

void exec(EMU_context *c, Instruction i) {
	// make pointers to the SP and PC registers (makes the code look cleaner).
	int *sp=&(c->registers[SP]);
	int *pc=&(c->registers[PC]);
	switch(i) {
		case PUSH: // PUSH <value>
			c->stack[++*sp]=c->program[++*pc];
			break;
		case POP: // DOESN'T print the value.
			--*sp;
			break;
		case PEEK: // prints the stack head.
			printf("%d\n", c->stack[*sp]);
			break;
		case ADD: { // make a scope so variables can be defined
			int a, b;
			a=c->stack[(*sp)--];
			b=c->stack[(*sp)--];
			c->stack[++*sp]=a+b;
			break;
		}
		case SUB: {
			int a, b;
			a=c->stack[(*sp)--];
			b=c->stack[(*sp)--];
			c->stack[++*sp]=b-a;
			break;
		}
		case MUL: {
			int a, b;
			a=c->stack[(*sp)--];
			b=c->stack[(*sp)--];
			c->stack[++*sp]=a*b;
			break;
		}
		case DIV: {
			int a, b;
			a=c->stack[(*sp)--];
			b=c->stack[(*sp)--];
			c->stack[++*sp]=b/a;
			break;
		}
		case SET: { // SET <register> <value>
			int reg=c->program[++*pc];
			c->registers[reg]=c->program[++*pc];
			break;
		}
		case PSET:
			c->registers[c->program[++*pc]]=c->stack[(*sp)--];
			break;
		case GET: // GET <register> (push the value to the stack)
			c->stack[++*sp]=c->registers[c->program[++*pc]];
			break;
		case JMP: { // JMP <pc value>
			int val=c->program[++*pc]-1; // has to be 1 less than what is requested because loop in emu.c -> run() increments it.
			*pc=val;
			break;
		}
		case NOP: // do nothing
			break;
		case HLT: // stop the program
		case END: // does the same as HLT
			c->isRunning=0;
			break;
		default:
			// unknkown instruction
			fprintf(stderr, "ERROR: unkown instruction '%d'!\npc=%d\nAborted execution\n", i, *pc);
			c->isRunning=0;
			break;
	}
}
