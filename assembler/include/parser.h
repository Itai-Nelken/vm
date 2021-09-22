#ifndef PARSER_H
#define PARSER_H

/******
 * Assemble a binary from a file. calls the scanner, does the parsing, and then writes the binary.
 * 
 * @param infile the name of the file to read.
 * @param outfile the name of the file to write.
 * 
 * @return 0: success, 1: failure.
 * failure includes syntax errors.
 ******/
int parse(const char *infile, const char *outfile);

#endif // PARSER_H
