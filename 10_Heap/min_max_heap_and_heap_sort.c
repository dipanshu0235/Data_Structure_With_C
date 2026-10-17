// Min and Max Heap, Heap Sort
#include <stdio.h>
#define CAPACITY 100

static int higher(int a, int b, int isMin) {
    return isMin ? a < b : a > b;
}
static void siftDown(int a[], int n, int i, int isMin) {
    for (;;) {
        int best = i, left = 2 * i + 1, right = left + 1;
        if (left < n && higher(a[left], a[best], isMin)) best = left;
        if (right < n && higher(a[right], a[best], isMin)) best = right;
        if (best == i) return;
        int t = a[i];
        a[i] = a[best];
        a[best] = t;
        i = best;
    }
}
static void heapify(int a[], int n, int isMin) {
    for (int i = n / 2 - 1; i >= 0; --i) siftDown(a, n, i, isMin);
}
static void insert(int a[], int *n, int value, int isMin) {
    int i = (*n)++;
    a[i] = value;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!higher(a[i], a[parent], isMin)) break;
        int t = a[i];
        a[i] = a[parent];
        a[parent] = t;
        i = parent;
    }
}
static int extract(int a[], int *n, int isMin, int *value) {
    if (*n == 0) return 0;
    *value = a[0];
    a[0] = a[--(*n)];
    if (*n > 0) siftDown(a, *n, 0, isMin);
    return 1;
}
static void display(const int a[], int n) {
    if (n == 0) {
        puts("Heap is empty.");
        return;
    }
    printf("Heap array: ");
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    putchar('\n');
}
static void displaySorted(const int a[], int n) {
    printf("Sorted array: ");
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    if (n == 0) printf("(empty)");
    putchar('\n');
}
static void heapMenu(int isMin) {
    int a[CAPACITY], n = 0, choice, value;
    do {
        printf("\n%s heap: 1.Build/heapify  2.Insert  3.Extract root  4.Display  0.Back\nChoice: ", isMin ? "Min" : "Max");
        if (scanf("%d", &choice) != 1) return;
        if (choice == 1) {
            printf("Number of values (0-%d): ", CAPACITY);
            if (scanf("%d", &n) != 1 || n < 0 || n > CAPACITY) {
                n = 0;
                puts("Invalid size.");
                continue;
            }
            for (int i = 0; i < n; ++i) if (scanf("%d", &a[i]) != 1) {
                n = 0;
                return;
            }
            heapify(a, n, isMin);
            puts("Heap built.");
        }
        else if (choice == 2) {
            if (n == CAPACITY) puts("Heap Overflow.");
            else {
                printf("Value: ");
                if (scanf("%d", &value) != 1) return;
                insert(a, &n, value, isMin);
                puts("Inserted.");
            }
        }
        else if (choice == 3) {
            if (extract(a, &n, isMin, &value)) printf("Extracted root: %d\n", value);
            else puts("Heap Underflow.");
        }
        else if (choice == 4) display(a, n);
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
}
static void heapSort(int a[], int n) {
    heapify(a, n, 0);
    for (int end = n - 1; end > 0; --end) {
        int t = a[0];
        a[0] = a[end];
        a[end] = t;
        siftDown(a, end, 0, 0);
    }
}
int main(void) {
    int choice;
    do {
        puts("\n1.Min heap  2.Max heap  3.Heap sort  0.Exit");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 1;
        if (choice == 1) heapMenu(1);
        else if (choice == 2) heapMenu(0);
        else if (choice == 3) {
            int a[CAPACITY], n;
            printf("Number of values (0-%d): ", CAPACITY);
            if (scanf("%d", &n) != 1 || n < 0 || n > CAPACITY) return 1;
            for (int i = 0; i < n; ++i) if (scanf("%d", &a[i]) != 1) return 1;
            printf("Original array: ");
            for (int i = 0; i < n; ++i) printf("%d ", a[i]);
            if (n == 0) printf("(empty)");
            putchar('\n');
            heapSort(a, n);
            displaySorted(a, n);
        }
        else if (choice != 0) puts("Invalid choice.");
    } while (choice != 0);
    return 0;
}
