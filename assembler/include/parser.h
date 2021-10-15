#ifndef PARSER_H
#define PARSER_H
#include "Array.h"

/******
 * Assembler a program into a dynamic array.
 * 
 * @param infile the name of the file to read.
 * @param prog the dynamic array to write the assembled program to.
 * 
 * @return SUCCESS, OPEN_FILE_FAILURE, SYNTAX_ERROR from the status enum.
 ******/
Status parseFile(const char *infile, Array *prog);

#endif // PARSER_H
