// Merge Sort
#include <stdio.h>
#define CAPACITY 100

static void display(const int a[], int n) {
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    if (n == 0) printf("(empty)");
    putchar('\n');
}
static void merge(int a[], int temp[], int left, int middle, int right) {
    int i = left, j = middle + 1, k = left;
    while (i <= middle && j <= right) temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= middle) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (i = left; i <= right; ++i) a[i] = temp[i];
}
static void mergeSortRange(int a[], int temp[], int left, int right) {
    if (left >= right) return;
    int middle = left + (right - left) / 2;
    mergeSortRange(a, temp, left, middle);
    mergeSortRange(a, temp, middle + 1, right);
    merge(a, temp, left, middle, right);
}
static void mergeSort(int a[], int n) {
    int temp[CAPACITY];
    if (n > 1) mergeSortRange(a, temp, 0, n - 1);
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
    mergeSort(a, n);
    printf("Sorted array:   ");
    display(a, n);
    return 0;
}
