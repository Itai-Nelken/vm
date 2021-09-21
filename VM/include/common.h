#ifndef COMMON_H
#define COMMON_H

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
    A, B, C, D, E, F, SP, PC,
    REG_COUNT
} Register;

struct operation {
    short instruction;
    int arg1, arg2;
};

#endif // COMMON_H