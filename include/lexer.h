

#include <stdio.h>

#define INITIAL_TOKEN_CAPACITY 10 
#define MAX_TOKEN_LEN 64

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

typedef struct {
    type_token type;
    char *value;
} token;

token **lexer(FILE *file);
void print_tokens(token **tokens);