#include <string.h>
#include "utilities.h"

int strcontains(char *s, const char *c) {
    int exit=0;
    for(int i=0; i<strlen(s) && exit!=1; ++i) {
        for(int x=0; x<strlen(c); ++x) {
            if(s[i]==c[x]) {
                exit=1;
            }
            if(exit==1) break;
        }
    }
    return exit ^ 1; // xor exit with 1 so if exit==1, return 0.
}

/***
 * XOR
 * ===
 * |in |in |out|
 * | 0 | 0 | 0 |
 * | 1 | 0 | 1 |
 * | 0 | 1 | 1 |
 * | 1 | 1 | 0 | // what strcontains() uses XOR for.
 ***/

int str2int(char *s) {
    int value=0;
    for(int i=0; i<strlen(s); ++i) {
        value = value*10+(s[i]-'0');
    }
    return value;
}

void strzero(char *s) {
    while(*s++) {
        *s=0;
    }
}
