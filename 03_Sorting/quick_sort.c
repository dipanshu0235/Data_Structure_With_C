// Quick Sort
#include <stdio.h>
#define CAPACITY 100

static void display(const int a[], int n) {
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    if (n == 0) printf("(empty)");
    putchar('\n');
}
static void quickSortRange(int a[], int low, int high) {
    if (low >= high) return;
    int pivot = a[low + (high - low) / 2], less = low, current = low, greater = high;
    while (current <= greater) {
        if (a[current] < pivot) {
            int t = a[less];
            a[less++] = a[current];
            a[current++] = t;
        }
        else if (a[current] > pivot) {
            int t = a[greater];
            a[greater--] = a[current];
            a[current] = t;
        }
        else ++current;
    }
    quickSortRange(a, low, less - 1);
    quickSortRange(a, greater + 1, high);
}
static void quickSort(int a[], int n) {
    if (n > 1) quickSortRange(a, 0, n - 1);
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
    quickSort(a, n);
    printf("Sorted array:   ");
    display(a, n);
    return 0;
}
