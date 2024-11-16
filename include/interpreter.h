#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ast.h"

void interpret(const char *input);
extern AST *global_ast;
void afficher_AST_global();

#endif // INTERPRETER_H
