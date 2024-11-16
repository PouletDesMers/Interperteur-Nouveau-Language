#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define MAX_VARS 100

// définit les types possibles de nœuds dans un ast
typedef enum { NODE_NUM, NODE_VAR, NODE_OP } NodeType;

// structure représentant un noeud de l'ast
typedef struct Node {
    NodeType type;
    union {
        int value;
        char var_name[32];
        struct {
            char op;
            struct Node *left;
            struct Node *right;
        } operation;
    };
} Node;

// structure pour une variable stocker dans la table des symboles
typedef struct {
    char name[32];
    int value;
} Variable;

// structure représentant la table des symboles
typedef struct {
    Variable vars[MAX_VARS];
    int size;
} HashTable;

// déclaration des variables
void hash_table_set(const char *name, int value);
int hash_table_get(const char *name);
Node *create_num_node(int value);
Node *create_var_node(const char *var_name);
Node *create_op_node(char op, Node *left, Node *right);

#endif // SYMBOLTABLE_H
