#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"

#define MAX_KEYWORDS 10 // nombre max de mot clé
const char *keywords[MAX_KEYWORDS] = { //définir les mot clé
    "if",
    "else",
    "while",
    "for",
    "return",
    "break",
    "continue",
    "switch",
    "case",
    "default"
};

// fonction permettant de créer de nouveaux tokens
token *create_token(type_token type, const char *value) {

    // 'malloc' permet d'allouer suffisamment d'espace pour la structure 'token'
    token *new_token = (token *)malloc(sizeof(token));
    if (new_token == NULL) {
        printf("Erreur : Allocation mémoire échouée pour un jeton.\n");
        exit(1); 
    }

    // assigner le type au nouveau token
    new_token->type = type;

    // vérifier si value n'est pas NULL pour allouer de la mémoire à la valeur
    if (value != NULL) {
        new_token->value = (char *)malloc(strlen(value) + 1);
        if (new_token->value == NULL) {
            printf("Erreur : Allocation mémoire échouée pour la valeur du jeton.\n");
            exit(1);
        }
        strcpy(new_token->value, value);
    } else {
        new_token->value = NULL;
    }
    return new_token;
}

int is_alpha(char c) { // si un caractère est une lettre
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_digit(char c) { // si un caractère est un chiffre
    return c >= '0' && c <= '9';
}

int is_keyword(const char *word) { // si un caractère est un mot clé
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // oui
        }
    }
    return 0; // non
}

type_token get_token_type(char c) { // récupérer le type de token en fonction du caractère
    switch(c) {
        case '(': return LPAREN;
        case ')': return RPAREN;
        case '{': return LBRACE;
        case '}': return RBRACE;
        case ';': return SEMICOLON;
        case '=': return ASSIGN;
        case '+':
        case '-':
        case '*':
        case '/': return OPERATOR;
        default: return IDENTIFIER;
    }
}


token **lexer(FILE *file) {
    int capacity = INITIAL_TOKEN_CAPACITY; // capacité initiale
    token **tokens = (token **)malloc(capacity * sizeof(token *));
    if (tokens == NULL) {
        printf("Erreur : Allocation mémoire échouée pour les tokens.\n");
        exit(1);
    }

    char buffer[MAX_TOKEN_LEN]; // buffer pour stocker les chaînes de caractères
    int token_index = 0;
    char c;

    int is_quote=0;

    // boucle de lecture des caractères du fichier jusqu'à la fin
    while ((c = fgetc(file)) != EOF) {
        if ((c == ' ' && is_quote == 0) || c == '\n') {
            continue; // ignorer les espaces et les sauts de ligne
        }

        if (is_alpha(c)) {
            int i = 0;
            buffer[i++] = c; // stocke le premier caractère alphabétique
            c = fgetc(file);
            while (is_alpha(c) || is_digit(c)||(c == ' ' && is_quote == 1)) {
                buffer[i++] = c; // continue à stocker les caractères valides
                c = fgetc(file);
            }
            buffer[i] = '\0';  
            ungetc(c, file); // remettre le dernier caractère dans le flux

            if (is_keyword(buffer)) { // Vérification des mots-clés
                tokens[token_index++] = create_token(KEYWORD, buffer);
            } else {
                tokens[token_index++] = create_token(IDENTIFIER, buffer);
            }
        } else if (is_digit(c)) {  
            int i = 0;
            buffer[i++] = c; // pour les nombres
            while (is_digit(c = fgetc(file))) {
                buffer[i++] = c;
            }
            buffer[i] = '\0';  
            ungetc(c, file);  // remettre le dernier caractère dans le flux
            tokens[token_index++] = create_token(NUMBER, buffer);
        } else if (c=='"'){
            if(is_quote==1){
                is_quote=0; // fin de la chaîne de caractères
            } else { 
                is_quote=1; // début de la chaîne de caractères
            }
            char tmp[2] = {c, '\0'}; // crée une chaîne avec le caractère guillemet
            tokens[token_index++] = create_token(QUOTE, tmp);
        } else {  
            char tmp[2] = {c, '\0'}; // autres symboles (opérateurs, parenthèses, etc.)
            tokens[token_index++] = create_token(get_token_type(c), tmp);
        }

        if (token_index >= capacity) { // si la capacité du tableau est atteinte, on la double
            capacity *= 2;
            tokens = (token **)realloc(tokens, capacity * sizeof(token *));
            if (tokens == NULL) {
                printf("Erreur : Réallocation mémoire échouée pour les tokens.\n");
                exit(1);
            }
        }
    }

    tokens[token_index] = NULL; // fin du tableau en utilisant NULL comme marqueur

    return tokens; 
}

// retourne une chaîne de caractères correspondant au nom du type Utilisation et convertit un type de token en une chaîne pour l'affichage
const char* token_type_to_string(type_token type) {
    switch (type) {
        case NUMBER: return "NUMBER";
        case KEYWORD: return "KEYWORD";
        case ASSIGN: return "ASSIGN";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case IDENTIFIER: return "IDENTIFIER";
        case OPERATOR: return "OPERATOR";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case SEMICOLON: return "SEMICOLON";
        case QUOTE: return "QUOTE";
        default: return "UNKNOWN";
    }
}

// fonction pour parcourir le tableau de tokens et afficher le type et la valeur de chaque token
void print_tokens(token **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
            printf("Token Type: %s, Value: %s\n", token_type_to_string(tokens[i]->type), tokens[i]->value);
    }
}