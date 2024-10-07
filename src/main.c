#include <stdlib.h>
#include <stdio.h>
#include "../include/lexer.h"


int main(int argc, char ** argv){
    if(argc==1){ // si pas d'argument
        printf("mode console(à faire)");
        return 0;
    }else if(argc==2){ // si un argument
        FILE * fichier=NULL;
        if((fichier=fopen(argv[1],"r"))==NULL){
            printf("Erreur lors de l'ouverture du fichier");
            return 1;
        }
        token* tokens=lexer(fichier);
        fclose(fichier);
        print_tokens(tokens);
        return 0;
    }else{ // si + de un argument
        printf("trop d'argument");
        return 1;
    }
}