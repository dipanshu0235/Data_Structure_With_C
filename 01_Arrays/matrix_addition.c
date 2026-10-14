// Matrix addition
#include <stdio.h>
#define LIMIT 10

int main(void) {
    int a[LIMIT][LIMIT], b[LIMIT][LIMIT], r, c;
    printf("Rows and columns (1-%d): ", LIMIT);
    if (scanf("%d%d", &r, &c) != 2 || r < 1 || r > LIMIT || c < 1 || c > LIMIT) {
        puts("Invalid dimensions.");
        return 1;
    }
    puts("Enter first matrix:");
    for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) if (scanf("%d", &a[i][j]) != 1) return 1;
    puts("Enter second matrix:");
    for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) if (scanf("%d", &b[i][j]) != 1) return 1;
    puts("Result:");
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) printf("%d\t", a[i][j] + b[i][j]);
        putchar('\n');
    }
    return 0;
}
