// Circular linked list insertion
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *next;
} Node;
static int insertAt(Node **head, int value, int position) {
    int length = 0;
    Node *last = *head;
    if (last != NULL) {
        length = 1;
        while (last->next != *head) {
            last = last->next;
            ++length;
        }
    }
    if (position < 1 || position > length + 1) return 0;
    Node *node = malloc(sizeof(*node));
    if (node == NULL) return -1;
    node->value = value;
    if (*head == NULL) {
        node->next = node;
        *head = node;
        return 1;
    }
    if (position == 1) {
        node->next = *head;
        last->next = node;
        *head = node;
        return 1;
    }
    Node *before = *head;
    for (int i = 1; i < position - 1; ++i) before = before->next;
    node->next = before->next;
    before->next = node;
    return 1;
}
static void display(const Node *head) {
    if (head == NULL) {
        puts("Circular list is empty.");
        return;
    }
    const Node *p = head;
    printf("Head -> ");
    do {
        printf("%d -> ", p->value);
        p = p->next;
    } while (p != head);
    puts("Head");
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
            puts(r == 1 ? "Inserted." : r == 0 ? "Invalid position." : "Memory allocation failed.");
        }
        else if (choice == 2) display(head);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    clear(&head);
    return 0;
}
