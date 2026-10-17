// BST insertion and deletion
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *left, *right;
} Node;
static Node *insert(Node *root, int value, int *ok) {
    if (root == NULL) {
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            *ok = 0;
            return NULL;
        }
        node->value = value;
        node->left = node->right = NULL;
        return node;
    }
    if (value < root->value) root->left = insert(root->left, value, ok);
    else if (value > root->value) root->right = insert(root->right, value, ok);
    else puts("Duplicate value ignored.");
    return root;
}
static Node *search(Node *root, int value) {
    while (root != NULL && root->value != value) root = value < root->value ? root->left : root->right;
    return root;
}
static Node *minimum(Node *root) {
    while (root->left != NULL) root = root->left;
    return root;
}
static Node *deleteValue(Node *root, int value, int *found) {
    if (root == NULL) return NULL;
    if (value < root->value) root->left = deleteValue(root->left, value, found);
    else if (value > root->value) root->right = deleteValue(root->right, value, found);
    else {
        *found = 1;
        if (root->left == NULL || root->right == NULL) {
            Node *child = root->left != NULL ? root->left : root->right;
            free(root);
            return child;
        }
        Node *successor = minimum(root->right);
        root->value = successor->value;
        int ignored = 0;
        root->right = deleteValue(root->right, successor->value, &ignored);
    }
    return root;
}
static void inorder(const Node *p) {
    if (p != NULL) {
        inorder(p->left);
        printf("%d ", p->value);
        inorder(p->right);
    }
}
static void preorder(const Node *p) {
    if (p != NULL) {
        printf("%d ", p->value);
        preorder(p->left);
        preorder(p->right);
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
    Node *root = NULL;
    int choice, value;
    do {
        puts("\n1.Insert  2.Search  3.Delete  4.Traversals  0.Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            freeTree(root);
            return 1;
        }
        if (choice == 1) {
            int ok = 1;
            printf("Value: ");
            if (scanf("%d", &value) != 1) {
                freeTree(root);
                return 1;
            }
            root = insert(root, value, &ok);
            if (!ok) puts("Memory allocation failed.");
            else puts("Insert complete.");
        }
        else if (choice == 2) {
            printf("Value: ");
            if (scanf("%d", &value) != 1) {
                freeTree(root);
                return 1;
            }
            puts(search(root, value) != NULL ? "Element found." : "Element not found.");
        }
        else if (choice == 3) {
            int found = 0;
            printf("Value: ");
            if (scanf("%d", &value) != 1) {
                freeTree(root);
                return 1;
            }
            root = deleteValue(root, value, &found);
            puts(found ? "Element deleted." : "Element not found.");
        }
        else if (choice == 4) {
            if (root == NULL) puts("Tree is empty.");
            else {
                printf("Inorder:   ");
                inorder(root);
                printf("\nPreorder:  ");
                preorder(root);
                printf("\nPostorder: ");
                postorder(root);
                putchar('\n');
            }
        }
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    freeTree(root);
    return 0;
}
