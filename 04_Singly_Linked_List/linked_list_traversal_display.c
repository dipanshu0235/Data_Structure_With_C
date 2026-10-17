// Linked list traversal
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
    int n, value;
    printf("Number of nodes (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    for (int i = 0; i < n; ++i) {
        printf("Node %d value: ", i + 1);
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
    if (head == NULL) puts("List is empty.");
    else {
        printf("Traversal: ");
        for (Node *p = head; p != NULL; p = p->next) printf("%d -> ", p->value);
        puts("NULL");
    }
    clear(head);
    return 0;
}
