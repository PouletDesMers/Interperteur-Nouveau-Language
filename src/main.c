#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/interpreter.h"

void file_mode(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t size_line = 64; 
    char *line = malloc(size_line);
    while (fgets(line, size_line, file)) {
        while (strchr(line, '\n') == NULL && !feof(file)) {
            size_line *= 2;
            char *new_line = realloc(line, size_line);
            line = new_line;
        }

        line[strcspn(line, "\n")] = '\0';

        interpret(line);
    }

    free(line);
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // Mode interactif avec REPL (Read-Eval-Print Loop)
        printf("Mode interactif. Tapez 'exit' pour quitter.\n");
        size_t size_input = 64; 
        char *input = malloc(size_input);
        while (1) {
            printf("> ");
            
            // Lire l'entrée utilisateur
            if (!fgets(input, size_input, stdin)) break; // Fin si CTRL+D

            while (input[strlen(input) - 1] != '\n' && !feof(stdin)) {
                size_input *= 2;
                char *new_input = realloc(input, size_input);
                input = new_input;
            }

            // Enlever le saut de ligne à la fin
            input[strcspn(input, "\n")] = '\0';

            // Vérifier la commande 'exit'
            if (strcmp(input, "exit") == 0) break;// Commande 'exit'
            interpret(input);
        }
        free(input);
    } else if (argc == 2) {
        // Mode fichier : lire les instructions depuis le fichier fourni
        file_mode(argv[1]);
    } else {
        printf("Usage: %s [nom_du_fichier]\n", argv[0]);
        return 1;
    }

    // Afficher l'AST global après l'exécution du programme
    afficher_AST_global();
    return 0;
}
