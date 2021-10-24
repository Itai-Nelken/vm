#include <stdio.h>
#include "common.h"
#include "parser.h"
#include "assembler.h"

static inline int writeOp(FILE *f, struct operation *op) {
    return fwrite(op, sizeof(struct operation), 1, f)!=0 ? 0 : 1;
}

Status assembleFile(const char *infile, const char *outfile) {
    FILE *out=fopen(outfile, "w");
    if(!out) {
        perror("assemblerFile(): fopen(outfile, w)");
        return OPEN_FILE_FAILURE;
    }
    struct operation op = {
        .arg1=0,
        .arg2=2
    };
    Array *program=initArray(16, 8);
    Array *sortedProgram=NULL;

    Status parseStatus=parseFile(infile, program);
    switch(parseStatus) {
        case OPEN_FILE_FAILURE:
        case SYNTAX_ERROR:
            destroyArray(program);
            fclose(out);
            return parseStatus;
        case SUCCESS:
        default:
            break;
    }
    // reverse the array
    sortedProgram=initArray(program->current+1, 8);
    while(op.instruction!=S_START) {
        arrayPop(program, &op);
        arrayPush(sortedProgram, &op);
    }

    // write the binary
    while(op.instruction!=S_END) {
        arrayPop(sortedProgram, &op);
        writeOp(out, &op);
    }
    
    destroyArray(sortedProgram);
    destroyArray(program);
    fclose(out);
    return SUCCESS;
}
