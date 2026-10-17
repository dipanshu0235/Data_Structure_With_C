// Polynomial Representation
#include <stdio.h>
#include <stdlib.h>
typedef struct Term {
    int coefficient, exponent;
    struct Term *next;
} Term;
static int addTerm(Term **poly, int coefficient, int exponent) {
    if (coefficient == 0) return 1;
    while (*poly != NULL && (*poly)->exponent > exponent) poly = &(*poly)->next;
    if (*poly != NULL && (*poly)->exponent == exponent) {
        (*poly)->coefficient += coefficient;
        return 1;
    }
    Term *term = malloc(sizeof(*term));
    if (term == NULL) return 0;
    term->coefficient = coefficient;
    term->exponent = exponent;
    term->next = *poly;
    *poly = term;
    return 1;
}
static void display(const Term *p) {
    int printed = 0;
    for (; p != NULL; p = p->next) if (p->coefficient != 0) {
        if (printed && p->coefficient > 0) printf(" + ");
        else if (printed) printf(" - ");
        else if (p->coefficient < 0) printf("-");
        int c = p->coefficient < 0 ? -p->coefficient : p->coefficient;
        if (p->exponent == 0 || c != 1) printf("%d", c);
        if (p->exponent > 0) {
            putchar('x');
            if (p->exponent > 1) printf("^%d", p->exponent);
        }
        printed = 1;
    }
    if (!printed) putchar('0');
    putchar('\n');
}
static void clear(Term *p) {
    while (p != NULL) {
        Term *next = p->next;
        free(p);
        p = next;
    }
}
int main(void) {
    Term *poly = NULL;
    int n, coefficient, exponent;
    printf("Number of input terms (0-100): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 1;
    puts("Enter each coefficient and non-negative exponent:");
    for (int i = 0; i < n; ++i) {
        if (scanf("%d%d", &coefficient, &exponent) != 2 || exponent < 0 || !addTerm(&poly, coefficient, exponent)) {
            clear(poly);
            puts("Invalid term or memory allocation failed.");
            return 1;
        }
    }
    printf("Polynomial: ");
    display(poly);
    clear(poly);
    return 0;
}
