#include <stdlib.h>
#include <stdio.h>
#include "../include/lexer.h"
#include <time.h>
#include <unistd.h>

token ** no_arguments() {
    time_t timestamp;
    char filename[100];
    FILE *fichier = NULL;
    
    time(&timestamp);//création du nom temporaire du fichier "tmp-{timestamp.cbester}"
    snprintf(filename, 100, "tmp-%ld.cbest", timestamp);
    
    if ((fichier = fopen(filename, "w+")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    char input[500];
    while (fgets(input, sizeof(input), stdin) != NULL) {
        fputs(input, fichier);
    }
    token ** tokens=lexer(fichier);
    print_tokens(tokens);
    rewind(fichier);
    fclose(fichier);
    if (remove(filename) != 0) {
        printf("Erreur lors de la suppression du fichier\n");
        exit(1);
    }
    return tokens;
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
    token **tokens;
    if (argc == 1) {
        tokens=no_arguments();
    } else if (argc == 2) {
        tokens=one_argument(argv[1]);
    } else {
        printf("trop d'arguments\n");
        return 1;
    }
    print_tokens(tokens);
    return 0;
}
