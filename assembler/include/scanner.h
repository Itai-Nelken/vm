#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include <stdbool.h>

#ifndef SCANNER_BUFFER_SIZE
#define SCANNER_BUFFER_SIZE 200
#endif


typedef struct scanner {
    FILE *infile;
    bool _wasNewLine, _firstRun;
    unsigned int infileLine;
    char buffer[SCANNER_BUFFER_SIZE];
    Status status;
} Scanner;

// 18 and 19 because of parser state table
typedef enum Token {
    T_INSTR, T_REG=18, T_INT=19
} Token;

struct token {
    Token token;
    int value;
    unsigned int line;
};

/******
 * Initialize a scanner context. you should free the context with scannerDestroy() when done with it.
 * 
 * @return A pointer to a malloc()'ed scanner context.
 ******/
Scanner *scannerInit();

/******
 * Destroy a scanner context (free() it).
 * 
 * @param s An initialized scanner context to destroy.
 ******/
void scannerDestroy(Scanner *s);

/******
 * Get the next token from the file.
 * 
 * @param context An initialized scanner context.
 * @param token A struct token to populate.
 * 
 * @return SUCCESS, END_OF_FILE, END_OF_LINE, UNRECOGNIZED_TOKEN from the status enum.
 ******/
Status nextToken(Scanner *context, struct token *token);

#endif // SCANNER_H
