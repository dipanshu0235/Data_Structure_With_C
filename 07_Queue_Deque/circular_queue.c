// Circular Queue
#include <stdio.h>
#define CAPACITY 8
int main(void) {
    int values[CAPACITY], front = 0, size = 0, choice, value;
    do {
        printf("\n1.Enqueue  2.Dequeue  3.Display  0.Exit (capacity %d)\nChoice: ", CAPACITY);
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1) {
            if (size == CAPACITY) puts("Circular Queue Overflow.");
            else {
                printf("Value: ");
                if (scanf("%d", &value) != 1) return 1;
                values[(front + size) % CAPACITY] = value;
                ++size;
                puts("Enqueued.");
            }
        }
        else if (choice == 2) {
            if (size == 0) puts("Circular Queue Underflow.");
            else {
                printf("Dequeued %d.\n", values[front]);
                front = (front + 1) % CAPACITY;
                --size;
            }
        }
        else if (choice == 3) {
            if (size == 0) puts("Queue is empty.");
            else {
                printf("Front -> ");
                for (int i = 0; i < size; ++i) printf("%d ", values[(front + i) % CAPACITY]);
                puts("<- Rear");
            }
        }
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    return 0;
}
