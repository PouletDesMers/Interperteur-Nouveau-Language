#include "../include/parser.h"
#include "../include/symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
AST *parse_facteur(token **tokens, int *indice);
AST *parse_terme(token **tokens, int *indice);
AST *parse_expression(token **tokens, int *indice);

// focntion qui analyse des facteurs (nombre, une variable ou expression entre parenthèses)
AST *parse_facteur(token **tokens, int *indice) {
    token *tok = tokens[*indice];
    if (tok->type == NUMBER) {
        (*indice)++;
        // convertit la valeur du token en entier et crée un nœud AST de type nombre
        return noeud_nombre(atoi(tok->value));
    } else if (tok->type == IDENTIFIER) {
        (*indice)++;
        // récupère la valeur de la variable dans la table des symboles
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
        // retourne le nœud correspondant à l'expression entre parenthèses
        return noeud;
    } else {
        printf("Erreur: Facteur inattendu '%s'\n", tok->value);
        exit(1);
    }
}

// analyse un terme dans l'expression
AST *parse_terme(token **tokens, int *indice) {
    // analyse le premier facteur du terme
    AST *noeud = parse_facteur(tokens, indice);

    // 
    while (tokens[*indice] && tokens[*indice]->type == OPERATOR &&
           (strcmp(tokens[*indice]->value, "*") == 0 || strcmp(tokens[*indice]->value, "/") == 0)) { // comparaison des chaines de caractères
        // récupère le caractère de l'opérateur ('*' ou '/')
        char ope = tokens[*indice]->value[0];
        (*indice)++;
        AST *droit = parse_facteur(tokens, indice);
        noeud = noeud_operation(ope, noeud, droit);
    }
    return noeud;
}

// fonction qui analyse une expression complète
AST *parse_expression(token **tokens, int *indice) {
    AST *noeud = parse_terme(tokens, indice);
    while (tokens[*indice] && tokens[*indice]->type == OPERATOR &&
           (strcmp(tokens[*indice]->value, "+") == 0 || strcmp(tokens[*indice]->value, "-") == 0)) { // comparaison des chaines de caractères
        char ope = tokens[*indice]->value[0];
        (*indice)++;
        AST *droit = parse_terme(tokens, indice);
        noeud = noeud_operation(ope, noeud, droit);
    }
    return noeud;
}

// point d'entrée du parser
AST *parser(token **tokens) {
    int indice = 0;
    return parse_expression(tokens, &indice);
}
