#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include "common.h"

/******
 * Return a pointer to a string containing the name of instruction i or 'UNKNOWN' if it doesn't exist.
 * 
 * @param i The instruction.
 * 
 * @return Pointer to the string containing the instruction name or 'UNKNOWN' if i is invalid.
 ******/
const char *instr2str(Instruction i);

/******
 * Return pointer to string containing the name of register r or 'UNKNOWN' if it doesn't exist.
 * 
 * @param r The register.
 * 
 * @return Pointer to the string containing the register name or 'UNKNOWN' if r is invalid.
 *****/
const char *reg2str(Register r);

/******
 * Return the enum value of the name of the register reg or -1 if it doesn't exist.
 * 
 * @param reg String containig the register name.
 * 
 * @return The value of the register in the enum.
 ******/
int str2reg(const char *reg);

/******
 * Disassemble a VM binary and print the output to stdout.
 * 
 * @param in An open file handle.
 ******/
void disassemble(FILE *in);

#endif // DISASSEMBLER_H
