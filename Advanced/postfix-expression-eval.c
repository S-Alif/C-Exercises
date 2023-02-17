#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50

char stack[MAX];
int top = -1;

void push(int n) {
    stack[++top] = n;
}

int pop() {
    return stack[top--];
}

int get_priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

char *infix_to_postfix(char *infix, char *postfix) {
    int i = 0, j = 0;
    char c;
    memset(postfix, 0, sizeof(postfix));

    while ((c = infix[i++]) != '\0') {
        if (isdigit(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop();
        } else {
            while (top >= 0 && get_priority(stack[top]) >= get_priority(c)) {
                postfix[j++] = pop();
            }
            push(c);
        }
    }
    while (top >= 0) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
    return postfix;
}

int evaluate_postfix(char *postfix) {
    int i = 0, a, b;
    char c;
    while ((c = postfix[i++]) != '\0') {
        if (isdigit(c)) {
            push(c - '0');
        } else {
            b = pop();
            a = pop();
            switch (c) {
                case '+':
                    push(a + b);
                    break;
                case '-':
                    push(a - b);
                    break;
                case '*':
                    push(a * b);
                    break;
                case '/':
                    push(a / b);
                    break;
                case '^':
                    push(pow(a, b));
                    break;
                default:
                    break;
            }
        }
    }
    return stack[top];
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter an infix expression: ");
    gets(infix);

    infix_to_postfix(infix, postfix);

    printf("\nPostfix expression : %s", postfix);
    printf("\nResult : %d", evaluate_postfix(postfix));

    return 0;
}