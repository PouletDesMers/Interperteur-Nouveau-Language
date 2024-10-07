#include <stdlib.h>
#include <stdio.h>
#include "../include/lexer.h"
#include <time.h>
#include <unistd.h>

void file_to_lexer(FILE *fichier) {
    token* tokens = lexer(fichier);
    print_tokens(tokens);
    free(tokens);
}

void no_arguments() {
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

    rewind(fichier);
    file_to_lexer(fichier);
    fclose(fichier);

    if (remove(filename) != 0) {
        printf("Erreur lors de la suppression du fichier\n");
        exit(1);
    }
}

void one_argument(char *filename) {
    FILE *fichier = NULL;
    if ((fichier = fopen(filename, "r")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    file_to_lexer(fichier);
    fclose(fichier);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        no_arguments();
        return 0;
    } else if (argc == 2) {
        one_argument(argv[1]);
        return 0;
    } else {
        printf("trop d'arguments\n");
        return 1;
    }
}
