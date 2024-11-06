#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

// Fonctions du parser
AST *parse_facteur(token **tokens, int *indice);
AST *parse_terme(token **tokens, int *indice);
AST *parse_expression(token **tokens, int *indice);
AST *parser(token **tokens);

#endif // PARSER_H
