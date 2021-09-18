#ifndef COMMON_H
#define COMMON_H

typedef enum instruction_e {
	PUSH, // 0, USAGE: PUSH <value> push a number to the stack
	POP, // 1, pop a number from the stack
	PEEK, // 2, print the head of the stack
	ADD, // 3, pop 2 values of the stack, add them, and push the result
	SET, // 4, USAGE: SET <reg> <val>
	GET, // 5, USAGE: GET <reg> pushes the value of <reg> to the stack.
	JMP, // 6, USAGE: JMP <pc val> jump to the PC value <pc val>
	HLT, // 7, end the program.
    END // 8, has to be at the end of every program, also ends it.
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
