#ifndef AST_H
#define AST_H

// Définition d'un type énuméré pour les types de nœuds de l'AST
typedef enum { AST_Nombre, AST_Operation } ASType;

// Définition de la structure principale de l'AST
typedef struct AST {
    ASType type; // Indique si le nœud est un nombre ou une opération
    union {
        int valeur; // Si le nœud est un nombre, stocke sa valeur entière
        struct {
            char operation; // Le symbole de l'opération ('+', '-', '*', '/')
            struct AST *gauche; // Pointeur vers le sous-nœud gauche
            struct AST *droite; // Pointeur vers le sous-nœud droit
        } ope; // Utilisé si le nœud est une opération
    };
} AST;

// Définition d'une structure pour une liste chaînée de nœuds AST avec des pointeur pour les noeuds de la liste
typedef struct AST_Node {
    AST *ast;
    struct AST_Node *next;
} AST_Node;

// Déclaration de fonctions pour créer des nœuds de l'AST
AST *noeud_nombre(int valeur);
AST *noeud_operation(char operation, AST *gauche, AST *droite);

// Déclaration d'une fonction pour afficher l'AST (facultatif)
void afficher_AST(AST *noeud, int niveau);

// Déclaration d'une fonction pour évaluer l'AST et retourner le résultat de l'expression
int eval(AST *noeud);

#endif // AST_H
