#ifndef VM_H
#define VM_H
#include <pthread.h>
#include "common.h"
#include "Array.h"

typedef struct vm {
    int isRunning;
    pthread_mutex_t timer_register_mutex;
    int stack[STACK_SIZE];
    int registers[REG_COUNT];
    Array *program;
} VM;

/******
 * Initialize a VM context.
 * 
 * @return A pointer to a heap allocated initialized VM context.
 ******/
VM *vmInit();

/******
 * Destroy a VM context.
 * 
 * @param v The VM context to destroy.
 ******/
void vmDestroy(VM *v);

/******
 * Load a binary into a linked list.
 * 
 * @param binaryname The name of the binary to load.
 * @param program An initialized Array to hold the program.
 * 
 * @return 0: success 1: error
 ******/
int loadBinary(const char *binaryname, Array *program);

/******
 * Execute a loaded binary
 * 
 * @param vm A initialized VM context.
 ******/
void exec(VM *vm);

/******
 * Push 'data' to v's stack.
 * 
 * @param data The data to push.
 * @param v The VM context to use.
 * 
 * @return 0: success, 1: failure: stack is full.
 ******/
int stackPush(VM *v, int data);

/******
 * Pop the stack head
 * 
 * @param v The VM context to use.
 * 
 * @return The value popped or -1 on failure (-1 can be returned on success if it's the value that was in the stack).
 ******/
int stackPop(VM *v);

/******
 * Return the stack head
 * 
 * @param v The VM context to use.
 * 
 * @return The stack head or -1 on failure (-1 can be returned on success if it's the value that was in the stack).
 ******/
int stackPeek(VM *v);

/******
 * Print the contents of the stack.
 * 
 * @param v The VM context to use.
 * @param to where to print the output to.
 ******/
void/*int*/ stackDump(VM *v, FILE *to);

#endif // VM_H
