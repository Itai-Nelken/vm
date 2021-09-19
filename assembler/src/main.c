#include <stdio.h>
#include "scanner.h"

int main(int argc, char **argv) {
    if(argc < 2) return 1;
    SCAN_context *c=scan_init();
    c->infile=fopen(argv[1], "r");
    scanfile(c);
    fclose(c->infile);
    scan_destroy(c);
    return 0;
}
