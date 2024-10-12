#include "../include/parser.h"


void parser(token ** tokens){
    for (int i = 0; tokens[i] != NULL; i++)
    {
        if(tokens[i]->type==SEMICOLON){
        printf("%d ",tokens[i]->type);
        printf("%s\n",tokens[i]->value);
        }
    }
    
}
