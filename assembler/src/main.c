#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "disassembler.h"
#include "parser.h"

static int disassembler(const char *binaryname) {
    FILE *in=fopen(binaryname, "rb");
    if(!in) {
	perror("disassembler(): fopen()");
	return 1;
    }
    printf("\033[1mFILE: %s\033[0m\n\n", binaryname);
    disassemble(in);
    fclose(in);
    return 0;
}

void print_help(const char *progname) {
    printf("%s [file] [options]\n", progname);
    printf("Options:\n");
    printf("    --disassemble|-d        Disassemble the provided file.\n");
    printf("    --output|-o  <outname>  Set the name of the output binary.\n");
    printf("    --help|-h               Print this help.\n");
    //printf("    --version|-v            Print version information.\n");
}

struct option long_options[] = {
    {"disassemble", required_argument, NULL, 'd'},
    {"output", required_argument, NULL, 'o'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, NULL, 0}
};

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "ERROR: insufficient arguments provided!\n");
        return 1;
    }
    int opt, ret_val=0, exit=0;
    char *outfile=NULL, *infile=malloc(strlen(argv[1])*sizeof(char)+1);
    strncpy(infile, argv[1], strlen(argv[1])*sizeof(char)+1);

    opt=getopt_long(argc, argv, "d:o:h", long_options, NULL);
    if(opt != -1) {
        switch(opt) {
            case 'o':
                outfile=optarg;
                break;
            case 'd':
		// return 1 if disassembler succeds, 1 if it fails
                ret_val=disassembler(optarg)==0 ? 0 : 1;
                exit=1;
                break;
            case 'h':
                print_help(argv[0]);
                ret_val=exit=1;
                break;
            default:
                ret_val=exit=1;
                break;
        }
    }
    if(exit!=1)
        ret_val=parse(infile, outfile!=NULL ? outfile : "as.out.vm");
    free(infile);
    return ret_val;
}

