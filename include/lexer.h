#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define INITIAL_TOKEN_CAPACITY 10 
#define MAX_TOKEN_LEN 64

// liste tous les types possibles de tokens que le lexer peut reconnaître lors de l'analyse lexicale.
typedef enum {
    NUMBER, // 0, 1, 2, ...
    KEYWORD, // if
    ASSIGN, // =
    LPAREN, // (
    RPAREN, // )
    IDENTIFIER, // a , b , print
    OPERATOR, // +, -, *, /
    LBRACE, // {
    RBRACE, // }
    SEMICOLON, // ;
    QUOTE, // "
} type_token;

// représente un token individuel
typedef struct {
    type_token type;
    char *value;
} token;

// déclaration des fonctions
token **lexer(FILE *file);
void print_tokens(token **tokens);

#endif // LEXER_H