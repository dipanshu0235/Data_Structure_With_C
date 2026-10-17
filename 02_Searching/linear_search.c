// Linear search
#include <stdio.h>
#define CAPACITY 100

int main(void) {
    int a[CAPACITY], n, key, found = 0;
    printf("Enter number of elements (1-%d): ", CAPACITY);
    if (scanf("%d", &n) != 1 || n < 1 || n > CAPACITY) {
        puts("Invalid size.");
        return 1;
    }
    for (int i = 0; i < n; ++i) if (scanf("%d", &a[i]) != 1) {
        puts("Invalid element.");
        return 1;
    }
    printf("Value to search: ");
    if (scanf("%d", &key) != 1) return 1;
    for (int i = 0; i < n; ++i) if (a[i] == key) {
        printf("Found at index %d (position %d).\n", i, i + 1);
        found = 1;
    }
    if (!found) puts("Element not found.");
    return 0;
}
