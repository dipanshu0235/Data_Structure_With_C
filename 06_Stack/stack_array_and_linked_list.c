// Stack using array and linked list
#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 50
typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void arrayStack(void) {
    int values[CAPACITY], top = -1, choice, value;
    do {
        puts("\nArray stack: 1.Push  2.Pop  3.Peek  4.Display  0.Back");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return;
        if (choice == 1) {
            if (top == CAPACITY - 1) puts("Stack Overflow.");
            else {
                printf("Value: ");
                if (scanf("%d", &value) != 1) return;
                values[++top] = value;
                puts("Pushed.");
            }
        }
        else if (choice == 2) {
            if (top < 0) puts("Stack Underflow.");
            else printf("Popped %d.\n", values[top--]);
        }
        else if (choice == 3) {
            if (top < 0) puts("Stack is empty.");
            else printf("Top: %d\n", values[top]);
        }
        else if (choice == 4) {
            if (top < 0) puts("Stack is empty.");
            else {
                printf("Top -> ");
                for (int i = top; i >= 0; --i) printf("%d ", values[i]);
                putchar('\n');
            }
        }
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
}
static void linkedStack(void) {
    Node *top = NULL;
    int choice, value;
    do {
        puts("\nLinked stack: 1.Push  2.Pop  3.Peek  4.Display  0.Back");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) {
            printf("Value: ");
            if (scanf("%d", &value) != 1) break;
            Node *node = malloc(sizeof(*node));
            if (node == NULL) puts("Memory allocation failed.");
            else {
                node->value = value;
                node->next = top;
                top = node;
                puts("Pushed.");
            }
        }
        else if (choice == 2) {
            if (top == NULL) puts("Stack Underflow.");
            else {
                Node *old = top;
                printf("Popped %d.\n", old->value);
                top = old->next;
                free(old);
            }
        }
        else if (choice == 3) {
            if (top == NULL) puts("Stack is empty.");
            else printf("Top: %d\n", top->value);
        }
        else if (choice == 4) {
            if (top == NULL) puts("Stack is empty.");
            else {
                printf("Top -> ");
                for (Node *p = top; p != NULL; p = p->next) printf("%d ", p->value);
                putchar('\n');
            }
        }
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    while (top != NULL) {
        Node *next = top->next;
        free(top);
        top = next;
    }
}
int main(void) {
    int choice;
    do {
        puts("\nChoose implementation: 1. Array  2. Linked list  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1) arrayStack();
        else if (choice == 2) linkedStack();
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    return 0;
}
