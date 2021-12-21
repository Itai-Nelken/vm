#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h> // for size_t
#include "common.h"

// change arrayPrintData() when changing type.
typedef int Data;

/***
 * Print the array Data type correctly.
 * @param d The value to print.
 ***/
void arrayPrintData(Data d);

typedef struct array {
    Data *data;
    size_t size;
    int current; // points to CURRENT element, not next one.
    bool has_allocated;
} Array;

/***
 * Create a new array.
 * @param initial_size The initial size of the array. can be 0.
 * @return A pointer to an initialized heap allocated array.
 ***/
Array *newArray(size_t initial_size);

/***
 * Free an array.
 * @param a An array to free. NULL will be assigned to it.
 ***/
void freeArray(Array *a);

/***
 * Append a value to an array.
 * @param a An initialized array.
 * @param value The value to append.
 ***/
void arrayAppend(Array *a, Data value);

/***
 * Get the value at an index of the array.
 * @param a An initialized array.
 * @param index The index of the value.
 * @param dest A pointer to where to put the value.
 ***/
void arrayGet(Array *a, int index, Data *dest);

/***
 * Utility macro to get the last element in an array.
 * @param a A pointer to an initialized array.
 * @param dest A pointer to where to put the value.
 ***/
#define arrayGetLastElement(a, dest) arrayGet(a, a->current, dest)

/***
 * Dump the contents of an array.
 * @param a An initialized array.
 ***/
void arrayDump(Array *a);

#endif // ARRAY_H
