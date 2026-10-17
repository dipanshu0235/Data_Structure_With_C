// Postfix Evaluation
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT 512

static int isOperatorToken(const char *s) {
    return s[0] != '\0' && s[1] == '\0' && strchr("+-*/^", s[0]) != NULL;
}
static double integerPower(double base, double exponent) {
    int e = (int)exponent;
    double result = 1.0;
    unsigned int count = (unsigned int)(e < 0 ? -e : e);
    while (count-- > 0) result *= base;
    return e < 0 ? 1.0 / result : result;
}
static int apply(double *stack, int *top, char op) {
    if (*top < 1) return 0;
    double right = stack[(*top)--], left = stack[(*top)--], result;
    if (op == '+') result = left + right;
    else if (op == '-') result = left - right;
    else if (op == '*') result = left * right;
    else if (op == '/') {
        if (right == 0.0) return 0;
        result = left / right;
    }
    else {
        if ((int)right != right || right < -1000 || right > 1000 || (left == 0.0 && right < 0)) return 0;
        result = integerPower(left, right);
    }
    stack[++(*top)] = result;
    return 1;
}
static int evaluate(char *expression, double *answer) {
    double stack[LIMIT];
    int top = -1, separated = strpbrk(expression, " \t") != NULL;
    if (separated) {
        char *token = strtok(expression, " \t\r\n");
        while (token != NULL) {
            if (isOperatorToken(token)) {
                if (!apply(stack, &top, token[0])) return 0;
            }
            else {
                char *end;
                double value = strtod(token, &end);
                if (*token == '\0' || *end != '\0' || top == LIMIT - 1) return 0;
                stack[++top] = value;
            }
            token = strtok(NULL, " \t\r\n");
        }
    } else {
        for (int i = 0; expression[i] != '\0' && expression[i] != '\n'; ++i) {
            char c = expression[i];
            if (isspace((unsigned char)c)) continue;
            if (c >= '0' && c <= '9') {
                if (top == LIMIT - 1) return 0;
                stack[++top] = c - '0';
            }
            else if (strchr("+-*/^", c) != NULL) {
                if (!apply(stack, &top, c)) return 0;
            }
            else return 0;
        }
    }
    if (top != 0) return 0;
    *answer = stack[0];
    return 1;
}
int main(void) {
    char expression[LIMIT];
    double answer;
    puts("Enter postfix tokens separated by spaces (e.g. 12 3 + 4 *). Without spaces, use single digits (e.g. 23+).");
    if (fgets(expression, sizeof(expression), stdin) == NULL) return 1;
    if (!evaluate(expression, &answer)) {
        puts("Invalid postfix expression (or division by zero). Exponents must be integers.");
        return 1;
    }
    printf("Result: %.10g\n", answer);
    return 0;
}
