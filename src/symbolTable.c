#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/symbolTable.h"

// tableau de hachage pour stocker les variables
HashTable variables = { .size = 0 };

// ajouter ou mettre à jour une variable dans la table de symboles
void hash_table_set(const char *name, int value) {
    for (int i = 0; i < variables.size; i++) {
        if (strcmp(variables.vars[i].name, name) == 0) {
            // si une variable avec le même nom existe déjà, mettre à jour sa valeur
            variables.vars[i].value = value;
            return;
        }
    }
    // copie le nom de la variable dans le tableau 'vars' à l'indice 'variables.size'
    strcpy(variables.vars[variables.size].name, name);
    // association de la valeur à la variable
    variables.vars[variables.size].value = value;
    variables.size++;
}

// fonction pour trouver une variable avec le nom spécifié
int hash_table_get(const char *name) {
    for (int i = 0; i < variables.size; i++) {
        if (strcmp(variables.vars[i].name, name) == 0) {
            // retourner la valeur de la variable si elle est trouvée
            return variables.vars[i].value;
        }
    }
    printf("Erreur: Variable %s non définie\n", name);
    return 0;
}

// fonction pour créer un nouveau noeud
Node *create_num_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_NUM;
    node->value = value;
    return node;
}

// fonction pour créer une variable
Node *create_var_node(const char *var_name) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_VAR;
    strcpy(node->var_name, var_name);
    return node;
}

// fonction pour créer une opération
Node *create_op_node(char op, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_OP;
    node->operation.op = op;
    node->operation.left = left;
    node->operation.right = right;
    return node;
}