#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h"
#include "../include/symbolTable.h"

// créer un nœud de type nombre et sa valeur
AST *noeud_nombre(int valeur) {
    // alloue de la mémoire pour le nouveau noeud
    AST *noeud = malloc(sizeof(AST));
    // définit le type du nœud comme un nombre
    noeud->type = AST_Nombre;
    // stocke la valeur entière dans le champ 'valeur' du nœud
    noeud->valeur = valeur;
    // retourne le pointeur vers le nouveau nœud
    return noeud;
}

// créer un nœud AST de type opération
AST *noeud_operation(char operation, AST *gauche, AST *droite) {
    // alloue de la mémoire pour le nouveau noeud
    AST *noeud = malloc(sizeof(AST));
    // le type du noeud est une opération
    noeud->type = AST_Operation;
    // stocke le caractere de l'opération
    noeud->ope.operation = operation;
    // associent les sous noeuds gauche et droite à l'opération
    noeud->ope.gauche = gauche;
    noeud->ope.droite = droite;
    return noeud;
}

// évaluateur de l'ast qui retourne le résultat de l'expression
int eval(AST *noeud) {
    // si le noeud est un nombre alors la condition retourne sa valeur
    if (noeud->type == AST_Nombre) {
        return noeud->valeur;
        // si le noeud est une opération, il y a une analyse des sous noeuds, de l'opérateur puis effectue les opérations
    } else if (noeud->type == AST_Operation) {
        int gauche = eval(noeud->ope.gauche);
        int droite = eval(noeud->ope.droite);
        switch (noeud->ope.operation) {
            case '+': return gauche + droite;
            case '-': return gauche - droite;
            case '*': return gauche * droite;
            case '/':
            // condition de vérification de la division
                if (droite == 0) {
                    printf("Erreur: Division par zéro\n");
                    exit(1);
                }
                return gauche / droite;
            default:
                // Si l'opération n'est pas reconnue
                printf("Erreur: Opération inconnue '%c'\n", noeud->ope.operation);
                exit(1);
        }
    }
    return 0;
}

// Fonction pour afficher l'ast de façon structurée
void afficher_AST(AST *noeud, int niveau) {
    // vérification du noeud s'il est null ou non
    if (!noeud) {
        printf("AST vide au niveau %d\n", niveau);
        return;
    }

    // boucle pour indenter en fonction du niveau dans l'arbre
    for (int i = 0; i < niveau; i++) printf("  ");

    // vérification du type de noeud et affichage du type et de la valeur
    if (noeud->type == AST_Nombre) {
        printf("Nombre: %d\n", noeud->valeur);
    } else if (noeud->type == AST_Operation) {
        printf("Opération: %c\n", noeud->ope.operation);
        afficher_AST(noeud->ope.gauche, niveau + 1);
        afficher_AST(noeud->ope.droite, niveau + 1);
    }
}
