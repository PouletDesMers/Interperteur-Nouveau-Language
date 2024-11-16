#ifndef AST_H
#define AST_H

typedef enum { AST_Nombre, AST_Operation } ASType;

typedef struct AST {
    ASType type; // nombre ou opération
    union {
        int valeur; // si nombre
        struct {
            char operation;
            struct AST *gauche; // sous-nœuds gauche et droit
            struct AST *droite;
        } ope; // pour les opérations +, -, *, /
    };
} AST;

typedef struct AST_Node {
    AST *ast; 
    struct AST_Node *next;
} AST_Node;

// Fonctions pour créer des nœuds AST
AST *noeud_nombre(int valeur);
AST *noeud_operation(char operation, AST *gauche, AST *droite);

// Fonction pour afficher l'AST (bonus)
void afficher_AST(AST *noeud, int niveau);

// Fonction pour évaluer l'AST
int eval(AST *noeud);

#endif // AST_H
