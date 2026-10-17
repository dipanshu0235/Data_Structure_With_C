// Count Nodes
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *next;
} Node;
int main(void) {
    Node *head = NULL, **tail = &head;
    int n, value, count = 0;
    printf("Number of nodes to create (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &value) != 1) {
            while (head != NULL) {
                Node *next = head->next;
                free(head);
                head = next;
            }
            return 1;
        }
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            puts("Memory allocation failed.");
            while (head != NULL) {
                Node *next = head->next;
                free(head);
                head = next;
            }
            return 1;
        }
        node->value = value;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }
    for (Node *p = head; p != NULL; p = p->next) ++count;
    printf("Node count: %d\n", count);
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
    return 0;
}
