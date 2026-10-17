// Bubble Sort
#include <stdio.h>
#define CAPACITY 100

static void display(const int a[], int n) {
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    if (n == 0) printf("(empty)");
    putchar('\n');
}
static void bubbleSort(int a[], int n) {
    for (int end = n - 1; end > 0; --end) {
        int swapped = 0;
        for (int i = 0; i < end; ++i) if (a[i] > a[i + 1]) {
            int t = a[i];
            a[i] = a[i + 1];
            a[i + 1] = t;
            swapped = 1;
        }
        if (!swapped) break;
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
    bubbleSort(a, n);
    printf("Sorted array:   ");
    display(a, n);
    return 0;
}
