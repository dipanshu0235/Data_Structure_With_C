// Doubly Linked List Insertion
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *prev, *next;
} Node;
static int insertAt(Node **head, int value, int position) {
    if (position < 1) return 0;
    int length = 0;
    for (Node *p = *head; p != NULL; p = p->next) ++length;
    if (position > length + 1) return 0;
    Node *after = *head, *before = NULL;
    for (int i = 1; i < position && after != NULL; ++i) {
        before = after;
        after = after->next;
    }
    if (after != NULL) before = after->prev;
    Node *node = malloc(sizeof(*node));
    if (node == NULL) return -1;
    node->value = value;
    node->next = after;
    node->prev = before;
    if (after != NULL) after->prev = node;
    if (before != NULL) before->next = node;
    else *head = node;
    return 1;
}
static void display(const Node *head) {
    if (head == NULL) {
        puts("List is empty.");
        return;
    }
    const Node *last = head;
    printf("Forward: ");
    while (last != NULL) {
        printf("%d <-> ", last->value);
        if (last->next == NULL) break;
        last = last->next;
    }
    puts("NULL");
    printf("Reverse: ");
    while (last != NULL) {
        printf("%d <-> ", last->value);
        last = last->prev;
    }
    puts("NULL");
}
static void clear(Node **head) {
    while (*head != NULL) {
        Node *next = (*head)->next;
        free(*head);
        *head = next;
    }
}
int main(void) {
    Node *head = NULL;
    int choice, value, position;
    do {
        puts("\n1. Insert  2. Display  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            clear(&head);
            return 1;
        }
        if (choice == 1) {
            printf("Value and position: ");
            if (scanf("%d%d", &value, &position) != 2) {
                clear(&head);
                return 1;
            }
            int r = insertAt(&head, value, position);
            puts(r == 1 ? "Node inserted." : r == 0 ? "Invalid position." : "Memory allocation failed.");
        }
        else if (choice == 2) display(head);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    clear(&head);
    return 0;
}
