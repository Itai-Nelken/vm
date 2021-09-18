#ifndef CPU_H
#define CPU_H
#include "common.h"

/******
 * execute an instruction.
 * 
 * @param t An initialized emulator context (EMU_context). The values of its members will be changed
 * @param i The instruction to execute.
 ******/
void exec(EMU_context *c, Instruction i);

/******
 * Return a pointer to a string containing the name of the instruction.
 * 
 * @param i An instruction opcode.
 * 
 * @return A pointer to a const char* containing the instruction name.
 ******/
const char *instr2str(Instruction i);

/******
 * Return a pointer to a string containing the name of the register.
 * 
 * @param r A Register number (see enum Regs_e).
 * 
 * @return A pointer to a const char* containing the Register name.
 ******/
const char *reg2str(Register r);

#endif // CPU_H
