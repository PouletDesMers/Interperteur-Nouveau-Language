#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// typedef enum { NODE_NUM, NODE_VAR, NODE_OP } NodeType;

// typedef struct Node {
//     NodeType type;
//     union {
//         int value;
//         char var_name[32];
//         struct {
//             char op;
//             struct Node *left;
//             struct Node *right;
//         } operation;
//     };
// } Node;

// typedef struct {
//     char name[32];
//     int value;
// } Variable;

// typedef struct {
//     Variable vars[100];
//     int size;
// } HashTable;

// HashTable variables = { .size = 0 };

// void hash_table_set(const char *name, int value) {
//     for (int i = 0; i < variables.size; i++) {
//         if (strcmp(variables.vars[i].name, name) == 0) {
//             variables.vars[i].value = value;
//             return;
//         }
//     }
//     strcpy(variables.vars[variables.size].name, name);
//     variables.vars[variables.size].value = value;
//     variables.size++;
// }

// int hash_table_get(const char *name) {
//     for (int i = 0; i < variables.size; i++) {
//         if (strcmp(variables.vars[i].name, name) == 0) {
//             return variables.vars[i].value;
//         }
//     }
//     printf("Erreur: Variable %s non définie\n", name);
//     return 0;
// }

// Node *create_num_node(int value) {
//     Node *node = malloc(sizeof(Node));
//     node->type = NODE_NUM;
//     node->value = value;
//     return node;
// }

// Node *create_var_node(const char *var_name) {
//     Node *node = malloc(sizeof(Node));
//     node->type = NODE_VAR;
//     strcpy(node->var_name, var_name);
//     return node;
// }

// Node *create_op_node(char op, Node *left, Node *right) {
//     Node *node = malloc(sizeof(Node));
//     node->type = NODE_OP;
//     node->operation.op = op;
//     node->operation.left = left;
//     node->operation.right = right;
//     return node;
// }

// int eval(Node *node) {
//     if (node->type == NODE_NUM) {
//         return node->value;
//     }
//     if (node->type == NODE_VAR) {
//         return hash_table_get(node->var_name);
//     }
//     if (node->type == NODE_OP) {
//         int left_val = eval(node->operation.left);
//         int right_val = eval(node->operation.right);
//         switch (node->operation.op) {
//             case '+': return left_val + right_val;
//             case '-': return left_val - right_val;
//             case '*': return left_val * right_val;
//             case '/': return left_val / right_val;
//         }
//     }
//     return 0;
// }

void interpret_assignment(const char *var_name, Node *expression) {
    int result = eval(expression);
    hash_table_set(var_name, result);
}

void interpret_print(const char *var_name) {
    int value = hash_table_get(var_name);
    printf("%d\n", value);
}

int main() {
    Node *expression = create_op_node('*', create_num_node(25), create_num_node(10));
    interpret_assignment("x", expression);
    interpret_print("x");

    free(expression);

    return 0;
}
