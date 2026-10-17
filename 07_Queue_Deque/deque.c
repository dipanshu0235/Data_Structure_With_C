// Deque
#include <stdio.h>
#define CAPACITY 10
int main(void) {
    int values[CAPACITY], front = 0, size = 0, choice, value;
    do {
        puts("\n1.Insert front  2.Insert rear  3.Delete front  4.Delete rear  5.Display  0.Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1 || choice == 2) {
            if (size == CAPACITY) {
                puts("Deque Overflow.");
                continue;
            }
            printf("Value: ");
            if (scanf("%d", &value) != 1) return 1;
            if (choice == 1) {
                front = (front - 1 + CAPACITY) % CAPACITY;
                values[front] = value;
            }
            else values[(front + size) % CAPACITY] = value;
            ++size;
            puts("Inserted.");
        } else if (choice == 3 || choice == 4) {
            if (size == 0) puts("Deque Underflow.");
            else if (choice == 3) {
                printf("Deleted %d.\n", values[front]);
                front = (front + 1) % CAPACITY;
                --size;
            }
            else {
                printf("Deleted %d.\n", values[(front + size - 1) % CAPACITY]);
                --size;
            }
        } else if (choice == 5) {
            if (size == 0) puts("Deque is empty.");
            else {
                printf("Front -> ");
                for (int i = 0; i < size; ++i) printf("%d ", values[(front + i) % CAPACITY]);
                puts("<- Rear");
            }
        } else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    return 0;
}
