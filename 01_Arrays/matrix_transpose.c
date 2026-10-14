// Matrix Transpose
#include <stdio.h>
#define LIMIT 10

int main(void) {
    int a[LIMIT][LIMIT], r, c;
    printf("Rows and columns (1-%d): ", LIMIT);
    if (scanf("%d%d", &r, &c) != 2 || r < 1 || r > LIMIT || c < 1 || c > LIMIT) {
        puts("Invalid dimensions.");
        return 1;
    }
    puts("Enter matrix:");
    for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) if (scanf("%d", &a[i][j]) != 1) return 1;
    puts("Transpose:");
    for (int j = 0; j < c; ++j) {
        for (int i = 0; i < r; ++i) printf("%d\t", a[i][j]);
        putchar('\n');
    }
    return 0;
}
