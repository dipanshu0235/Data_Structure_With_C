// Priority queue
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int value, priority;
    struct Node *next;
} Node;
static int enqueue(Node **front, int value, int priority) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) return 0;
    node->value = value;
    node->priority = priority;
    while (*front != NULL && (*front)->priority <= priority) front = &(*front)->next;
    node->next = *front;
    *front = node;
    return 1;
}
static void display(const Node *front) {
    if (front == NULL) {
        puts("Priority queue is empty.");
        return;
    }
    puts("Value (priority):");
    while (front != NULL) {
        printf("%d (%d)\n", front->value, front->priority);
        front = front->next;
    }
}
int main(void) {
    Node *front = NULL;
    int choice, value, priority;
    do {
        puts("\n1. Insert  2. Remove highest priority  3. Display  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) {
            printf("Value and priority (smaller number = higher priority): ");
            if (scanf("%d%d", &value, &priority) != 2) break;
            puts(enqueue(&front, value, priority) ? "Inserted." : "Memory allocation failed.");
        }
        else if (choice == 2) {
            if (front == NULL) puts("Priority Queue Underflow.");
            else {
                Node *old = front;
                printf("Removed %d (priority %d).\n", old->value, old->priority);
                front = old->next;
                free(old);
            }
        }
        else if (choice == 3) display(front);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    while (front != NULL) {
        Node *next = front->next;
        free(front);
        front = next;
    }
    return 0;
}
