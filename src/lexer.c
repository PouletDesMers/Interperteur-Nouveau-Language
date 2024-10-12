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

token *create_token(type_token type, const char *value) {
    token *new_token = (token *)malloc(sizeof(token));
    if (new_token == NULL) {
        printf("Erreur : Allocation mémoire échouée pour un jeton.\n");
        exit(1); 
    }
    new_token->type = type;
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

int is_alpha(char c) { // si une lettre
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_digit(char c) { // si un chiffre
    return c >= '0' && c <= '9';
}

int is_keyword(const char *word) { // si mot clé
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // oui
        }
    }
    return 0; // non
}

type_token get_token_type(char c) { // récupérer le type
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

    char buffer[MAX_TOKEN_LEN]; // taille max du chaine
    int token_index = 0;
    char c;

    int is_quote=0;
    while ((c = fgetc(file)) != EOF) {
        if ((c == ' ' && is_quote == 0) || c == '\n') {
            continue;
        }

        if (is_alpha(c)) {
            int i = 0;
            buffer[i++] = c; // pour les chaînes de caractères
            c = fgetc(file);
            while (is_alpha(c) || is_digit(c)||(c == ' ' && is_quote == 1)) {
                buffer[i++] = c;
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
                is_quote=0;
            } else { 
                is_quote=1;
            }
            char tmp[2] = {c, '\0'};
            tokens[token_index++] = create_token(QUOTE, tmp);
        } else {  
            char tmp[2] = {c, '\0'};
            tokens[token_index++] = create_token(get_token_type(c), tmp);
        }

        if (token_index >= capacity) { // capacité dynamique
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

void print_tokens(token **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
            printf("Token Type: %s, Value: %s\n", token_type_to_string(tokens[i]->type), tokens[i]->value);
    }
}