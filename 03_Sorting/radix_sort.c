// Radix Sort
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 100

static void display(const int a[], int n) {
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    if (n == 0) printf("(empty)");
    putchar('\n');
}
static int radixSort(int a[], int n) {
    uint32_t *values = malloc((size_t)n * sizeof(*values));
    uint32_t *temp = malloc((size_t)n * sizeof(*temp));
    if (n > 0 && (values == NULL || temp == NULL)) {
        free(values);
        free(temp);
        return 0;
    }
    for (int i = 0; i < n; ++i) values[i] = ((uint32_t)(int32_t)a[i]) ^ UINT32_C(0x80000000);
    for (unsigned shift = 0; shift < 32; shift += 8) {
        size_t counts[256] = {0};
        for (int i = 0; i < n; ++i) ++counts[(values[i] >> shift) & UINT32_C(255)];
        size_t total = 0;
        for (int i = 0; i < 256; ++i) {
            size_t count = counts[i];
            counts[i] = total;
            total += count;
        }
        for (int i = 0; i < n; ++i) {
            unsigned digit = (values[i] >> shift) & UINT32_C(255);
            temp[counts[digit]++] = values[i];
        }
        uint32_t *swap = values;
        values = temp;
        temp = swap;
    }
    for (int i = 0; i < n; ++i) a[i] = (int32_t)(values[i] ^ UINT32_C(0x80000000));
    free(values);
    free(temp);
    return 1;
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
    if (!radixSort(a, n)) {
        puts("Memory allocation failed.");
        return 1;
    }
    printf("Sorted array:   ");
    display(a, n);
    return 0;
}
