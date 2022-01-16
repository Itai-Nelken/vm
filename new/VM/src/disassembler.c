#include <stdio.h>
#include "common.h"
#include "disassembler.h"

static const char *instructions[] = {
    "PUSH", "POP", "POPTO",
    "MOV", "LD", "ST",
    "ADD", "SUB", "MUL", "DIV",
    "JMP", "JEQ", "JNE", "JGT", "JLT",
    "REQ", "NOP", "HLT"
};

const char *instr2str(OpCode instruction) {
    if(Instruction < INSTRUCTION_COUNT) {
        return instructions[instruction];
    } else {
        LOGERR("Unknown instruction 0x%X!", instruction);
        return "UNKNOWN";
    }
}
