#ifndef COMMON_H
#define COMMON_H

/*** includes ***/
#include <stdbool.h>
#include <stdint.h>

/*** internal includes ***/
#include <stdio.h>
#include <stdlib.h>

/*** defines ***/
#define DEBUG_LOG
#define ARRAY_DEFAULT_INITIAL_SIZE 8
#define ARRAY_DEFAULT_STEP 2

/*** log macros ***/
#ifdef DEBUG_LOG
#   define LOG(fmt, ...) do { \
        printf("[LOG]: "); \
        printf(fmt, __VA_ARGS__); \
        printf("\n"); \
    } while(0)
#   define LOGWARN(fmt, ...) do { \
        printf("[WARNING]: "); \
        printf(fmt, __VA_ARGS__); \
        printf("\n"); \
    } while(0)
#   define LOGERR(fmt, ...) do { \
        printf("[ERROR]: "); \
        printf(fmt, __VA_ARGS__); \
        printf("\n"); \
    } while(0)
#   define LOGFATAL(exitStatus, fmt, ...) do { \
       fprintf(stderr, "[FATAL]: "); \
       fprintf(stderr, fmt, __VA_ARGS__); \
       fprintf(stderr, "\n"); \
       exit(exitStatus); \
    } while(0)
#else
#   define LOG
#   define LOGWARN
#   define LOGERR
#   define LOGFATAL
#endif // DEBUG_LOG

#define ASSERT(expr) do { \
    if(!(expr)) { \
        fprintf(stderr, "\n%s:%d in function %s(): assertion '%s' failed!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, #expr); \
        abort(); \
    } \
} while(0)

/*** other ***/
typedef enum opcodes {
    OP_PUSH = 0x0,
    OP_POP, OP_POPTO,
    OP_MOV,
    OP_LD,
    OP_ST,
    OP_ADD, OP_SUB, OP_MUL, OP_DIV,
    OP_AND, OP_OR, OP_XOR, OP_SHL, OP_SHR,
    OP_JMP, OP_JEQ, OP_JNE, OP_JGT, OP_JLT,
    OP_REQ,
    OP_NOP,
    OP_HLT,
    INSTRUCTION_COUNT
} OpCode;

typedef enum registers {
    A, B, C, D, E, F, // general purpose
    RQ, PC, SP,       // special
    T1, T2,           // timers
    FLAGS,            // well, flags...
    REGISTER_COUNT
} Register;

#endif // COMMON_H
