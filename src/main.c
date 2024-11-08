#include <stdlib.h>
#include <stdio.h>
#include "../include/parser.h"
#include "../include/interpreter.h"
#include <time.h>
#include <unistd.h>

// token ** no_arguments() {
//     time_t timestamp;
//     char filename[100];
//     FILE *fichier = NULL;
    
//     time(&timestamp);//création du nom temporaire du fichier "tmp-{timestamp.cbester}"
//     snprintf(filename, 100, "tmp-%ld.cbest", timestamp);
    
//     if ((fichier = fopen(filename, "w+")) == NULL) {
//         printf("Erreur lors de l'ouverture du fichier\n");
//         exit(1);
//     }

//     char input[500];
//     printf("Nom du fichier temporaire (Ctrl+D pour terminer) : %s\n", filename);

//     while (fgets(input, sizeof(input), stdin) != NULL) {
//         fputs(input, fichier);
//     }

//     fflush(fichier);  
//     rewind(fichier);  
//     token **tokens = lexer(fichier);

//     if (tokens == NULL) {
//         printf("Erreur lors de l'appel du lexer\n");
//         fclose(fichier);
//         remove(filename);
//         exit(1);
//     }
//     fclose(fichier);  
//     if (remove(filename) != 0) {  
//         printf("Erreur lors de la suppression du fichier\n");
//         exit(1);
//     }
//     return tokens;
// }

token ** no_arguments() {
    printf("Entrée en mode interactif. Tapez 'exit' pour quitter.\n");
    return NULL;  // Le mode interactif ne nécessite pas de token préchargé
}

token ** one_argument(char *filename) {
    FILE *fichier = NULL;
    if ((fichier = fopen(filename, "r")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    token ** tokens=lexer(fichier);
    fclose(fichier);
    return tokens;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // Mode interactif avec REPL (Read-Eval-Print Loop)
        char input[256];
        while (1) {
            printf("> ");
            if (fgets(input, sizeof(input), stdin) == NULL) break; // Fin si CTRL+D
            if (strcmp(input, "exit\n") == 0) break; // Commande 'exit'
            interpret(input); // Interpréter l'entrée
        }
    } else if (argc == 2) {
        // Mode fichier : lire les instructions depuis le fichier fourni
        token **tokens = one_argument(argv[1]);
        int index = 0;
        while (tokens[index]) {
            interpret(tokens[index]->value);
            index++;
        }
    } else {
        printf("Erreur : trop d'arguments\n");
        return 1;
    }
    return 0;
}l
