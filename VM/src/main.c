#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disassembler.h"
#include "common.h"
#include "utilities.h"
#include "scanner.h"

void tokcpy(struct token *dest, struct token *src) {
    dest->token=src->token;
    dest->value=src->value;
}

const int table[20][8]= {
//  0   1   2   3   4   5   6   7
   {1, -1, -1, -1, -1, -1, -1, -1}, // 0
   {0, -1, -1, -1, -1, -1, -1, -1}, // 1
   {0, -1, -1, -1, -1, -1, -1, -1}, // 2
   {0, -1, -1, -1, -1, -1, -1, -1}, // 3
   {0, -1, -1, -1, -1, -1, -1, -1}, // 4
   {0, -1, -1, -1, -1, -1, -1, -1}, // 5
   {0, -1, -1, -1, -1, -1, -1, -1}, // 6
   {2, -1, -1, -1, -1, -1, -1, -1}, // 7
   {3, -1, -1, -1, -1, -1, -1, -1}, // 8
   {3, -1, -1, -1, -1, -1, -1, -1}, // 9
   {4, -1, -1, -1, -1, -1, -1, -1}, // 10
   {5, -1, -1, -1, -1, -1, -1, -1}, // 11
   {5, -1, -1, -1, -1, -1, -1, -1}, // 12
   {5, -1, -1, -1, -1, -1, -1, -1}, // 13
   {5, -1, -1, -1, -1, -1, -1, -1}, // 14
   {5, -1, -1, -1, -1, -1, -1, -1}, // 15
   {0, -1, -1, -1, -1, -1, -1, -1}, // 16
   {0, -1, -1, -1, -1, -1, -1, -1}, // 17
  {-1, -1,  6,  0,  7, -1, -1,  0}, // 18
  {-1,  0, -1, -1, -1,  0,  0, -1}  // 19
};

int parse(const char *infile) {
    int state=0, tmp, ret_val=0, isWaiting=0;
    struct token t, t2;
    SCANNERcontext *c=scannerInit();
    c->infile=fopen(infile, "rb");

    do {
        tmp=nextToken(c, &t);
        if(tmp==2 || tmp==1) break;
        if(tmp==3)  {
            continue;
        }
        tokcpy(&t2, &t);
        switch(t.token) {
            case T_INSTR:
                t.token=t2.value;
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
                t.token=18;
                break;
            case T_INT:
                t.token=19;
                break;
        }
        if((state=table[t.token][state]) == -1) {
            tokcpy(&t, &t2);
            break;
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
    return ret_val;
}

int main(int argc, char **argv) {
    return parse("in.asm");
}


// add static once this function is used.
/* static */void disassembler(const char *binaryname) {
    FILE *in=fopen(binaryname, "rb");
    printf("\033[1mFILE: %s\033[0m\n\n", binaryname);
    disassemble(in);
    fclose(in);
}

/*
struct token t;
    SCANNERcontext *c=scannerInit();
    c->infile=fopen("/Users/itai/Desktop/VM/in.asm", "r");
    int tmp;
    while(1) {
        tmp=nextToken(c, &t);
        if(tmp==2 || tmp==1) break;
        else if(tmp==3) continue;

        if(t.token==T_INSTR) {
            switch(t.value) {
                case PUSH:
                    printf("PUSH");
                    break;
                case PEEK:
                    printf("PEEK\n");
                    break;
                case ADD:
                    printf("ADD\n");
                    break;
            }
            fflush(stdout);
        } else if(t.token==T_INT) {
            printf(" %d\n", t.value);
        }
    }
    fclose(c->infile);
    scannerDestroy(c);
*/
