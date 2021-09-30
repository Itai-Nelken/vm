#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include "common.h"

typedef struct array {
    struct operation *data;
    size_t size, current, step;
} Array;

/******
 * Initialize a Dynamic array.
 * 
 * @param initial_size The initial size of the array.
 * @param step The amount of cells to add in each grow operation.
 * 
 * @return Pointer to a heap allocated Array context.
 ******/
Array *initArray(size_t initial_size, size_t step);

/******
 * free() an Array context.
 * 
 * @param a An initialized Array context to free()
 ******/
void destroyArray(Array *a);

/******
 * Add a value to the top of the array.
 * 
 * @param a An initialized Array context.
 * @param value The value to push
 *****/
void arrayPush(Array *a, struct operation *op);

/******
 * "remove" the last value pushed. The value is still there but will be overwritten in the next push.
 * 
 * @param a An initialized Array context.
 *****/
void arrayPop(Array *a);

/******
 * Get the value in index 'index' of array 'a'.
 * 
 * @param a An initialized Array context.
 * @param index The index of the array to get the value from.
 * @param op A pointer to a struct operation to populate.
 * 
 * @return 0: success, 1: failure (index doesn't exist).
 *****/
int arrayGet(Array *a, uint index, struct operation *op);

/******
 * Dump the contents of an Array
 * 
 * @param a An array to dump it's contents.
 ******/
void dumpArray(Array *a);

#endif // ARRAY_H
