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

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Enlever le saut de ligne à la fin
        line[strcspn(line, "\n")] = '\0';
        interpret(line);
    }

    fclose(file);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // Mode interactif avec REPL (Read-Eval-Print Loop)
        char input[256];
        printf("Mode interactif. Tapez 'exit' pour quitter.\n");
        while (1) {
            printf("> ");
            if (fgets(input, sizeof(input), stdin) == NULL) break; // Fin si CTRL+D
            // Enlever le saut de ligne à la fin
            input[strcspn(input, "\n")] = '\0';
            if (strcmp(input, "exit") == 0) break; // Commande 'exit'
            interpret(input); // Interpréter l'entrée
        }
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
