#include <stdio.h>
#include <getopt.h>
#include "vm.h"

#ifndef VM_VERSION
#define VM_VERSION 1.0
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

static void printHelp(const char *argv0) {
    printf("\033[1mUSAGE:\033[0m\n\t %s [-h|-v] [binary]\n", argv0);
    printf("\033[1marguments:\033[0m\n");
    printf("\t-h|--help - print this help.\n");
    printf("\t-v|--version - print version information.\n");
}

struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {0, 0, NULL, 0}
};

int main(int argc, char **argv) {
    int retval=0, opt;
    VM *vm=NULL;
    if(argc < 2) {
        fprintf(stderr, "ERROR: Insufficient arguments provided!\n");
        retval=1;
    } else {
        if((opt=getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
            switch(opt) {
                case 'h':
                    printHelp(argv[0]);
                    break;
                case 'v':
                    printf("VM version %f, built on %s%s.\n", VM_VERSION, __TIMESTAMP__, (DEBUG!=0 ? " with debug mode on" : ""));
                    break;
                default:
                    retval=2;
                    break;
            }
        } else {
            retval=3;
        }
    }
    switch (retval) {
        case 0:
        case 1:
        case 2:
            return retval==2 ? 1 : retval;
        case 3:
            vm=vmInit();
            if(loadBinary(argv[1], vm->program)!=0) {
                fprintf(stderr, "ERROR: Failed to load binary!\n");
                vmDestroy(vm);
                retval=1;
            } else {
                exec(vm);
                vmDestroy(vm);
                retval=0;
            }
            break;
    }
    return retval;
}
