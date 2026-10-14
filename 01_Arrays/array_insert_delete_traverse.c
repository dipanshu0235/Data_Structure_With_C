// Array insertion, deletion and traversal
#include <stdio.h>

#define CAPACITY 100

static void display(const int a[], int n) {
    if (n == 0) {
        puts("Array is empty.");
        return;
    }
    printf("Array: ");
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    putchar('\n');
}

int main(void) {
    int a[CAPACITY], n, choice, value, position;
    printf("Enter number of elements (0-%d): ", CAPACITY);
    if (scanf("%d", &n) != 1 || n < 0 || n > CAPACITY) {
        puts("Invalid size.");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        printf("Element %d: ", i + 1);
        if (scanf("%d", &a[i]) != 1) {
            puts("Invalid element.");
            return 1;
        }
    }
    do {
        puts("\n1. Insert  2. Delete  3. Traverse  0. Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1) {
            if (n == CAPACITY) {
                puts("Array Overflow.");
                continue;
            }
            printf("Value and position (1-%d): ", n + 1);
            if (scanf("%d%d", &value, &position) != 2) return 1;
            if (position < 1 || position > n + 1) {
                puts("Invalid position.");
                continue;
            }
            for (int i = n; i >= position; --i) a[i] = a[i - 1];
            a[position - 1] = value;
            ++n;
            puts("Inserted.");
        } else if (choice == 2) {
            if (n == 0) {
                puts("Array is empty.");
                continue;
            }
            printf("Position to delete (1-%d): ", n);
            if (scanf("%d", &position) != 1) return 1;
            if (position < 1 || position > n) {
                puts("Invalid position.");
                continue;
            }
            for (int i = position - 1; i < n - 1; ++i) a[i] = a[i + 1];
            --n;
            puts("Deleted.");
        } else if (choice == 3) display(a, n);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    return 0;
}
