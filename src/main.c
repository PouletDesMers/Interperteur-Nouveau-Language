#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/interpreter.h"

// mode fichier : lit et interprète les instructions depuis un fichier
void file_mode(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t size_line = 64; 
    char *line = malloc(size_line);

    // lit une ligne du fichier jusqu'à la fin du fichier ou jusqu'à ce qu'une nouvelle ligne soit rencontrée
    while (fgets(line, size_line, file)) {
        // si le saut de ligne n'est pas trouvé dans la ligne lue et que ce n'est pas la fin du fichier
        while (strchr(line, '\n') == NULL && !feof(file)) {
            size_line *= 2;
            char *new_line = realloc(line, size_line); // réalloue de la mémoire
            line = new_line;
        }

        // supprime le caractère '\n' à la fin de la ligne s'il est présent
        line[strcspn(line, "\n")] = '\0';

        // interpreter la ligne lue
        interpret(line);
    }

    free(line);
    fclose(file);
}

// fonction principale du programme
int main(int argc, char **argv) {
    // vérification du nombre d'argument fourni, ici mode interactif
    if (argc == 1) {
        // Mode interactif avec REPL (Read-Eval-Print Loop)
        printf("Mode interactif. Tapez 'exit' pour quitter.\n");
        size_t size_input = 64; 
        char *input = malloc(size_input);
        while (1) {
            printf("> ");
            
            // lire l'entrée utilisateur
            if (!fgets(input, size_input, stdin)) break; // fin du programme si CTRL+D

            // si l'utilisateur a rentré une ligne plus longue que le buffer, on réaloue de la mémoire
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
        // mode fichier : lire les instructions depuis le fichier fourni
        file_mode(argv[1]);
    } else {
        printf("Vous ne pouvez pas utiliser plusieurs arguments.\nLa commande utilisee doit etre : %s [nom_du_fichier]\n", argv[0]);
        return 1;
    }

    // Afficher l'AST global après l'exécution du programme
    afficher_AST_global();
    return 0;
}
