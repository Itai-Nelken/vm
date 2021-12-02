#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

// symbols
#define S_START -1
#define S_END -2

typedef enum instructions {
    PUSH, 
    POP,
    PEEK,
    ADD,
    SUB,
    MUL,
    DIV,
    SET,
    PSET,
    GET,
    MOV,
    JMP,
    JEQ,
    JNE,
    JLT,
    JGT,
    NOP,
    HLT
} Instruction;

typedef enum registers {
    A, B, C, D, E, F, SP, PC, TM, // TM == timer
    REG_COUNT
} Register;

struct operation {
    short instruction;
    int arg1, arg2;
};

typedef enum status {
    SUCCESS,
    FAILURE,
    END_OF_FILE,
    END_OF_LINE,
    UNRECOGNIZED_TOKEN,
    OPEN_FILE_FAILURE,
    SYNTAX_ERROR
} Status;

#endif // COMMON_H
