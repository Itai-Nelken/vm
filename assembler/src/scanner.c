#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "utilities.h"
#include "disassembler.h"
#include "scanner.h"

Scanner *scannerInit() {
    Scanner *new = malloc(sizeof(*new));
    strzero(new->buffer);
    new->infileLine = 0;
    new->_wasNewLine = false;
    new->_firstRun = true;
    new->status = SUCCESS;
    return new;
}

void scannerDestroy(Scanner *s) {
    free(s);
}

void trim(char *s) {
    for(int i = strlen(s) - 1; i > 0; i--) {
        if(s[i] == '\n' || s[i] == ' ' || s[i] == '\r' || s[i] == '\t') {
            s[i] = '\0';
        } else {
            break;
        }       
    }
}

Status nextToken(Scanner *context, struct token *token) {
    char *p, *separator = " ";
    if(context->_firstRun) {
        strzero(context->buffer);
        if(fgets(context->buffer, SCANNER_BUFFER_SIZE, context->infile) == NULL) {
            context->status = END_OF_FILE;
            return END_OF_FILE;
        }
        (context->infileLine)++;
        trim(context->buffer);
        p = strtok(context->buffer, separator);
        context->_firstRun=false;
    } else {
        // reset wasNewLine if it isn't
        if(!context->_wasNewLine) context->_wasNewLine = false;
        p = strtok(NULL, separator);
    }
    if(p == NULL) {
        context->_wasNewLine = true;
        context->_firstRun = true;
        context->status = END_OF_LINE;
        return END_OF_LINE;
    }
    // trim here because we want to handle strtok() returning NULL first
    trim(p);
    // handle newlines and comments
    if(*p == '\n' || *p == ';') {
        context->_firstRun = true;
        context->status = END_OF_LINE;
        return END_OF_LINE;
    } else if(!strcasecmp(p, "PUSH")) { // instructions
        token->value = PUSH;
        token->token = T_INSTR;
    } else if(!strcasecmp(p, "POP")) {
        token->token = T_INSTR;
        token->value = POP;
    } else if(!strcasecmp(p, "PEEK")) {
        token->token = T_INSTR;
        token->value = PEEK;
    } else if(!strcasecmp(p, "ADD")) {
        token->token = T_INSTR;
        token->value = ADD;
    } else if(!strcasecmp(p, "ADD")) {
        token->token = T_INSTR;
        token->value = ADD;
    } else if(!strcasecmp(p, "SUB")) {
        token->token = T_INSTR;
        token->value = SUB;
    } else if(!strcasecmp(p, "MUL")) {
        token->token = T_INSTR;
        token->value = MUL;
    } else if(!strcasecmp(p, "DIV")) {
        token->token = T_INSTR;
        token->value = DIV;
    } else if(!strcasecmp(p, "SET")) {
        token->token = T_INSTR;
        token->value = SET;
    } else if(!strcasecmp(p, "PSET")) {
        token->token = T_INSTR;
        token->value = PSET;
    } else if(!strcasecmp(p, "GET")) {
        token->token = T_INSTR;
        token->value = GET;
    } else if(!strcasecmp(p, "MOV")) {
        token->token = T_INSTR;
        token->value = MOV;
    } else if(!strcasecmp(p, "JMP")) {
        token->token = T_INSTR;
        token->value = JMP;
    } else if(!strcasecmp(p, "JEQ")) {
        token->token = T_INSTR;
        token->value = JEQ;
    } else if(!strcasecmp(p, "JNE")) {
        token->token = T_INSTR;
        token->value = JNE;
    } else if(!strcasecmp(p, "JLT")) {
        token->token = T_INSTR;
        token->value = JLT;
    } else if(!strcasecmp(p, "JGT")) {
        token->token = T_INSTR;
        token->value = JGT;
    } else if(!strcasecmp(p, "NOP")) {
        token->token = T_INSTR;
        token->value = NOP;
    } else if(!strcasecmp(p, "HLT")) {
        token->token = T_INSTR;
        token->value = HLT;
    } else if(tolower(p[0])=='r') {
        token->token = T_REG;
        leftShift(p);
        token->value=str2reg(p);
    } else if(!strcasecmp(p, "SP")) {
        token->token = T_REG;
        token->value = SP;
    } else if(!strcasecmp(p, "PC")) {
        token->token = T_REG;
        token->value = PC;
    } else if(!strcasecmp(p, "TM")) {
        token->token = T_REG;
        token->value = TM;
    } else if(!strcontains(p, "0123456789")) { // integers
        token->token=T_INT;
        token->value=str2int(p);
    } else {
        fprintf(stderr, "ERROR: unrecognized word \"%s\" in line %u!\n", p, context->infileLine);
        context->status=UNRECOGNIZED_TOKEN;
        return UNRECOGNIZED_TOKEN;
    }
    token->line=context->infileLine;
    context->status=SUCCESS;
    return SUCCESS;
}
