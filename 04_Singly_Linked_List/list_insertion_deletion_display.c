// Linked List Insertion, Deletion and Display
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value;
    struct Node *next;
} Node;

static Node *makeNode(int value) {
    Node *n = malloc(sizeof(*n));
    if (n != NULL) {
        n->value = value;
        n->next = NULL;
    }
    return n;
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
static int insertAt(Node **head, int value, int position) {
    if (position < 1) return 0;
    int length = 0;
    for (Node *p = *head; p != NULL; p = p->next) ++length;
    if (position > length + 1) return 0;
    Node **link = head;
    for (int i = 1; i < position; ++i) link = &(*link)->next;
    Node *n = makeNode(value);
    if (n == NULL) return -1;
    n->next = *link;
    *link = n;
    return 1;
}
static int deleteAt(Node **head, int position) {
    Node **link = head;
    for (int i = 1; i < position && *link != NULL; ++i) link = &(*link)->next;
    if (position < 1 || *link == NULL) return 0;
    Node *removed = *link;
    *link = removed->next;
    free(removed);
    return 1;
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
        puts("\n1. Insert at position  2. Delete at position  3. Display  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            clear(&head);
            return 1;
        }
        if (choice == 1) {
            printf("Value and position (1 inserts at head): ");
            if (scanf("%d%d", &value, &position) != 2) {
                clear(&head);
                return 1;
            }
            int result = insertAt(&head, value, position);
            puts(result == 1 ? "Inserted." : result == 0 ? "Invalid position." : "Memory allocation failed.");
        } else if (choice == 2) {
            printf("Position to delete: ");
            if (scanf("%d", &position) != 1) {
                clear(&head);
                return 1;
            }
            puts(deleteAt(&head, position) ? "Deleted." : "List is empty or position is invalid.");
        } else if (choice == 3) display(head);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    clear(&head);
    return 0;
}
