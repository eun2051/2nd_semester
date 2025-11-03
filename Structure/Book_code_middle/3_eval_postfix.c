#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    lparen, rparen, plus, minus, times,
    divide, mod, eos, operand }precedence;
int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;
precedence get_token(char *symbol, int *n);

void push (precedence item) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack[++top] = item;
}

precedence pop()
{
    if (top == -1) {
        precedence error_e = {-1};
        return error_e;
    }
    return stack[top--];
}

int eval(void)
{
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    top = -1;
    token = get_token(&symbol, &n);
    while (token != eos) {
        if (token == operand)
            push(symbol - '0');
        else {
            op2 = pop();
            op1 = pop();
            switch(token) {
                case plus : push(op1 + op2); break;
                case minus : push (op1 - op2); break;
                case times : push(op1 * op2); break;
                case divide : push(op1 / op2); break;
                case mod : push(op1 % op2); break;
                default :
                    fprintf(stderr, "잘못된 형식\n");
                    exit(1);
            }
        }
        token = get_token(&symbol, &n);
    }
    return pop();
}

precedence get_token(char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch(*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod;
        case ' ' : return eos;
        default : return operand;
    }
}