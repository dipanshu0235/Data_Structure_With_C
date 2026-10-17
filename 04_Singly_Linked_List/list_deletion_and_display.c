// Linked List Deletion and Display
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *next;
} Node;

static int append(Node **head, int value) {
    Node *n = malloc(sizeof(*n));
    if (n == NULL) return 0;
    n->value = value;
    n->next = NULL;
    while (*head != NULL) head = &(*head)->next;
    *head = n;
    return 1;
}
static int deleteValue(Node **head, int value) {
    while (*head != NULL && (*head)->value != value) head = &(*head)->next;
    if (*head == NULL) return 0;
    Node *removed = *head;
    *head = removed->next;
    free(removed);
    return 1;
}
static void display(const Node *head) {
    if (head == NULL) {
        puts("List is empty.");
        return;
    }
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->value);
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
    int n, value, choice;
    printf("Initial node count (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    for (int i = 0; i < n; ++i) {
        printf("Value %d: ", i + 1);
        if (scanf("%d", &value) != 1 || !append(&head, value)) {
            clear(&head);
            puts("Input or allocation error.");
            return 1;
        }
    }
    do {
        puts("\n1. Delete first matching value  2. Display  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            clear(&head);
            return 1;
        }
        if (choice == 1) {
            printf("Value to delete: ");
            if (scanf("%d", &value) != 1) {
                clear(&head);
                return 1;
            }
            puts(deleteValue(&head, value) ? "Deleted." : "Element not found.");
        }
        else if (choice == 2) display(head);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    clear(&head);
    return 0;
}
