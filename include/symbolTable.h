#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define MAX_VARS 100

typedef enum { NODE_NUM, NODE_VAR, NODE_OP } NodeType;

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

typedef struct {
    char name[32];
    int value;
} Variable;

typedef struct {
    Variable vars[MAX_VARS];
    int size;
} HashTable;

void hash_table_set(const char *name, int value);
int hash_table_get(const char *name);
Node *create_num_node(int value);
Node *create_var_node(const char *var_name);
Node *create_op_node(char op, Node *left, Node *right);

#endif // SYMBOLTABLE_H
