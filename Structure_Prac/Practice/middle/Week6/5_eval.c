#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF_SIZ 100
#define MAX_TERMS 10
#define ERROR_KEY -999 /*stack empty error key*/

typedef enum {
    lparen, rparen, plus, minus,
    times, divide, mod, eos,
    operand, err_code /*stack empty error code*/
} precedence;
/* isp와 icp 배열 -- 인덱스는 연산자
    lparen, rparen, plus, minus, times, divide, mod, eos의 우선순위*/
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
precedence* post_stack;
int post_top = -1;
int post_max_size = MAX_TERMS;
int *eval_stack;
int *expr;
int *stack;


//입력 스트링으로부터 토큰을 가져오는 함수
precedence getToken(char *symbol, int *n)
{
    /*다음 토큰을 취함. symbol : 문자 표현
    token : 그것의 열거된 값으로 표현, 함수이름으로 반환됨*/
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return mod;
        case ' ' : return eos;
        default : return operand;
        /*에러 검사는 하지 않고 기본 값은 피연산자*/
    }
}
// 후위 표기식 계산하는 함수
int eval(void) {
    // 전역변수로 되어있는 후위 표기식 expr 연산
    // 함수 getTOken은 토큰의 타입과 문자 심벌 반환
    // stack, top : 전역변수
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0; // 수식 스트링을 위한 카운터
    int top = -1;
    token = getToken(&symbol, &n);
    while (token != eos) {
        if (token == operand)
            push(symbol - '0'); //스택삽입
        else {
            //두 피연산자 삭제하여 연산 수행 후
            //그 결과 스택에 삽입
            op2 = pop(); //스택 삭제
            op1 = pop();
            switch (token) {
                case plus: push(op1 + op2);
                    break;
                case minus: push(op1 - op2);
                    break;
                case times: push(op1 * op2);
                    break;
                case divide: push(op1 / op2);
                    break;
                case mod: push (op1 % op2);
            }
        }
        token = getToken(&symbol, &n);
    }
    return pop(); // 결과 반환
}


void postfix(void) {
    /*수식을 후위표기식으로 출력
    수식 스트링, 스택, top : 전역*/
    char symbol;
    precedence token;
    int n = 0;
    int top = 0; // eos를 스택에 삽입
    stack[0] = eos;
    for (token ==getToken(&symbol, &n); token!=eos;
    token == getToken(&symbol, &n)) {
        if (token == operand)
            printf("%c", symbol);
        else if (token == rparen) {
            /*왼쪽 괄호가 나올 때까지 토큰들을 제거해서 출력시킴*/
            while (stack[top] != lparen)
                printToken(pop());
            pop(); //왼족 괄호를 버린다
        } else {
            /*symbol의 isp가 token의 icp보다 크거나 같으면 
            symbol을 제거하고 출력시킴*/
            while (isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
    }
    while ((token = pop()) != eos)
        printToken(token);
    printf("\n");
}