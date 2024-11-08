#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AST *noeud_nombre(int valeur) { //crée le noeud ast, 
    AST *noeud = malloc(sizeof(AST)); // alloue la mémoire
    noeud->type = AST_Nombre; //définie  AST nombre le type en enum
    noeud->valeur = valeur;
    return noeud;
}

AST *noeud_operation(char operation, AST *gauche, AST *droite) { //crée un noeud d'opération
    AST *noeud = malloc(sizeof(AST));
    noeud->type = AST_Operation;
    noeud->ope.operation = operation;
    noeud->ope.gauche = gauche; //deux sous branche gauche droite
    noeud->ope.droite = droite;
    return noeud;
}

AST *parse_facteur(token **tokens, int *indice) { //analyse le facteur, nmbre nombre convertie ast nombre
    token *tok = tokens[*indice];
    if (tok->type == NUMBER) {
        (*indice)++;
        return noeud_nombre(atoi(tok->value));//convertie une chaine de carac en entier
    }
    return NULL; //0
}

AST *parse_operation(token **tokens, int *indice) { //pour les operations * /  
    AST *noeud = parse_facteur(tokens, indice); //c pour les opérations * / rée les sous noeuds
    while (tokens[*indice] && (tokens[*indice]->type == OPERATOR) &&
           (strcmp(tokens[*indice]->value, "*") == 0 || strcmp(tokens[*indice]->value, "/") == 0)) {
        char ope = tokens[*indice]->value[0];
        (*indice)++;
        AST *droit = parse_facteur(tokens, indice);
        noeud = noeud_operation(ope, noeud, droit);
    }

    return noeud;
}

AST *parse_nombre(token **tokens, int *indice) { // operations - + 
    AST *noeud = parse_operation(tokens, indice);// garantie la priorité
    while (tokens[*indice] && (tokens[*indice]->type == OPERATOR) &&
           (strcmp(tokens[*indice]->value, "+") == 0 || strcmp(tokens[*indice]->value, "-") == 0)) {
        char ope = tokens[*indice]->value[0];
        (*indice)++;
        AST *droit = parse_operation(tokens, indice);
        noeud = noeud_operation(ope, noeud, droit);
    }

    return noeud;
}

AST *parser(token **tokens) { //appel syntasyque
    int indice = 0;
    return parse_nombre(tokens, &indice);
}

void parseuraffichage(AST *noeud) {
    if (!noeud) return;
    
    if (noeud->type == AST_Nombre) {
        printf("%d", noeud->valeur);
    } else if (noeud->type == AST_Operation) {
        printf("(");
        parseuraffichage(noeud->ope.gauche);
        printf(" %c ", noeud->ope.operation);
        parseuraffichage(noeud->ope.droite);
        printf(")");
    }
}