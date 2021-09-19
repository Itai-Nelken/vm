#ifndef COMMON_H
#define COMMON_H

/* SCANNER */
typedef enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INT, T_EOF
} Token;

struct token {
    Token token;
    int intval;
};

#endif // COMMON_H
