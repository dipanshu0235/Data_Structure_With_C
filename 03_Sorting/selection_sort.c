// Selection Sort
#include <stdio.h>
#define CAPACITY 100

static void display(const int a[], int n) {
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    if (n == 0) printf("(empty)");
    putchar('\n');
}
static void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) if (a[j] < a[min]) min = j;
        if (min != i) {
            int t = a[i];
            a[i] = a[min];
            a[min] = t;
        }
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
    selectionSort(a, n);
    printf("Sorted array:   ");
    display(a, n);
    return 0;
}
