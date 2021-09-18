#ifndef COMMON_H
#define COMMON_H

typedef enum instruction_e {
	PUSH, // 0, USAGE: PUSH <value> push a number to the stack
	POP, // 1, pop a number from the stack
	PEEK, // 2, print the head of the stack
	ADD, // 3, pop 2 values from the stack, add them, and push the result
	SUB, // 4, pop 2 values from the stack, substract the LAST PUSHED from the FIRST PUSHED, and push the result. (push 5, push 2, sub == 5 - 2)
	MUL, // 5, pop 2 values from the stack, multiply them, and push the result
	DIV, // 6, pop 2 values from the stack, divide the FIRST PUSHED by the LAST PUSHED, and push the result. (push 10, push 2, div == 10 / 2)
	SET, // 7, USAGE: SET <reg> <val>
	GET, // 8, USAGE: GET <reg> pushes the value of <reg> to the stack.
	JMP, // 9, USAGE: JMP <pc val> jump to the PC value <pc val>
	NOP, // a (10), do nothing.
	HLT, // b (11), end the program.
	END // c (12), has to be at the end of every program, also ends it.
} Instruction;

typedef enum Regs_e {
	A, B, C, D, E, F, PC, SP,
	REGISTER_NUM // will always be the number of registers
} Register;

typedef struct emu_s {
	int *program;
	int program_size;
	int stack[256];
	int registers[REGISTER_NUM];
	int isRunning;
} EMU_context;

#endif // COMMON_H
