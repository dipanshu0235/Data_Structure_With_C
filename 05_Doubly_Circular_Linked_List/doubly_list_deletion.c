// Doubly Linked List Deletion
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *prev, *next;
} Node;
static int append(Node **head, int value) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) return 0;
    node->value = value;
    node->next = NULL;
    if (*head == NULL) {
        node->prev = NULL;
        *head = node;
        return 1;
    }
    Node *last = *head;
    while (last->next != NULL) last = last->next;
    last->next = node;
    node->prev = last;
    return 1;
}
static int deleteAt(Node **head, int position) {
    if (position < 1) return 0;
    Node *node = *head;
    for (int i = 1; i < position && node != NULL; ++i) node = node->next;
    if (node == NULL) return 0;
    if (node->prev != NULL) node->prev->next = node->next;
    else *head = node->next;
    if (node->next != NULL) node->next->prev = node->prev;
    free(node);
    return 1;
}
static void display(const Node *head) {
    if (head == NULL) {
        puts("List is empty.");
        return;
    }
    printf("List: ");
    while (head != NULL) {
        printf("%d <-> ", head->value);
        head = head->next;
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
    int n, value, choice, position;
    printf("Initial node count (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &value) != 1 || !append(&head, value)) {
            clear(&head);
            puts("Input or allocation error.");
            return 1;
        }
    }
    do {
        puts("\n1. Delete at position  2. Display  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            clear(&head);
            return 1;
        }
        if (choice == 1) {
            printf("Position: ");
            if (scanf("%d", &position) != 1) {
                clear(&head);
                return 1;
            }
            puts(deleteAt(&head, position) ? "Node deleted." : "List is empty or position is invalid.");
        }
        else if (choice == 2) display(head);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    clear(&head);
    return 0;
}
