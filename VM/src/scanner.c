#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "utilities.h"
#include "scanner.h"

SCANNERcontext *scannerInit() {
    SCANNERcontext *context=malloc(sizeof(SCANNERcontext));
    strzero(context->buffer);
    context->buffer_size=100*sizeof(char);
    context->infileLine=0;
    return context;
}

void scannerDestroy(SCANNERcontext *context) {
    free(context);
}

void trim(char *s) {
    for(int i=strlen(s)-1; i>0; i--) {
        if(s[i]=='\n' || s[i]==' ' || s[i]=='\r' || s[i]=='\t') {
            s[i]='\0';
        } else {
            break;
        }       
    }
}

// 0: success.
// 1: end of file.
// 2: unrecognized token.
// 3: end of line/newline/comment.
int nextToken(SCANNERcontext *context, struct token *t) {
    static int firstRun=1;
    char *p, *separator=" ";
    if(firstRun==1) {
        strzero(context->buffer);
        if(fgets(context->buffer, (context->buffer_size)-1, context->infile)==NULL) {
            return 1;
        }
        (context->infileLine)++;
        trim(context->buffer);
    }

    if(firstRun==1) {
        p=strtok(context->buffer, separator);
        firstRun=0;
    } else {
        p=strtok(NULL, separator);
    }
    if(p==NULL) {
        firstRun=1;
        return 3;
    }
    trim(p);
    if(*p=='\n' || *p==';') {
        firstRun=1;
        return  3;
    } else if(!strcasecmp(p, "PUSH")) { // instructions
        t->token=T_INSTR;
        t->value=PUSH;
    } else if(!strcasecmp(p, "POP")) {
        t->token=T_INSTR;
        t->value=POP;
    } else if(!strcasecmp(p, "PEEK")) {
        t->token=T_INSTR;
        t->value=PEEK;
    } else if(!strcasecmp(p, "ADD")) {
        t->token=T_INSTR;
        t->value=ADD;
    } else if(!strcasecmp(p, "ADD")) {
        t->token=T_INSTR;
        t->value=ADD;
    } else if(!strcasecmp(p, "SUB")) {
        t->token=T_INSTR;
        t->value=SUB;
    } else if(!strcasecmp(p, "MUL")) {
        t->token=T_INSTR;
        t->value=MUL;
    } else if(!strcasecmp(p, "DIV")) {
        t->token=T_INSTR;
        t->value=DIV;
    } else if(!strcasecmp(p, "SET")) {
        t->token=T_INSTR;
        t->value=SET;
    } else if(!strcasecmp(p, "PSET")) {
        t->token=T_INSTR;
        t->value=PSET;
    } else if(!strcasecmp(p, "GET")) {
        t->token=T_INSTR;
        t->value=GET;
    } else if(!strcasecmp(p, "MOV")) {
        t->token=T_INSTR;
        t->value=MOV;
    } else if(!strcasecmp(p, "JMP")) {
        t->token=T_INSTR;
        t->value=JMP;
    } else if(!strcasecmp(p, "JEQ")) {
        t->token=T_INSTR;
        t->value=JEQ;
    } else if(!strcasecmp(p, "JNE")) {
        t->token=T_INSTR;
        t->value=JNE;
    } else if(!strcasecmp(p, "JLT")) {
        t->token=T_INSTR;
        t->value=JLT;
    } else if(!strcasecmp(p, "JGT")) {
        t->token=T_INSTR;
        t->value=JGT;
    } else if(!strcasecmp(p, "NOP")) {
        t->token=T_INSTR;
        t->value=NOP;
    } else if(!strcasecmp(p, "HLT")) {
        t->token=T_INSTR;
        t->value=HLT;
    } else if(!strcasecmp(p, "A")) { // registers
        t->token=T_REG;
        t->value=A;
    } else if(!strcasecmp(p, "B")) {
        t->token=T_REG;
        t->value=B;
    } else if(!strcasecmp(p, "C")) {
        t->token=T_REG;
        t->value=C;
    } else if(!strcasecmp(p, "D")) {
        t->token=T_REG;
        t->value=D;
    } else if(!strcasecmp(p, "E")) {
        t->token=T_REG;
        t->value=E;
    } else if(!strcasecmp(p, "F")) {
        t->token=T_REG;
        t->value=F;
    } else if(!strcasecmp(p, "SP")) {
        t->token=T_REG;
        t->value=SP;
    } else if(!strcasecmp(p, "PC")) {
        t->token=T_REG;
        t->value=PC;
    } else if(!strcontains(p, "0123456789")) { // integers
        t->token=T_INT;
        t->value=str2int(p);
    } else {
        fprintf(stderr, "ERROR: unrecognized token \"%s\" in line %d!\n", p, context->infileLine);
        return 2;
    }
    return 0;
}