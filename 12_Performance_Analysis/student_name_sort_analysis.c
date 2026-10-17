// Sort student names
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_STUDENTS 200
#define NAME_LENGTH 100
#define ROUNDS 100
static void insertionSort(char names[][NAME_LENGTH], int n) {
    for (int i = 1; i < n; ++i) {
        char name[NAME_LENGTH];
        strcpy(name, names[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(names[j], name) > 0) {
            strcpy(names[j + 1], names[j]);
            --j;
        }
        strcpy(names[j + 1], name);
    }
}
static void merge(char names[][NAME_LENGTH], char temp[][NAME_LENGTH], int left, int middle, int right) {
    int i = left, j = middle + 1, k = left;
    while (i <= middle && j <= right) {
        if (strcmp(names[i], names[j]) <= 0) strcpy(temp[k++], names[i++]);
        else strcpy(temp[k++], names[j++]);
    }
    while (i <= middle) strcpy(temp[k++], names[i++]);
    while (j <= right) strcpy(temp[k++], names[j++]);
    for (i = left; i <= right; ++i) strcpy(names[i], temp[i]);
}
static void mergeSortRange(char names[][NAME_LENGTH], char temp[][NAME_LENGTH], int left, int right) {
    if (left >= right) return;
    int middle = left + (right - left) / 2;
    mergeSortRange(names, temp, left, middle);
    mergeSortRange(names, temp, middle + 1, right);
    merge(names, temp, left, middle, right);
}
static void mergeSort(char names[][NAME_LENGTH], int n) {
    char temp[MAX_STUDENTS][NAME_LENGTH];
    if (n > 1) mergeSortRange(names, temp, 0, n - 1);
}
static void display(char names[][NAME_LENGTH], int n) {
    for (int i = 0; i < n; ++i) printf("%2d. %s\n", i + 1, names[i]);
    if (n == 0) puts("(no names)");
}
int main(void) {
    static char original[MAX_STUDENTS][NAME_LENGTH], insertion[MAX_STUDENTS][NAME_LENGTH], merged[MAX_STUDENTS][NAME_LENGTH];
    int n;
    printf("Number of students (0-%d): ", MAX_STUDENTS);
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX_STUDENTS) return 1;
    puts("Enter one student name per line (up to 99 characters):");
    for (int i = 0; i < n; ++i) if (scanf(" %99[^\n]", original[i]) != 1) return 1;
    printf("Original names:\n");
    display(original, n);
    clock_t insertionStart = clock();
    for (int r = 0; r < ROUNDS; ++r) {
        memcpy(insertion, original, (size_t)n * sizeof(original[0]));
        insertionSort(insertion, n);
    }
    clock_t insertionEnd = clock();
    clock_t mergeStart = clock();
    for (int r = 0; r < ROUNDS; ++r) {
        memcpy(merged, original, (size_t)n * sizeof(original[0]));
        mergeSort(merged, n);
    }
    clock_t mergeEnd = clock();
    printf("\nInsertion sort result:\n");
    display(insertion, n);
    printf("Merge sort result:\n");
    display(merged, n);
    double insertionTime = (double)(insertionEnd - insertionStart) / CLOCKS_PER_SEC / ROUNDS;
    double mergeTime = (double)(mergeEnd - mergeStart) / CLOCKS_PER_SEC / ROUNDS;
    printf("Average insertion-sort time: %.8f seconds\n", insertionTime);
    printf("Average merge-sort time:     %.8f seconds\n", mergeTime);
    if (insertionTime < mergeTime) puts("Insertion sort was faster for this input and run.");
    else if (mergeTime < insertionTime) puts("Merge sort was faster for this input and run.");
    else puts("The measured times tied at the timer's resolution for this input.");
    puts("Times may vary by computer.");
    return 0;
}
