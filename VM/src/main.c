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

int parse(const char *filename) {
    int ret_val=0, tok_ret, getNext=1;
    struct token t, tmp, tmp2;
    SCANNERcontext *c=scannerInit();
    c->infile=fopen(filename, "r");
    while(1) {
        if(getNext==1) {
            tok_ret=nextToken(c, &t);
            if(tok_ret==2 || tok_ret==1) break;
            else if(tok_ret==3) continue;
        } else {
            if(getNext==0) {
                tokcpy(&t, &tmp);
                getNext=1;
            } else if(getNext==-1) {
                tokcpy(&t, &tmp);
                tokcpy(&tmp, &tmp2);
                getNext=0;
            }
        }

        if(t.token == T_INSTR) {
            switch(t.value) {
                // single argument instructions
                case PUSH: // int
                case PSET: // register
                case GET: // register
                case JMP: // int
                case JEQ: // int
                case JNE: // int
                case JLT: // int
                case JGT: // int
                    // check single argument
                    if(nextToken(c, &tmp)!=0) {
                        fprintf(stderr, "ERROR: instruction '%s' requires an argument!\n", instr2str(t.value));
                        ret_val=1;
                        goto cleanup;
                    } else {
                        getNext=0;
                    }
                    break;
                // 2 argument instructions
                case SET: // register int
                case MOV: // register register
                    // check 2 arguments
                    if(nextToken(c, &tmp)!=0) {
                        fprintf(stderr, "ERROR: instruction '%s' requires 2 arguments!\n", instr2str(t.value));
                        ret_val=1;
                        goto cleanup;
                    } else {
                        if(nextToken(c, &tmp2)!=0) {
                            fprintf(stderr, "ERROR: instruction '%s' requires another argument!\n", instr2str(t.value));
                            ret_val=1;
                            goto cleanup;
                        }
                        getNext=-1;
                    }
                    break;
                default:
                    break;
                    
            }
        } else if(t.token == T_REG) {
            // move register checking to here.
            // and change register syntax to 'r<reg>'
        } else if(t.token == T_INT) {
            // nothing to do :)
        }
    }

cleanup:
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
