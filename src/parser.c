#include "../include/parser.h"


void parser(token ** tokens){
    for (int i = 0; tokens[i] != NULL; i++)
    {
       switch (tokens[i]->type) { //switch case pour suivre en fonction de quel type a été récupéré
        case SEMICOLON:
        printf("%d\n",tokens[i]->type); //affiche le type de tokens
            printf("%d\n", tokens[i]->value); //affiche la valeur de tokens
            break; 

            case NUMBER: 
            printf("%d\n",tokens[i]->type);
            printf("%d\n", tokens[i]->value);
            break;

            case OPERATOR: 
            printf("%d\n",tokens[i]->type);
            printf("%d\n", tokens[i]->value);

            if(strcmp(tokens[i]->value, "*") == 0 || strcmp(tokens[i]->value, "/")==0){ //compare entre le symbole * et /
            printf("%d\n", tokens[i]->type);
            printf("%d\n", tokens[i]->value);
            } 
            else if (strcmp (tokens[i]->value, "+")==0 || strcmp(tokens[i]->value, "-")==0){
            printf("%d\n", tokens[i]->type);
            printf("%d\n", tokens[i]->value);
            }

    }
    }
    
}
