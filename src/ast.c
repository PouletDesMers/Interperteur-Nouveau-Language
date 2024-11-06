#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h"
#include "../include/symbolTable.h"

AST *noeud_nombre(int valeur) {
    AST *noeud = malloc(sizeof(AST));
    noeud->type = AST_Nombre;
    noeud->valeur = valeur;
    return noeud;
}

AST *noeud_operation(char operation, AST *gauche, AST *droite) {
    AST *noeud = malloc(sizeof(AST));
    noeud->type = AST_Operation;
    noeud->ope.operation = operation;
    noeud->ope.gauche = gauche;
    noeud->ope.droite = droite;
    return noeud;
}

int eval(AST *noeud) {
    if (noeud->type == AST_Nombre) {
        return noeud->valeur;
    } else if (noeud->type == AST_Operation) {
        int gauche = eval(noeud->ope.gauche);
        int droite = eval(noeud->ope.droite);
        switch (noeud->ope.operation) {
            case '+': return gauche + droite;
            case '-': return gauche - droite;
            case '*': return gauche * droite;
            case '/': return gauche / droite;
            default:
                printf("Erreur: Opération inconnue '%c'\n", noeud->ope.operation);
                exit(1);
        }
    }
    return 0;
}

// Fonction pour afficher l'AST (bonus)
void afficher_AST(AST *noeud, int niveau) {
    if (!noeud) return;
    for (int i = 0; i < niveau; i++) printf("  ");
    if (noeud->type == AST_Nombre) {
        printf("Nombre: %d\n", noeud->valeur);
    } else if (noeud->type == AST_Operation) {
        printf("Opération: %c\n", noeud->ope.operation);
        afficher_AST(noeud->ope.gauche, niveau + 1);
        afficher_AST(noeud->ope.droite, niveau + 1);
    }
}
