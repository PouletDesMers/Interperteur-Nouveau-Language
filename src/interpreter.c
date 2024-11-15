#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/symbolTable.h"
#include "../include/ast.h"

// AST global avec une liste chaînée
AST_Node *global_ast_head = NULL;  // Tête de la liste chaînée des ASTs


void ajouter_ast_global(AST *ast) {
    // Créer un nouveau nœud pour la liste chaînée
    AST_Node *new_node = malloc(sizeof(AST_Node));
    new_node->ast = ast;
    new_node->next = NULL;

    // Si la liste est vide, initialiser la tête de la liste
    if (global_ast_head == NULL) {
        global_ast_head = new_node;
    } else {
        // Sinon, ajouter le nœud à la fin de la liste
        AST_Node *current = global_ast_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void interpret(const char *input) {
    // Tokenisation de l'entrée
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
        if (tokens[indice] && tokens[indice]->type == LPAREN) {
            indice++; // Passer la parenthèse ouvrante
            // Parser l'expression à l'intérieur de print()
            AST *ast = parse_expression(tokens, &indice);
            if (tokens[indice] && tokens[indice]->type == RPAREN) {
                indice++; // Passer la parenthèse fermante
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
        indice += 2; // Passer le nom de la variable et le signe '='
        AST *ast = parse_expression(tokens, &indice);
        if (ast) {
            int result = eval(ast);
            hash_table_set(var_name, result);
            // Libérer l'AST après utilisation
            // (À implémenter si nécessaire)
            ajouter_ast_global(ast);  
        } else {
            printf("Erreur: Expression incorrecte\n");
        }
        return;
    }

    // Sinon, évaluer l'expression mathématique
    AST *ast = parse_expression(tokens, &indice);
    if (ast) {
        int result = eval(ast);
        printf("%d\n", result);
        ajouter_ast_global(ast);  
    } else {
        printf("Erreur: Entrée non reconnue\n");
    }
}


void afficher_AST_global() {
    printf("Affichage de l'AST global après exécution:\n");

    AST_Node *current = global_ast_head;
    while (current != NULL) {
        afficher_AST(current->ast, 0);  // Afficher chaque AST dans la liste
        current = current->next;
    }
}
