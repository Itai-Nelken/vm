#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include "common.h"

typedef struct scan_context {
    int Line;
    int Putback; // scanner uses integers to store characters because of EOF == -1
    FILE *infile;
} SCAN_context;

/******
 * Initialize A scanner context
 * 
 * @return A pointer to a heap allocated scanner context. make sure to free it with scan_destroy() when done with it.
 ******/
SCAN_context *scan_init();

/******
 * Destroy a scanner context
 * 
 * @param c An intialized scanner context.
 ******/
void scan_destroy(SCAN_context *c);

/******
 * Get the next character (using skip() so it isn't a space or newline etc.)
 * And populate a struct token according to it.
 * 
 * @param sc An initialized scanner context.
 * @param t A pointer to a struct token.
 * 
 * @return 0 if the token is valid or -1 if it is invalid.
 ******/
int scan(SCAN_context *sc, struct token *t);

/******
 * Scan a file and print the output.
 * 
 * @param c An initialized scanner context
 ******/
void scanfile(SCAN_context *c);

#endif // SCANNER_H
