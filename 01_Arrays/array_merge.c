// Array merge
#include <stdio.h>
#define CAPACITY 200

int main(void) {
    int a[CAPACITY], n, m;
    printf("Number of elements in first array (0-%d): ", CAPACITY);
    if (scanf("%d", &n) != 1 || n < 0 || n > CAPACITY) {
        puts("Invalid size.");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        printf("First[%d]: ", i);
        if (scanf("%d", &a[i]) != 1) return 1;
    }
    printf("Number of elements in second array (0-%d): ", CAPACITY - n);
    if (scanf("%d", &m) != 1 || m < 0 || n + m > CAPACITY) {
        puts("Invalid size.");
        return 1;
    }
    for (int i = 0; i < m; ++i) {
        printf("Second[%d]: ", i);
        if (scanf("%d", &a[n + i]) != 1) return 1;
    }
    printf("Merged array: ");
    for (int i = 0; i < n + m; ++i) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
