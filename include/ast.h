#ifndef AST_H
#define AST_H

// définition d'un type énuméré pour les types de nœuds de l'AST
typedef enum { AST_Nombre, AST_Operation } ASType;

// définition de la structure principale de l'AST
typedef struct AST {
    ASType type; // indique si le nœud est un nombre ou une opération
    union {
        int valeur; // si le nœud est un nombre, stocke sa valeur entière
        struct {
            char operation; // le symbole de l'opération ('+', '-', '*', '/')
            struct AST *gauche; // pointeur vers le sous-nœud gauche
            struct AST *droite; // pointeur vers le sous-nœud droit
        } ope; // utilisé si le nœud est une opération
    };
} AST;

// définition d'une structure pour une liste chaînée de nœuds AST avec des pointeur pour les noeuds de la liste
typedef struct AST_Node {
    AST *ast;
    struct AST_Node *next;
} AST_Node;

// déclaration de fonctions pour créer des nœuds de l'AST
AST *noeud_nombre(int valeur);
AST *noeud_operation(char operation, AST *gauche, AST *droite);

// déclaration d'une fonction pour afficher l'AST
void afficher_AST(AST *noeud, int niveau);

// déclaration d'une fonction pour évaluer l'AST et retourner le résultat de l'expression
int eval(AST *noeud);

#endif // AST_H
