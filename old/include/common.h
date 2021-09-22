#ifndef COMMON_H
#define COMMON_H

typedef enum instruction_e {
	PUSH, // 0, USAGE: PUSH <value> push a number to the stack
	POP,  // 1, pop a number from the stack
	PEEK, // 2, print the head of the stack
	ADD,  // 3, pop 2 values from the stack, add them, and push the result
	SUB,  // 4, pop 2 values from the stack, substract the LAST PUSHED from the FIRST PUSHED, and push the result. (push 5, push 2, sub == 5 - 2)
	MUL,  // 5, pop 2 values from the stack, multiply them, and push the result
	DIV,  // 6, pop 2 values from the stack, divide the FIRST PUSHED by the LAST PUSHED, and push the result. (push 10, push 2, div == 10 / 2)
	SET,  // 7, USAGE: SET <reg> <val>
	PSET, // 8, USAGE: PSET <reg> pop the stack head and store the value in <reg>.
	GET,  // 9, USAGE: GET <reg> pushes the value of <reg> to the stack.
	JMP,  // a (10), USAGE: JMP <pc val> jump to the PC value <pc val>
	MOV,  // b (11), USAGE: MOV <reg1> <reg2> move the value in <reg2> into <reg1>
	NOP,  // c (12), do nothing.
	HLT,  // d (13), end the program.
	END   // e (14), has to be at the end of every program, also ends it.
} Instruction;

typedef enum Regs_e {
	A, B, C, D, E, F, PC, SP, // A-F: general purpose registers, PC: program counter, SP: stack pointer
	REGISTER_NUM // will always be the number of registers
} Register;

typedef struct emu_s {
	int *program; // will hold the program for execution
	int program_size; // size of 'program'
	int stack[256]; // the stack.
	int registers[REGISTER_NUM]; // the registers
	int isRunning; // will be 1 if the program is running and 0 if not.
} EMU_context;

/******
 * Remove all occurences of a character from a string.
 * 
 * @param str A string containing the character you want to remove.
 * @param c The character you want to remove.
 ******/
void rm_all_chars(char* str, char c);

#endif // COMMON_H
