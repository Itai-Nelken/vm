#ifndef COMMON_H
#define COMMON_H

// Symbols
#define S_START -1
#define S_END -2

// Instructions
typedef enum instructions {
    PUSH, // 0  | 1 argument
    POP,  // 1  | 0 argument
    PEEK, // 2  | 0 argument
    ADD,  // 3  | 0 argument
    SUB,  // 4  | 0 argument
    MUL,  // 5  | 0 argument
    DIV,  // 6  | 0 argument
    SET,  // 7  | 2 argument
    PSET, // 8  | 1 argument
    GET,  // 9  | 1 argument
    MOV,  // 10 | 2 argument
    JMP,  // 11 | 1 argument
    JEQ,  // 12 | 1 argument
    JNE,  // 13 | 1 argument
    JLT,  // 14 | 1 argument
    JGT,  // 15 | 1 argument
    NOP,  // 16 | 0 argument
    HLT   // 17 | 0 argument
} Instruction;

// Registers
typedef enum registers {
    A, B, C, D, E, F, SP, PC,
    REG_COUNT
} Register;

struct operation {
    short instruction;
    int arg1, arg2;
};

#endif // COMMON_H
