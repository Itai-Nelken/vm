#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h> // for size_t

// TODO: keep track of all allocations and register an atexit() function
// to free it all.
// also keep track of free()'s using freem().

/***
 * Allocate SIZE bytes.
 * @param size The amount of bytes to allocate.
 * @return Pointer to the allocated block.
 ***/
void *allocm(size_t size);

/***
 * Change the size of a memory block allocated using allocm().
 * @param ptr A pointer to the old memory block.
 * @param size The new size.
 * @return A pointer to the enlarged memory block (could be a new one if there was no space to expand old one).
 ***/
void *reallocm(void *ptr, size_t size);

/***
 * Free memory allocated using allocm()
 * @param ptr Pointer to the memory block to free.
 ***/
void freem(void *ptr);

#endif // MEMORY_H
