#include <stdio.h>
#include <getopt.h>
#include "vm.h"

#ifndef VM_VERSION
#define VM_VERSION 1.0
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {0, 0, NULL, 0}
};

int main(int argc, char **argv) {
    int retval=0;
    if(argc < 2) {
        fprintf(stderr, "ERROR: insufficient arguments provided!\n");
        retval=1;
    } else {
        int opt=getopt_long(argc, argv, "hv", long_options, NULL);
        switch(opt) {
            case 'h':
                printf("USAGE: %s [-h] [binary]\n", argv[0]);
                retval=1;
                break;
            case 'v':
                printf("VM version %f, built on %s%s.", VM_VERSION, __TIMESTAMP__, (DEBUG!=0 ? " with debug mode on" : ""));
                break;
            default:
                retval=-1;
                break;
        }
    }
    if(retval == -1) {
        VM *vm=vmInit();
        loadBinary(argv[1], vm->program);
        exec(vm);
        vmDestroy(vm);
    }
    return retval;
}
