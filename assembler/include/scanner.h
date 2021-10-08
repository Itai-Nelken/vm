#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>

enum tokens {
    T_INSTR, T_REG, T_INT
};

struct token {
    int token;
    int value;
};

typedef struct scan_context {
    FILE *infile;
    int wasNewLine; // will be 1 if the scanner encountered a newline and will be set to zero the 2nd time the scanner is called after being set to 1
    unsigned int infileLine;
    char buffer[200];
    size_t buffer_size;
} SCANNERcontext;

/******
 * Initialize a scanner context. you should free the context with scannerDestroy() when done with it.
 * 
 * @return A pointer to a malloc()ed scanner context.
 ******/
SCANNERcontext *scannerInit();

/******
 * Destroy a scanner context (free() it)
 * 
 * @param context An initialized scanner context to destroy.
 ******/
void scannerDestroy(SCANNERcontext *context);

// 0: success.
// 1: end of file.
// 2: unrecognized token.
// 3: end of line/newline.

/******
 * Get the next token from the file.
 * 
 * @param context An initialized scanner context.
 * @param t A struct token to populate.
 * 
 * @return 0: success. 1: end of file. 2: unrecognized token. 3: end of line/newline.
 * 2 is the only error.
 ******/
int nextToken(SCANNERcontext *context, struct token *t);

#endif // SCANNER_H
