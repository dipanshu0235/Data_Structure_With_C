// Circular linked list deletion
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *next;
} Node;
static int append(Node **head, int value) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) return 0;
    node->value = value;
    if (*head == NULL) {
        node->next = node;
        *head = node;
        return 1;
    }
    Node *last = *head;
    while (last->next != *head) last = last->next;
    node->next = *head;
    last->next = node;
    return 1;
}
static int deleteAt(Node **head, int position) {
    if (*head == NULL || position < 1) return 0;
    if (position == 1) {
        Node *removed = *head;
        if (removed->next == removed) *head = NULL;
        else {
            Node *last = removed;
            while (last->next != removed) last = last->next;
            *head = removed->next;
            last->next = *head;
        }
        free(removed);
        return 1;
    }
    Node *before = *head;
    for (int i = 1; i < position - 1 && before->next != *head; ++i) before = before->next;
    if (before->next == *head) return 0;
    Node *removed = before->next;
    before->next = removed->next;
    free(removed);
    return 1;
}
static void display(const Node *head) {
    if (head == NULL) {
        puts("Circular list is empty.");
        return;
    }
    const Node *p = head;
    do {
        printf("%d -> ", p->value);
        p = p->next;
    } while (p != head);
    puts("(back to head)");
}
static void clear(Node **head) {
    if (*head == NULL) return;
    Node *p = (*head)->next;
    while (p != *head) {
        Node *next = p->next;
        free(p);
        p = next;
    }
    free(*head);
    *head = NULL;
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
