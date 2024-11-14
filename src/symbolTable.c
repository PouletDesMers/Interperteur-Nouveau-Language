#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/symbolTable.h"

// Tableau de hachage pour stocker les variables
HashTable variables = { .size = 0 };

// Ajouter ou mettre à jour une variable dans la table de symboles
void hash_table_set(const char *name, int value) {
    for (int i = 0; i < variables.size; i++) {
        if (strcmp(variables.vars[i].name, name) == 0) {
            variables.vars[i].value = value;
            return;
        }
    }
    strcpy(variables.vars[variables.size].name, name);
    variables.vars[variables.size].value = value;
    variables.size++;
}

int hash_table_get(const char *name) {
    for (int i = 0; i < variables.size; i++) {
        if (strcmp(variables.vars[i].name, name) == 0) {
            return variables.vars[i].value;
        }
    }
    printf("Erreur: Variable %s non définie\n", name);
    return 0;
}

Node *create_num_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_NUM;
    node->value = value;
    return node;
}

Node *create_var_node(const char *var_name) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_VAR;
    strcpy(node->var_name, var_name);
    return node;
}

Node *create_op_node(char op, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_OP;
    node->operation.op = op;
    node->operation.left = left;
    node->operation.right = right;
    return node;
}