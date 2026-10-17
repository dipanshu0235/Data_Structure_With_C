// Binary Tree Traversals
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *left, *right;
} Node;
static void preorder(const Node *p) {
    if (p != NULL) {
        printf("%d ", p->value);
        preorder(p->left);
        preorder(p->right);
    }
}
static void inorder(const Node *p) {
    if (p != NULL) {
        inorder(p->left);
        printf("%d ", p->value);
        inorder(p->right);
    }
}
static void postorder(const Node *p) {
    if (p != NULL) {
        postorder(p->left);
        postorder(p->right);
        printf("%d ", p->value);
    }
}
static void freeTree(Node *p) {
    if (p != NULL) {
        freeTree(p->left);
        freeTree(p->right);
        free(p);
    }
}
int main(void) {
    Node *nodes[100], *root = NULL;
    int n;
    printf("Number of nodes (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    puts("Enter node values in level order (left child before right child):");
    for (int i = 0; i < n; ++i) {
        nodes[i] = malloc(sizeof(*nodes[i]));
        if (nodes[i] == NULL) {
            for (int j = 0; j < i; ++j) free(nodes[j]);
            puts("Memory allocation failed.");
            return 1;
        }
        if (scanf("%d", &nodes[i]->value) != 1) {
            for (int j = 0; j <= i; ++j) free(nodes[j]);
            return 1;
        }
        nodes[i]->left = nodes[i]->right = NULL;
    }
    if (n > 0) {
        root = nodes[0];
        for (int i = 0; i < n; ++i) {
            int left = 2 * i + 1;
            if (left < n) nodes[i]->left = nodes[left];
            if (left + 1 < n) nodes[i]->right = nodes[left + 1];
        }
    }
    if (root == NULL) puts("Tree is empty.");
    else {
        printf("Preorder:  ");
        preorder(root);
        printf("\nInorder:   ");
        inorder(root);
        printf("\nPostorder: ");
        postorder(root);
        putchar('\n');
    }
    freeTree(root);
    return 0;
}
