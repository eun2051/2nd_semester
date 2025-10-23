#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    lparen, rparen, plus, minus, times,
    divide, mod, eos, operand }precedence;
char expr[MAX_EXPR_SIZE];
int top = -1;
precedence p_stack[MAX_STACK_SIZE];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

void postfix(void) {
    char symbol;
    precedence token;
    int n = 0;
    top = -1;

    push(eos);
    for (token = get_token(&symbol, &n); token != eos;
    token = get_token(&symbol, &n)) {
        if (token == operand)
            print("%c", symbol);
        else if (token == rparen) {
            while (p_stack[top] != lparen)
                print_token(pop());
            pop();
        } else {
            while (isp[p_stack[top]] >= icp[token])
                print_token(pop());
            push(token);
        }
    }
    while ((token = pop()) != eos)
        print_token(token);
    printf("\n");
}
