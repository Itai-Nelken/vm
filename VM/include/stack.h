#ifndef STACK_H
#define STACK_H
#include <stddef.h>

typedef struct stack_context {
    int *data; // the stack itself
    int *sp; // pointer to the stack pointer
    size_t dataSize;
} STACKcontext;

/******
 * Initialize a stack context. the stack pointer is external and it's memory address needs to be provided.
 * 
 * @param size The size of the stack (10 means a stack that can hold 10 values).
 * 
 * @return A pointer to a heap allocated stack context. you can free it with stackDestroy().
 ******/
STACKcontext *stackInit(size_t size, int *sp);

/******
 * Destroy an initialized stack context.
 * 
 * @param c The stack context to destroy.
 ******/
void stackDestroy(STACKcontext *c);

/******
 * Push a value to a stack.
 * 
 * @param c An initialized stack context.
 * @param data The value to push.
 * 
 * @return 0: success, 1: failure.
 ******/
int stackPush(STACKcontext *c, int data);

/******
 * Pop a value off a stack. the value popped is returned.
 * 
 * @param c An initialized stack context.
 * 
 * @return The value popped on success and -1 on failure (-1 might be returned on success if it's the value that was popped).
 ******/
int stackPop(STACKcontext *c);

/******
 * Get the stack head.
 * 
 * @param c An initialized stack context.
 * 
 * @return The stack head or -1 on failure (-1 might be returned on success if it's the stack head).
 ******/
int stackPeek(STACKcontext *c);

/******
 * Print the contents of the stack head to bottom.
 * 
 * @param c An initialized stack context.
 * 
 * @return 0: success, 1: failure.
 ******/
int stackDump(STACKcontext *c);

#endif // STACK_H
