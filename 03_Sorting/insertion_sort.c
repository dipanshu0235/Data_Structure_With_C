// Insertion Sort
#include <stdio.h>
#define CAPACITY 100

static void display(const int a[], int n) {
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    if (n == 0) printf("(empty)");
    putchar('\n');
}
static void insertionSort(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int value = a[i], j = i - 1;
        while (j >= 0 && a[j] > value) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = value;
    }
}
int main(void) {
    int a[CAPACITY], n;
    printf("Number of elements (0-%d): ", CAPACITY);
    if (scanf("%d", &n) != 1 || n < 0 || n > CAPACITY) {
        puts("Invalid size.");
        return 1;
    }
    for (int i = 0; i < n; ++i) if (scanf("%d", &a[i]) != 1) return 1;
    printf("Original array: ");
    display(a, n);
    insertionSort(a, n);
    printf("Sorted array:   ");
    display(a, n);
    return 0;
}
