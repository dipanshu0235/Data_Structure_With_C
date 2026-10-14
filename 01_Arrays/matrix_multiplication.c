// Matrix multiplication
#include <stdio.h>
#define LIMIT 10

int main(void) {
    int a[LIMIT][LIMIT], b[LIMIT][LIMIT], result[LIMIT][LIMIT] = {
        {
            0
        }
    };
    int r1, c1, r2, c2;
    printf("Rows and columns of first matrix (1-%d): ", LIMIT);
    if (scanf("%d%d", &r1, &c1) != 2 || r1 < 1 || r1 > LIMIT || c1 < 1 || c1 > LIMIT) {
        puts("Invalid dimensions.");
        return 1;
    }
    printf("Rows and columns of second matrix: ");
    if (scanf("%d%d", &r2, &c2) != 2 || r2 < 1 || r2 > LIMIT || c2 < 1 || c2 > LIMIT || c1 != r2) {
        puts("Invalid dimensions: columns of first must equal rows of second.");
        return 1;
    }
    puts("Enter first matrix:");
    for (int i = 0; i < r1; ++i) for (int j = 0; j < c1; ++j) if (scanf("%d", &a[i][j]) != 1) return 1;
    puts("Enter second matrix:");
    for (int i = 0; i < r2; ++i) for (int j = 0; j < c2; ++j) if (scanf("%d", &b[i][j]) != 1) return 1;
    for (int i = 0; i < r1; ++i) for (int j = 0; j < c2; ++j)
    for (int k = 0; k < c1; ++k) result[i][j] += a[i][k] * b[k][j];
    puts("Result:");
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) printf("%d\t", result[i][j]);
        putchar('\n');
    }
    return 0;
}
