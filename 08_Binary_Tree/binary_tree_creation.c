// Binary tree creation
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *left, *right;
} Node;
static void inorder(const Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
}
static void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main(void) {
    Node *nodes[100], *root = NULL;
    int n;
    printf("Number of nodes (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    for (int i = 0; i < n; ++i) {
        int value;
        printf("Level-order value %d: ", i + 1);
        if (scanf("%d", &value) != 1) {
            for (int j = 0; j < i; ++j) free(nodes[j]);
            return 1;
        }
        nodes[i] = malloc(sizeof(*nodes[i]));
        if (nodes[i] == NULL) {
            for (int j = 0; j < i; ++j) free(nodes[j]);
            puts("Memory allocation failed.");
            return 1;
        }
        nodes[i]->value = value;
        nodes[i]->left = nodes[i]->right = NULL;
    }
    if (n > 0) {
        root = nodes[0];
        for (int i = 0; i < n; ++i) {
            int left = 2 * i + 1, right = left + 1;
            if (left < n) nodes[i]->left = nodes[left];
            if (right < n) nodes[i]->right = nodes[right];
        }
    }
    if (root == NULL) puts("Tree is empty.");
    else {
        printf("Tree created. Inorder display: ");
        inorder(root);
        putchar('\n');
    }
    freeTree(root);
    return 0;
}
