#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Types de nœuds dans l'arbre d'expression
typedef enum { NODE_NUM, NODE_VAR, NODE_OP } NodeType;

// Structure d'un nœud d'arbre, qui peut être un nombre, une variable, ou une opération
typedef struct Node {
    NodeType type;  // Type de nœud
    union {
        int value;  // Si le nœud est un nombre, on stocke sa valeur ici
        char var_name[32];  // Si c'est une variable, on stocke son nom ici
        struct {
            char op;  // L'opération (+, -, *, /)
            struct Node *left;  // Sous-arbre gauche
            struct Node *right;  // Sous-arbre droit
        } operation;
    };
} Node;

// Structure pour stocker les variables et leurs valeurs
typedef struct {
    char name[32];
    int value;
} Variable;

typedef struct {
    Variable vars[100];  // Tableau pour stocker jusqu'à 100 variables
    int size;  // Nombre de variables stockées
} HashTable;

// Table des variables globales
HashTable variables = { .size = 0 };

// Fonction pour ajouter ou mettre à jour une variable
void hash_table_set(const char *name, int value) {
    for (int i = 0; i < variables.size; i++) {
        if (strcmp(variables.vars[i].name, name) == 0) {  // Si la variable existe
            variables.vars[i].value = value;  // Mettre à jour la valeur
            return;
        }
    }
    // Si la variable n'existe pas, on l'ajoute
    strcpy(variables.vars[variables.size].name, name);
    variables.vars[variables.size].value = value;
    variables.size++;
}

// Fonction pour récupérer la valeur d'une variable
int hash_table_get(const char *name) {
    for (int i = 0; i < variables.size; i++) {
        if (strcmp(variables.vars[i].name, name) == 0) {  // Si on trouve la variable
            return variables.vars[i].value;  // Retourner sa valeur
        }
    }
    // Si la variable n'est pas trouvée, afficher une erreur
    printf("Erreur: Variable %s non définie\n", name);
    return 0;
}

// Crée un nœud de nombre
Node *create_num_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_NUM;
    node->value = value;
    return node;
}

// Crée un nœud de variable
Node *create_var_node(const char *var_name) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_VAR;
    strcpy(node->var_name, var_name);
    return node;
}

// Crée un nœud d'opération avec des sous-nœuds
Node *create_op_node(char op, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->type = NODE_OP;
    node->operation.op = op;
    node->operation.left = left;
    node->operation.right = right;
    return node;
}

// Fonction d'évaluation : calcule la valeur du nœud
int eval(Node *node) {
    if (node->type == NODE_NUM) {  // Si c'est un nombre, retourne la valeur
        return node->value;
    }
    if (node->type == NODE_VAR) {  // Si c'est une variable, retourne sa valeur
        return hash_table_get(node->var_name);
    }
    if (node->type == NODE_OP) {  // Si c'est une opération, calcule le résultat
        int left_val = eval(node->operation.left);  // Évalue le sous-arbre gauche
        int right_val = eval(node->operation.right);  // Évalue le sous-arbre droit
        switch (node->operation.op) {  // Applique l'opération correspondante
            case '+': return left_val + right_val;
            case '-': return left_val - right_val;
            case '*': return left_val * right_val;
            case '/': return left_val / right_val;
        }
    }
    return 0;  // Valeur par défaut si aucun cas ne correspond
}

// Interprète une instruction d'assignation
void interpret_assignment(const char *var_name, Node *expression) {
    int result = eval(expression);  // Évalue l'expression
    hash_table_set(var_name, result);  // Associe le résultat à la variable
}

// Interprète une instruction d'affichage de variable
void interpret_print(const char *var_name) {
    int value = hash_table_get(var_name);  // Récupère la valeur de la variable
    printf("%d\n", value);  // Affiche la valeur
}

// Fonction principale
int main() {
    // Crée une expression "56 * 10"
    Node *expression = create_op_node('*', create_num_node(56), create_num_node(10));

    // Assigne le résultat de l'expression à la variable "x"
    interpret_assignment("x", expression);

    // Affiche la valeur de la variable "x"
    interpret_print("x");

    // Libère la mémoire utilisée par l'expression
    free(expression);

    return 0;
}
