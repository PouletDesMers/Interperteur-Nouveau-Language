#include "../include/parser.h"
#include "../include/symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
AST *parse_facteur(token **tokens, int *indice);
AST *parse_terme(token **tokens, int *indice);
AST *parse_expression(token **tokens, int *indice);

AST *parse_facteur(token **tokens, int *indice) {
    token *tok = tokens[*indice];
    if (tok->type == NUMBER) {
        (*indice)++;
        return noeud_nombre(atoi(tok->value));
    } else if (tok->type == IDENTIFIER) {
        // Gérer les variables (extension possible)
        (*indice)++;
        int valeur = hash_table_get(tok->value);
        return noeud_nombre(valeur);
    } else if (tok->type == LPAREN) {
        (*indice)++;
        AST *noeud = parse_expression(tokens, indice);
        if (tokens[*indice]->type == RPAREN) {
            (*indice)++;
        } else {
            printf("Erreur: Parenthèse fermante attendue\n");
            exit(1);
        }
        return noeud;
    } else {
        printf("Erreur: Facteur inattendu '%s'\n", tok->value);
        exit(1);
    }
}

AST *parse_terme(token **tokens, int *indice) {
    AST *noeud = parse_facteur(tokens, indice);
    while (tokens[*indice] && tokens[*indice]->type == OPERATOR &&
           (strcmp(tokens[*indice]->value, "*") == 0 || strcmp(tokens[*indice]->value, "/") == 0)) {
        char ope = tokens[*indice]->value[0];
        (*indice)++;
        AST *droit = parse_facteur(tokens, indice);
        noeud = noeud_operation(ope, noeud, droit);
    }
    return noeud;
}

AST *parse_expression(token **tokens, int *indice) {
    AST *noeud = parse_terme(tokens, indice);
    while (tokens[*indice] && tokens[*indice]->type == OPERATOR &&
           (strcmp(tokens[*indice]->value, "+") == 0 || strcmp(tokens[*indice]->value, "-") == 0)) {
        char ope = tokens[*indice]->value[0];
        (*indice)++;
        AST *droit = parse_terme(tokens, indice);
        noeud = noeud_operation(ope, noeud, droit);
    }
    return noeud;
}

AST *parser(token **tokens) {
    int indice = 0;
    return parse_expression(tokens, &indice);
}
