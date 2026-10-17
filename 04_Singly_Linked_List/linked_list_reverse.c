// Reverse Linked List
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
static Node *reverse(Node *head) {
    Node *previous = NULL;
    while (head != NULL) {
        Node *next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    return previous;
}
static void display(const Node *head) {
    if (head == NULL) {
        puts("(empty)");
        return;
    } while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    puts("NULL");
}
int main(void) {
    Node *head = NULL, **tail = &head;
    int n, value;
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
            return 1;
        }
        node->value = value;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }
    printf("Original list: ");
    display(head);
    head = reverse(head);
    printf("Reversed list: ");
    display(head);
    clear(head);
    return 0;
}
