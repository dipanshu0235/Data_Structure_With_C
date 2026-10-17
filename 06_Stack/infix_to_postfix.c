// Infix to postfix
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define LIMIT 512

static int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
static int rightAssociative(char op) {
    return op == '^';
}
static int convert(const char *input, char output[], size_t outputCapacity) {
    char stack[LIMIT];
    int top = -1, expectingOperand = 1;
    size_t out = 0;
    for (int i = 0; input[i] != '\0' && input[i] != '\n'; ++i) {
        char c = input[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            if (!expectingOperand || out + 2 >= outputCapacity) return 0;
            output[out++] = c;
            output[out++] = ' ';
            expectingOperand = 0;
        } else if (c == '(') {
            if (!expectingOperand || top >= LIMIT - 1) return 0;
            stack[++top] = c;
            expectingOperand = 1;
        } else if (c == ')') {
            if (expectingOperand) return 0;
            while (top >= 0 && stack[top] != '(') {
                if (out + 2 >= outputCapacity) return 0;
                output[out++] = stack[top--];
                output[out++] = ' ';
            }
            if (top < 0) return 0;
            --top;
        } else if (precedence(c) != 0) {
            if (expectingOperand || top >= LIMIT - 1) return 0;
            while (top >= 0 && stack[top] != '(' &&
            (precedence(stack[top]) > precedence(c) ||
            (precedence(stack[top]) == precedence(c) && !rightAssociative(c)))) {
                if (out + 2 >= outputCapacity) return 0;
                output[out++] = stack[top--];
                output[out++] = ' ';
            }
            stack[++top] = c;
            expectingOperand = 1;
        } else return 0;
    }
    if (expectingOperand) return 0;
    while (top >= 0) {
        if (stack[top] == '(' || out + 2 >= outputCapacity) return 0;
        output[out++] = stack[top--];
        output[out++] = ' ';
    }
    if (out > 0) --out;
    output[out] = '\0';
    return 1;
}
int main(void) {
    char input[LIMIT], output[LIMIT * 2];
    puts("Enter an infix expression (single-letter or single-digit operands; + - * / ^ and parentheses):");
    if (fgets(input, sizeof(input), stdin) == NULL) return 1;
    if (!convert(input, output, sizeof(output))) {
        puts("Invalid expression or unmatched parentheses.");
        return 1;
    }
    printf("Postfix: %s\n", output);
    return 0;
}
