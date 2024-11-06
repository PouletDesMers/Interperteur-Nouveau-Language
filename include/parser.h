#include "lexer.h"


//void parser(token ** tokens);
typedef enum {AST_Nombre, AST_Operation} ASType;
typedef struct AST {
    ASType type; //nombre ou operation
    union {
        int valeur; //si nombre
        struct {
            char operation;
            struct AST *gauche; //parcourir 
            struct AST *droite;
        } ope; //inclus + - * et / 
    };
} AST;


AST *noeud_nombre(int valeur);//crée le noeud nombre
AST *noeud_operation(char operation, AST *gauche, AST *droite);
AST *parse_facteur(token **tokens, int *indice);
AST *parse_operation(token **tokens, int *indice);
AST *parse_nombre(token **tokens, int *indice);
AST *parser(token **tokens);
void parseuraffichage(AST *noeud);