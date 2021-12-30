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
#   define LOG(...) do { \
        printf("[%s(): LOG]: ", __func__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while(0)
#   define LOGWARN(...) do { \
        printf("[%s(): WARNING]: ", __func__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while(0)
#   define LOGERR(...) do { \
        printf("[%s(): ERROR]: ", __func__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while(0)
#   define LOGFATAL(exitStatus, ...) do { \
       fprintf(stderr, "[%s(): FATAL]: ", __func__); \
       fprintf(stderr, __VA_ARGS__); \
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
        fprintf(stderr, "\n%s:%d in function %s(): assertion '%s' failed!\n", __FILE__, __LINE__, __func__, #expr); \
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

typedef enum serivces {
    SR_WRITE = 0x0,
    SR_READ,
    SR_OPEN, SR_CLOSE,
    SR_EXIT,
    SERVICE_COUNT
} Service;

typedef enum runtime_errors {
    RERR_DIVISION_BY_ZERO = 0x1,
    RERR_STACK_OVERFLOW,
    RERR_STACK_UNDERFLOW,
    RERR_INVALID_ADDRESS,
    RERR_INSUFFICIENT_ARGS_TO_SERVICE,
    RERR_INVALID_REQUEST,
    RUNTIME_ERRORS_COUNT
} RuntimeError;

#endif // COMMON_H
