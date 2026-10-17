// Linked list search
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *next;
} Node;
static void clear(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}
int main(void) {
    Node *head = NULL, **tail = &head;
    int n, value, key, position = 1, found = 0;
    printf("Number of nodes (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &value) != 1) {
            clear(head);
            return 1;
        }
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            clear(head);
            puts("Memory allocation failed.");
            return 1;
        }
        node->value = value;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }
    printf("Value to search: ");
    if (scanf("%d", &key) != 1) {
        clear(head);
        return 1;
    }
    for (Node *p = head; p != NULL; p = p->next, ++position) if (p->value == key) {
        printf("Found at position %d.\n", position);
        found = 1;
    }
    if (!found) puts("Element not found.");
    clear(head);
    return 0;
}
