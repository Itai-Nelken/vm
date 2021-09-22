#include <stdio.h>
#include <string.h>
#include "common.h"
#include "scanner.h"
#include "disassembler.h"

static void tokcpy(struct token *dest, struct token *src) {
    dest->token=src->token;
    dest->value=src->value;
}

static int writeOp(FILE *f, struct operation *op) {
    return fwrite(op, sizeof(struct operation), 1, f)!=0 ? 0 : 1;
}

// state table for parser.
// holds all possible states.
// -1 means that the state shouldn't happen.
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

int parse(const char *infile, const char *outfile) {
    int state=0, tmp, ret_val=0, isWaiting=0;
    
    int whatArg=1;
    struct operation op;
    FILE *out=fopen(outfile, "w");
    if(!out) {
        perror("parse(): fopen(outfile, w)");
        return 1;
    }
    // write the start symbol
    op.instruction=S_START;
    op.arg1=0;
    op.arg2=0;
    writeOp(out, &op);
    
    struct token t, t2;
    SCANNERcontext *c=scannerInit();
    c->infile=fopen(infile, "rb");
    if(!c->infile) {
        perror("parse(): fopen(infile, rb)");
        scannerDestroy(c);
        fclose(out);
        return 1;
    }

    do {
        tmp=nextToken(c, &t);
        if(tmp==2 || tmp==1) break;
        if(tmp==3)  {
            continue;
        }
        tokcpy(&t2, &t);
        switch(t.token) {
            case T_INSTR:
                op.instruction=t.value;
                t.token=t.value;
                break;
            case T_REG:
                // if only 'R' is provided
                if(!t.value) {
                    break;     
                }
                // if register doesn't exist
                if(!strcmp(reg2str(t.value), "UNKNOWN")) {
                    fprintf(stderr, "WARNING: line %d: register doesn't exist!\n", c->infileLine);
                }
                if(whatArg==1) {
                    op.arg1=t.value;
                    whatArg=2;
                } else if(whatArg==2) {
                    op.arg2=t.value;
                    whatArg=1;
                }
                t.token=18;
                break;
            case T_INT:
                if(whatArg==1) {
                    op.arg1=t.value;
                    whatArg=2;
                } else if(whatArg==2) {
                    op.arg2=t.value;
                    whatArg=1;
                }
                t.token=19;
                break;
        }
        if((state=table[t.token][state]) == -1) {
            tokcpy(&t, &t2);
            break;
        }
        // if state is back to normal (0), write the opcode+operands
        if(state==0) {
            whatArg=1;
            writeOp(out, &op);
            op.arg1=0;
            op.arg2=0;
        }
        // if state != 0 (meaning that there is another argument, set isWaiting to the current line).
        // we can then use isWaiting to check if an argument wasn't provided in cases where the state table
        // doesn't (like the file ended). the line is so we can print in what line the error is.
        if(state!=0) isWaiting=c->infileLine;
        if(state==0) isWaiting=0;

    } while(1);
    if(state==-1) {
        fprintf(stderr, "ERROR: syntax error in line %d!\n", c->infileLine);
        ret_val=1;
    } else if(isWaiting!=0) {
        fprintf(stderr, "ERROR: line %d: waiting for argument but file ended!\n", isWaiting);
        ret_val=1;
    }

    fclose(c->infile);
    scannerDestroy(c);

    // write the end symbol
    op.instruction=S_END;
    writeOp(out, &op);
    fclose(out);
    return ret_val;
}