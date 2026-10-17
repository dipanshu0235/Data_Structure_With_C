// Balanced Parentheses
#include <stdio.h>
#include <string.h>
#define LIMIT 512

static int matches(char open, char close) {
    return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}');
}
int main(void) {
    char expression[LIMIT], stack[LIMIT];
    int top = -1, valid = 1;
    printf("Enter an expression: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) return 1;
    for (int i = 0; expression[i] != '\0'; ++i) {
        char c = expression[i];
        if (c == '(' || c == '[' || c == '{') stack[++top] = c;
        else if (c == ')' || c == ']' || c == '}') {
            if (top < 0 || !matches(stack[top], c)) {
                valid = 0;
                break;
            }
            --top;
        }
    }
    if (top != -1) valid = 0;
    puts(valid ? "Parentheses are balanced." : "Parentheses are not balanced.");
    return 0;
}
