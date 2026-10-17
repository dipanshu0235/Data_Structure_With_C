// Queue using array and linked list
#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 50
typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void arrayQueue(void) {
    int values[CAPACITY], front = 0, size = 0, choice, value;
    do {
        puts("\nArray queue: 1.Enqueue  2.Dequeue  3.Display  0.Back");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return;
        if (choice == 1) {
            if (size == CAPACITY) puts("Queue Overflow.");
            else {
                printf("Value: ");
                if (scanf("%d", &value) != 1) return;
                values[(front + size) % CAPACITY] = value;
                ++size;
                puts("Enqueued.");
            }
        }
        else if (choice == 2) {
            if (size == 0) puts("Queue Underflow.");
            else {
                printf("Dequeued %d.\n", values[front]);
                front = (front + 1) % CAPACITY;
                --size;
            }
        }
        else if (choice == 3) {
            if (size == 0) puts("Queue is empty.");
            else {
                for (int i = 0; i < size; ++i) printf("%d ", values[(front + i) % CAPACITY]);
                putchar('\n');
            }
        }
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
}
static void linkedQueue(void) {
    Node *front = NULL, *rear = NULL;
    int choice, value;
    do {
        puts("\nLinked queue: 1.Enqueue  2.Dequeue  3.Display  0.Back");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) {
            printf("Value: ");
            if (scanf("%d", &value) != 1) break;
            Node *node = malloc(sizeof(*node));
            if (node == NULL) puts("Memory allocation failed.");
            else {
                node->value = value;
                node->next = NULL;
                if (rear == NULL) front = node;
                else rear->next = node;
                rear = node;
                puts("Enqueued.");
            }
        }
        else if (choice == 2) {
            if (front == NULL) puts("Queue Underflow.");
            else {
                Node *old = front;
                printf("Dequeued %d.\n", old->value);
                front = old->next;
                if (front == NULL) rear = NULL;
                free(old);
            }
        }
        else if (choice == 3) {
            if (front == NULL) puts("Queue is empty.");
            else {
                for (Node *p = front; p != NULL; p = p->next) printf("%d ", p->value);
                putchar('\n');
            }
        }
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    while (front != NULL) {
        Node *next = front->next;
        free(front);
        front = next;
    }
}
int main(void) {
    int choice;
    do {
        puts("\nChoose implementation: 1. Array  2. Linked list  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1) arrayQueue();
        else if (choice == 2) linkedQueue();
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    return 0;
}
