#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    lparen, rparen, plus, minus, times,
    divide, mod, eos, operand }precedence;
char expr[MAX_EXPR_SIZE];
int top = -1;
precedence p_stack[MAX_STACK_SIZE];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

precedence pop()
{
    if (top == -1) {
        precedence error_e = {-1};
        return error_e;
    }
    return p_stack[top--];
}

void push (precedence item) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    p_stack[++top] = item;
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

void print_token(precedence token)
{
    if (token >= lparen && token <= mod) {
        switch (token) {
            case lparen : printf("("); break;
            case rparen : printf(")"); break;
            case plus : printf("+"); break;
            case minus : printf("-"); break;
            case times : printf("*"); break;
            case divide : printf("/"); break;
            case mod : printf("%%"); break;
            case eos : return; 
            default: break; 
        }
    }
}

void postfix(void) {
    char symbol;
    precedence token;
    int n = 0;
    top = -1;

    push(eos);
    for (token = get_token(&symbol, &n); token != eos;
    token = get_token(&symbol, &n)) {
        if (token == operand)
            printf("%c", symbol);
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

int main() {
    // 1. 테스트할 중위 표기식(Infix Expression)을 전역 배열 expr에 복사
    // 예시: A*(B+C)/D  -> 후위식: ABC+*D/
    printf("중위식 입력: A*(B+C)/D\n");
    strcpy(expr, "A*(B+C)/D"); 

    // 2. postfix 함수 호출
    printf("후위식 출력: ");
    postfix(); 

    // 다른 예시
    // strcpy(expr, "A+B*C"); // 후위식: ABC*+
    // printf("후위식 출력: ");
    // postfix(); 
    
    return 0;
}
