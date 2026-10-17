// Binary Search
#include <stdio.h>
#define CAPACITY 100

int main(void) {
    int a[CAPACITY], n, key, low, high, found = -1;
    puts("Binary search requires the array to be sorted in ascending order.");
    printf("Enter number of elements (1-%d): ", CAPACITY);
    if (scanf("%d", &n) != 1 || n < 1 || n > CAPACITY) {
        puts("Invalid size.");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) return 1;
        if (i > 0 && a[i] < a[i - 1]) {
            puts("Input is not sorted; binary search stopped.");
            return 1;
        }
    }
    printf("Value to search: ");
    if (scanf("%d", &key) != 1) return 1;
    low = 0;
    high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == key) {
            found = mid;
            high = mid - 1;
        }
        else if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    if (found >= 0) printf("%d found at index %d (position %d).\n", key, found, found + 1);
    else puts("Element not found.");
    return 0;
}
