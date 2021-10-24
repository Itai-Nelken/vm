#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include "common.h"

/******
 * Assemble a file into a program and write it into a binary.
 * 
 * @param infile The name of the input file.
 * @param outfile The name of the output binary to write.
 * 
 * @return SUCCESS, OPEN_FILE_FAILURE, SYNTAX_ERROR from the status enum.
 ******/
Status assembleFile(const char *infile, const char *outfile);

#endif // ASSEMBLER_H
