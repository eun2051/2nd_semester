#include <iostream>
#define MAX_BUF_SIZ 100
#define MAX_TERMS 10
#define ERROR_KEY -999 
using namespace std;

typedef enum {
    lparen, rparen, plus, minus,
    times, divide, mod, eos,
    operand, err_code /*stack empty error code*/
} precedence;

precedence* post_stack;
int post_max_size = MAX_TERMS;
int max_stack_size = MAX_BUF_SIZ;
char expr[] = {};
int top = -1;

bool Stack_isFull() {
        return top == max_stack_size - 1;
}

bool Stack_isEmpty() {
    return top == -1;
}

void push(int item) {
        if (Stack_isFull()) {
            cout << "스택이 가득 찼습니다." << endl;
            int new_size = max_stack_size * 2;
            int *new_expr = new int[new_size];
            copy(expr, expr + max_stack_size, new_expr);
            delete[] expr;
            expr = new_expr;
            max_stack_size = new_size;
        }
        expr[++top] = item;
    }

int pop() {
    if (Stack_isEmpty()) {
        throw out_of_range("스택이 비었습니다");
    }
    return stack[top--];
}
precedence getToken(char *expr, char *symbol, int *n)
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

int eval(char *expr) {
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

int main()
{   
    cout << "Infix : "
    eval(expr);
    cout << "Infix to Postfix : "
    cout << "\tToken | Stack \t\t" << "|  Top | Output" << endl;

    //infix 표현 수식
    // => stack 사용 -> postfix()
    //postfix 표현 수식
    // => stack 사용 -> eval()
    //계산 결과값
}