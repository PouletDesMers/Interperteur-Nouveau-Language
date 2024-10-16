#include "../include/parser.h"


void parser(token ** tokens){
    for (int i = 0; tokens[i] != NULL; i++)
    {
        if(tokens[i]->type==SEMICOLON){ // si dans les tokens le caractère semicolone apparait 
        printf("%d ",tokens[i]->type); // alors afficher son typ 
        printf("%s\n",tokens[i]->value); // et sa valeur
        }
        if(tokens[i]->type==NUMBER){ // même chose pour les numéros
            printf("%d\n",tokens[i]->type); 
            printf("%d\n",tokens[i]->value); 
            
        }
        if(tokens[i]->type==OPERATOR){ // et les opérateurs
            printf("%d\n",tokens[i]->type);
            printf("%d\n", tokens[i]->value);
            if (tokens[OPERATOR]=="*" || "/"){
                printf("%d\n", tokens[OPERATOR]->value); 
            }
            else {
                printf("+" || "-");
            }
        }
    }
    
}
