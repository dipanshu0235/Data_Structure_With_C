// Array and linked list search timing
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LIMIT 10000
#define REPETITIONS 500
typedef struct Node {
    int value;
    struct Node *next;
} Node;
static int arraySearch(const int values[], int n, int key) {
    for (int i = 0; i < n; ++i) if (values[i] == key) return i;
    return -1;
}
static int listSearch(const Node *head, int key) {
    int index = 0;
    for (; head != NULL; head = head->next, ++index) if (head->value == key) return index;
    return -1;
}
static void clear(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}
int main(void) {
    static int values[LIMIT];
    Node *head = NULL, **tail = &head;
    int n, key;
    printf("Number of values (1-%d): ", LIMIT);
    if (scanf("%d", &n) != 1 || n < 1 || n > LIMIT) return 1;
    puts("Enter integer values:");
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            clear(head);
            return 1;
        }
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            clear(head);
            puts("Memory allocation failed.");
            return 1;
        }
        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }
    printf("Search key: ");
    if (scanf("%d", &key) != 1) {
        clear(head);
        return 1;
    }
    volatile long long checksum = 0;
    clock_t start = clock();
    for (int i = 0; i < REPETITIONS; ++i) checksum += arraySearch(values, n, key);
    clock_t arrayEnd = clock();
    for (int i = 0; i < REPETITIONS; ++i) checksum += listSearch(head, key);
    clock_t listEnd = clock();
    double arrayTime = (double)(arrayEnd - start) / CLOCKS_PER_SEC / REPETITIONS;
    double listTime = (double)(listEnd - arrayEnd) / CLOCKS_PER_SEC / REPETITIONS;
    printf("Array search result: %d; average time: %.6f seconds\n", arraySearch(values, n, key), arrayTime);
    printf("Linked-list search result: %d; average time: %.6f seconds\n", listSearch(head, key), listTime);
    printf("Checksum: %lld\n", checksum);
    clear(head);
    return 0;
}
