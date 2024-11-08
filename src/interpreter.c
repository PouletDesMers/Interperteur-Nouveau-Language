#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/symbolTable.h"

// Fonction d'interprétation principale
void interpret(const char *input) {
    // Tokenisation de l'entrée
    FILE *temp_file = tmpfile();
    fputs(input, temp_file);
    rewind(temp_file);
    token **tokens = lexer(temp_file);
    fclose(temp_file);

    // Vérifier pour une commande "print"
    if (tokens[0] && tokens[0]->type == IDENTIFIER && strcmp(tokens[0]->value, "print") == 0) {
        if (tokens[1] && tokens[1]->type == IDENTIFIER) {
            int value = hash_table_get(tokens[1]->value);
            printf("%d\n", value);
        } else {
            printf("Erreur: print nécessite une variable\n");
        }
        return;
    }

    // Gérer une assignation de type "x = expression"
    if (tokens[1] && tokens[1]->type == ASSIGN) {
        if (tokens[0]->type == IDENTIFIER) {
            char *var_name = tokens[0]->value;
            int index = 2;
            AST *ast = parse_nombre(tokens, &index);
            if (ast) {
                int result = eval(ast);
                hash_table_set(var_name, result);
                free(ast);
            } else {
                printf("Erreur: expression incorrecte\n");
            }
        } else {
            printf("Erreur: format de variable incorrect\n");
        }
        return;
    }

    // Évaluer l'expression mathématique
    int index = 0;
    AST *ast = parser(tokens);
    if (ast) {
        int result = eval(ast);
        printf("%d\n", result);
        free(ast);
    }
}
