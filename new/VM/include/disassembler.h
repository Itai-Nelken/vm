#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "common.h"

/***
 * Return the name of instruction 'instruction' as a string.
 * @param instruction an instruction
 * @return A pointer to an immutable string containing the name of the instruction.
 ***/
const char *instr2str(OpCode instruction);

#endif // DISASSEMBLER_H
