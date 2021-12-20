#include <stdio.h>
#include "common.h"
#include "disassembler.h"

const char *instr2str(OpCode instruction) {
    switch(instruction) {
        case OP_PUSH:
            return "PUSH";
        case OP_POP:
            return "POP";
        case OP_POPTO:
            return "POPTO";
        case OP_MOV:
            return "MOV";
        case OP_LD:
            return "LD";
        case OP_ST:
            return "ST";
        case OP_ADD:
            return "ADD";
        case OP_SUB:
            return "SUB";
        case OP_MUL:
            return "MUL";
        case OP_DIV:
            return "DIV";
        case OP_JMP:
            return "JMP";
        case OP_JEQ:
            return "JEQ";
        case OP_JNE:
            return "JNE";
        case OP_JGT:
            return "JGT";
        case OP_JLT:
            return "JLT";
        case OP_REQ:
            return "REQ";
        case OP_NOP:
            return "NOP";
        case OP_HLT:
            return "HLT";
        default:
            LOGERR("instr2str(0x%X): Unknown instruction!", instruction);
            break;
    }
    return "UNKNOWN";
}
