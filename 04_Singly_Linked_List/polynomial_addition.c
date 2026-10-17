// Add two polynomials
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
static int readPolynomial(Term **poly, const char *name) {
    int n, c, e;
    printf("Number of terms in %s (0-100): ", name);
    if (scanf("%d", &n) != 1 || n < 0 || n > 100) return 0;
    for (int i = 0; i < n; ++i) if (scanf("%d%d", &c, &e) != 2 || e < 0 || !addTerm(poly, c, e)) return 0;
    return 1;
}
static void display(const Term *p) {
    int any = 0;
    for (; p != NULL; p = p->next) if (p->coefficient != 0) {
        if (any) printf(p->coefficient > 0 ? " + " : " - ");
        else if (p->coefficient < 0) putchar('-');
        int c = p->coefficient < 0 ? -p->coefficient : p->coefficient;
        if (p->exponent == 0 || c != 1) printf("%d", c);
        if (p->exponent > 0) {
            putchar('x');
            if (p->exponent > 1) printf("^%d", p->exponent);
        }
        any = 1;
    }
    if (!any) putchar('0');
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
    Term *a = NULL, *b = NULL, *sum = NULL;
    if (!readPolynomial(&a, "first polynomial") || !readPolynomial(&b, "second polynomial")) {
        clear(a);
        clear(b);
        puts("Invalid input or memory allocation failed.");
        return 1;
    }
    for (Term *p = a; p != NULL; p = p->next) if (!addTerm(&sum, p->coefficient, p->exponent)) {
        clear(a);
        clear(b);
        clear(sum);
        puts("Memory allocation failed.");
        return 1;
    }
    for (Term *p = b; p != NULL; p = p->next) if (!addTerm(&sum, p->coefficient, p->exponent)) {
        clear(a);
        clear(b);
        clear(sum);
        puts("Memory allocation failed.");
        return 1;
    }
    printf("First:  ");
    display(a);
    printf("Second: ");
    display(b);
    printf("Sum:    ");
    display(sum);
    clear(a);
    clear(b);
    clear(sum);
    return 0;
}
