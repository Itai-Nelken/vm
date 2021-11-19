#include <string.h>
#include "utilities.h"

void strzero(char *s) {
    while(*s++) {
        *s=0;
    }
}

void leftShift(char *s) {
    for(int i = 1; i < (int)strlen(s); i++) {
        s[i-1] = s[i];
    }
    s[strlen(s)-1]='\0';
}

int strcontains(char *s, const char *c) {
    int exit=0;
    for(int i=0; i<(int)strlen(s) && exit!=1; ++i) {
        for(int x=0; x<(int)strlen(c); ++x) {
            if(s[i]==c[x]) {
                exit=1;
            }
            if(exit==1) break;
        }
    }
    return !exit; // if exit==1 (match found), return 0. if no match found (exit==0), return 1.
}

int str2int(char *s) {
    int value=0;
    for(int i=0; i<(int)strlen(s); ++i) {
        value = value*10+(s[i]-'0');
    }
    return value;
}
