#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

// déclaration des fonctions
AST *parse_facteur(token **tokens, int *indice);
AST *parse_terme(token **tokens, int *indice);
AST *parse_expression(token **tokens, int *indice);
AST *parser(token **tokens);

#endif // PARSER_H
