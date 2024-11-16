#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/symbolTable.h"
#include "../include/ast.h"

// ast global avec une liste chaînée
AST_Node *global_ast_head = NULL;  // Tête de la liste chaînée des ASTs

// ajouter un ast à une liste chainée globale
void ajouter_ast_global(AST *ast) {
    // Créer un nouveau nœud pour la liste chaînée
    AST_Node *new_node = malloc(sizeof(AST_Node));
    new_node->ast = ast;
    new_node->next = NULL;

    // si la liste est vide, initialiser la tête de la liste
    if (global_ast_head == NULL) {
        global_ast_head = new_node;
    } else {
        // sinon, parcourir la liste jusqu'à la fin pour ajouter le nouveau noeud
        AST_Node *current = global_ast_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// fonction d'interpretation du code source
void interpret(const char *input) {
    // Tokenisation de l'entrée en créant un fichier temporaire en mémoire pour stocker l'entrée et le relire
    FILE *temp_file = tmpfile();
    fputs(input, temp_file);
    rewind(temp_file);
    token **tokens = lexer(temp_file);
    fclose(temp_file);

    if (!tokens[0]) return;

    int indice = 0;

    // Vérifier pour une commande "print"
    if (tokens[indice]->type == IDENTIFIER && strcmp(tokens[indice]->value, "print") == 0) {
        indice++;

        // vérification si le token est une parenthèse pour parser l'expression
        if (tokens[indice] && tokens[indice]->type == LPAREN) {
            indice++;
            AST *ast = parse_expression(tokens, &indice);

            // vérification de la présence de la parenthèse fermante
            if (tokens[indice] && tokens[indice]->type == RPAREN) {
                indice++;

                // évaluer l'ast pour obtenir la valeur de l'expression
                if (ast) {
                    int value = eval(ast);
                    printf("%d\n", value);
                    ajouter_ast_global(ast);  
                } else {
                    printf("Erreur: Expression incorrecte dans print\n");
                }
            } else {
                printf("Erreur: Parenthèse fermante attendue après l'argument de print\n");
            }
        } else {
            printf("Erreur: Parenthèse ouvrante attendue après print\n");
        }
        return;
    }

    // Gérer une assignation de type "x = expression"
    if (tokens[indice]->type == IDENTIFIER && tokens[indice + 1] &&
        tokens[indice + 1]->type == ASSIGN) {
        char *var_name = tokens[indice]->value;
        indice += 2;
        // analyse de l'expression à droite de l'assignation
        AST *ast = parse_expression(tokens, &indice);

        // évaluer l'ast pour obtenir la valeur de l'expression
        if (ast) {
            int result = eval(ast);

            // stocker la valeur dans la table des symboles avec le nom de la variable
            hash_table_set(var_name, result);
            ajouter_ast_global(ast);  
        } else {
            printf("Erreur: Expression incorrecte\n");
        }
        return;
    }

    // sinon, évaluer l'expression mathématique
    AST *ast = parse_expression(tokens, &indice);
    if (ast) {
        int result = eval(ast);
        printf("%d\n", result);
        ajouter_ast_global(ast);  
    } else {
        printf("Erreur: Entrée non reconnue\n");
    }
}

// affichage de l'arbre global
void afficher_AST_global() {
    printf("Affichage de l'AST global après exécution:\n");

    // innitialisation d'un pointeur pour parcourir la liste chainée
    AST_Node *current = global_ast_head;
    while (current != NULL) {
        afficher_AST(current->ast, 0);  // Afficher chaque AST dans la liste
        current = current->next;
    }
}
