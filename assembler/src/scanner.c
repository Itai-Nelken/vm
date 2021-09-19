#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // strstr()
#include <ctype.h> // isdigit()

#include "common.h"
#include "scanner.h"

// the tokens as a string.
const char *tokstr[] = {"+", "-", "*", "/", "intlit"};

SCAN_context *scan_init() {
    SCAN_context *new=malloc(sizeof(SCAN_context));
    if(new==NULL) {
        fprintf(stderr, "scan_init(): malloc() failed!\n");
        exit(1);
    }
    new->Line=1;
    new->Putback=0;
    return new;
}

void scan_destroy(SCAN_context *c) {
    free(c);
}

/******
 * Get the next character
 * @param sc An initialized scanner context
 * @return The character.
 ******/
static int next(SCAN_context *sc) {
    int c;

    if(sc->Putback) {
        c=sc->Putback;
        sc->Putback=0;
        return c;
    }
    c=fgetc(sc->infile);
    if(c=='\n') (sc->Line)++;
    return c;
}

/******
 * Put back a character
 * @param sc An initialized scanner context.
 * @param c The character to put back.
 ******/
static void putback(SCAN_context *sc, char c) {
    sc->Putback=c;
}

/******
 * Skip newlines, spaces etc.
 * @param sc An initialized scanner context.
 * @return The next character that isn't a space, newline etc.
 ******/
static int skip(SCAN_context *sc) {
    int c=next(sc);
    while (c==' ' || c=='\n' || c=='\r' || c=='\r' || c=='\f') {
        c=next(sc);
    }
    return c;
}

/******
 * Check if a character is one of the characters in a string.
 * @param s The string.
 * @param c the character.
 * @return The character or -1 if the character isn't there.
 ******/
static int chrpos(char *s, int c) {
    char s2[2]={0};
    snprintf(s2, 2, "%c", c);
    char *p=strstr(s, s2);
    return p ? p-s : -1; // TODO: understand how p-s works (returns the first character p points to).
}

/******
 * Check if character c is an integer (in ascii).
 * @param sc An initialized scanner context.
 * @param c the character.
 ******/
static int scanint(SCAN_context *sc, int c) {
    int tmp, val=0;
    while((tmp=chrpos("0123456789", c))>=0) {
        val=val*10+tmp; // *10 to make room for the new value???
        c=next(sc);
    }
    // not an int
    putback(sc, c);
    return val;
}

int scan(SCAN_context *sc, struct token *t) {
    int c=skip(sc);
    switch(c) {
        case EOF:
            t->token=T_EOF;
            return 1;
        case '+':
            t->token=T_PLUS;
            break;
        case '-':
            t->token=T_MINUS;
            break;
        case '*':
            t->token=T_STAR;
            break;
        case '/':
            t->token=T_SLASH;
            break;
        default:
            if(isdigit(c)) {
                t->intval=scanint(sc, c);
                t->token=T_INT;
                break;
            }
            printf("Unrecognized character '%c' on line %d!\n", c, sc->Line);
            exit(1);
    }
    return 0;
}

/******
 * Scan a file and print the output.
 * @param c An initialized scanner context.
 ******/
void scanfile(SCAN_context *c) {
    struct token T;

    while(!scan(c, &T)) {
        printf("Token \"%s\"", tokstr[T.token]);
        if(T.token==T_INT) {
            printf(", value %d", T.intval);
        }
        printf("\n");
    }
}
