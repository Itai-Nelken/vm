#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "common.h"
#include "Array.h"
#include "scanner.h"
#include "disassembler.h"
#include "parser.h"

// copy src to dest
static void tokcpy(struct token *dest, struct token *src) {
    dest->token=src->token;
    dest->value=src->value;
    dest->line=src->line;
}

// state table for parser
// impossible states are -1
const int table[20][8]= {
//               STATES             // OPCODES
//  0   1   2   3   4   5   6   7   // -------
   {1, -1, -1, -1, -1, -1, -1, -1}, // 0  PUSH
   {0, -1, -1, -1, -1, -1, -1, -1}, // 1  POP
   {0, -1, -1, -1, -1, -1, -1, -1}, // 2  PEEK
   {0, -1, -1, -1, -1, -1, -1, -1}, // 3  ADD
   {0, -1, -1, -1, -1, -1, -1, -1}, // 4  SUB
   {0, -1, -1, -1, -1, -1, -1, -1}, // 5  MUL
   {0, -1, -1, -1, -1, -1, -1, -1}, // 6  DIV
   {2, -1, -1, -1, -1, -1, -1, -1}, // 7  SET
   {3, -1, -1, -1, -1, -1, -1, -1}, // 8  PSET
   {3, -1, -1, -1, -1, -1, -1, -1}, // 9  GET
   {4, -1, -1, -1, -1, -1, -1, -1}, // 10 MOV
   {5, -1, -1, -1, -1, -1, -1, -1}, // 11 JMP
   {5, -1, -1, -1, -1, -1, -1, -1}, // 12 JEQ
   {5, -1, -1, -1, -1, -1, -1, -1}, // 13 JNE
   {5, -1, -1, -1, -1, -1, -1, -1}, // 14 JLT
   {5, -1, -1, -1, -1, -1, -1, -1}, // 15 JGT
   {0, -1, -1, -1, -1, -1, -1, -1}, // 16 NOP
   {0, -1, -1, -1, -1, -1, -1, -1}, // 17 HLT
  {-1, -1,  6,  0,  7, -1, -1,  0}, // 18 REGISTER
  {-1,  0, -1, -1, -1,  0,  0, -1}  // 19 INT
};

Status parseFile(const char *filename, Array *prog) {
    // parser status and data
    int state=0, ret_val=SUCCESS;
    bool isWaiting=false, exit=true;
    int whatArg=1; // track what argument we recieved for instructions with multiple arguments
    struct token t, prev;
    struct operation op = {
        .arg1=0,
        .arg2=0
    };
    Scanner *scanner=scannerInit();

    // open the infile
    scanner->infile=fopen(filename, "r");
    if(!scanner->infile) {
        fprintf(stderr, "parseFile(): fopen(%s, r): %s\n", filename, strerror(errno));
        scannerDestroy(scanner);
        return OPEN_FILE_FAILURE;
    }

    // add the start symbol
    op.instruction=S_START;
    arrayPush(prog, &op);

    // start parsing
    while(exit) {
        switch(nextToken(scanner, &t)) {
            case END_OF_LINE:
                continue;
            case END_OF_FILE:
            case UNRECOGNIZED_TOKEN:
                exit=false;
                continue;
            case SUCCESS:
            default:
                break;
        }
        switch(t.token) {
            case T_INSTR:
                op.instruction=t.value;
                // set t.token to the instruction (t.value) for the state table
                t.token=t.value;
                break;
            case T_REG:
                // if register doesn't exist
                if(!strcmp(reg2str(t.value), "UNKNOWN")) {
                    fprintf(stderr, "WARNING: line %d: register doesn't exist!\n", scanner->infileLine);
                }
                // decide what argument we recieved
                if(whatArg==1) {
                    op.arg1=t.value;
                    whatArg=2;
                } else if(whatArg==2) {
                    op.arg2=t.value;
                    whatArg=1;
                }
                break;
            case T_INT:
                if(whatArg==1) {
                    op.arg1=t.value;
                    whatArg=2;
                } else if(whatArg==2) {
                    op.arg2=t.value;
                    whatArg=1;
                }
                break;
        }
        if((state=table[t.token][state]) == -1) {
            break;
        }
        // if state is back to 0 (normal), write the operation to the program array
        if(state==0) {
            arrayPush(prog, &op);
            // reset parser state for next instruction
            tokcpy(&prev, &t);
            isWaiting=false;
            whatArg=1;
            op.arg1=0;
            op.arg2=0;
        }
        // if state is -1 (meaning that there should be another argument), set isWaiting to true.
        // we can then use isWaiting to check if an argument wasn;t provided in cases where the state table
        // doesn't (like if the file ended).
        if(!isWaiting && state == -1) isWaiting=true;
    }

    if(state == -1) {
        // if there was a new line and the state doesn't match with what it shoud be,
        // the current line will be one too much, so if the scanner encountered a newline
        // it will set scanner.wasNewLine to true.
        // it will be reset to false in the 2nd call to the scanner (nextToken()) after being set to true.
        // so if the state doesn't match and there was a newline (scanner.wasNewLine == true), the line is prev.line.
        // The previous token.line
        // else it's simply t.line (the current token.line)
        fprintf(stderr, "ERROR: syntax error in line %d!\n", (isWaiting ? prev.line : t.line));
        ret_val=SYNTAX_ERROR;
    } else if(isWaiting) {
        fprintf(stderr, "ERROR: line %d: waiting for argument but file ended!\n", prev.line);
        ret_val=SYNTAX_ERROR;
    }
    fclose(scanner->infile);
    scannerDestroy(scanner);

    op.instruction=S_END;
    arrayPush(prog, &op);
    return ret_val;
}
