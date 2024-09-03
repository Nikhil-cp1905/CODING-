#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} Stack;

void push(Stack *s, char c) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = c;
    } else {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
}

char pop(Stack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } else {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
}

char peek(Stack *s) {
    if (s->top >= 0) {
        return s->items[s->top];
    } else {
        return '\0'; 
    }
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int precedence(char op) {
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

void infixToPostfix(const char *infix, char *postfix) {
    Stack s;
    s.top = -1;
    int j = 0;

    for (int i = 0; infix[i]; i++) {
        char c = infix[i];

        if (isspace(c)) {
            continue; 
        }

        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(&s, c);
        } else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s); 
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s); 
            }
        } else { 
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c)) {
                postfix[j++] = pop(&s); 
            }
            push(&s, c);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0'; 
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0; 
    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
