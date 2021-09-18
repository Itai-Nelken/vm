#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void exec(EMU_context *c, Instruction i) {
	int *sp=&(c->registers[SP]);
	int *pc=&(c->registers[PC]);
	switch(i) {
		case PUSH: // PUSH <value>
			c->stack[++*sp]=c->program[++*pc];
			break;
		case POP: // POP
			--*sp;
			break;
		case PEEK: // PEEK
			printf("%d\n", c->stack[*sp]);
			break;
		case ADD: { // ADD
			int a, b;
			a=c->stack[(*sp)--];
			b=c->stack[(*sp)--];
			c->stack[++*sp]=a+b;
			break;
		} // make a scope so variables can be defined
		case SUB: { // SUB
			int a, b;
			a=c->stack[(*sp)--];
			b=c->stack[(*sp)--];
			c->stack[++*sp]=b-a;
			break;
		}
		case MUL: { // MUL
			int a, b;
			a=c->stack[(*sp)--];
			b=c->stack[(*sp)--];
			c->stack[++*sp]=a*b;
			break;
		}
		case DIV: { // DIV
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
		case GET: // GET <register> (push the value to the stack)
			c->stack[++*sp]=c->registers[c->program[++*pc]];
			break;
		case JMP: { // JMP <pc value>
			int val=c->program[++*pc]-1; // has to be 1 less than what is requested because loop in emu.c -> run() increments it.
			*pc=val;
			break;
		}
		case NOP: // NOP
			break;
		case HLT: // HLT
		case END: // END
			c->isRunning=0;
			break;
		default:
			// unknkown instruction
			c->isRunning=0;
			break;
	}
}
