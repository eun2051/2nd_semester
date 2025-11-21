#include <iostream>
#include <cstdlib>
#include <cstring>
#define MAX_STACK_SIZE 999
#define MAX_EXPR_SIZE 999
using namespace std;

enum precedence{ lparen, rparen, p_plus, p_minus, times,
    divide, mod, power, p_not, eos, operand };
precedence p_stack[MAX_STACK_SIZE];
int e_stack[MAX_STACK_SIZE];
char new_expr[MAX_EXPR_SIZE];
char expr[MAX_EXPR_SIZE];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 20, 1, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 20, 1, 0};
int e_top = -1;
int p_top = -1;
int idx = 0;

void e_push(int item);
int e_pop();
void p_push(precedence item);
precedence p_pop();
precedence getToken(char *expr, char *symbol, int *n);
int eval(char *expr);
char printToken(precedence token);
void postfix(char *expr, char *new_expr);
void print_estep(char symbol);
void print_pstep(char symbol, const char *str);

precedence getToken(char *expr, char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return p_plus;
        case '-' : return p_minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod;
        case '^' : return power;
        case '!' : return p_not;
        case '\0' : return eos;
        default : return operand;
    }
}

int eval(char *expr)
{
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    e_top = -1;

    token = getToken(expr,&symbol, &n);
    while (token != eos) {
        if (token == operand)
            e_push(symbol - '0');
        else {
            op2 = e_pop();
            op1 = e_pop();
            switch (token) {
                case p_plus : e_push(op1 + op2); break;
                case p_minus : e_push(op1 - op2); break;
                case times : e_push(op1 * op2); break;
                case divide : e_push(op1 / op2); break;
                case mod : e_push(op1 % op2); break;
                case power : e_push((op1 || op2)? 0 : 1); break;
                case p_not : e_push((!op1)? op2 : op1); break;
                default :
                    cout << "잘못된 토큰 : " << printToken(token) << endl;
                    exit(1);
            }
        }
        print_estep(symbol);
        token = getToken(expr,&symbol, &n);
    }
    return e_pop();
}

void print_pstep(char symbol, const char *str) {
    if (symbol == ')') {
        return ;
    }

    cout << "      " << symbol;
    for(int i = 0; i < 6 - 1; ++i) cout << " "; 
    cout << "| ";

    string stack_content = "";
    for (int i = 0; i <= p_top; ++i) {
        stack_content += printToken(p_stack[i]);
        stack_content += " ";
    }
    cout << stack_content;
    for(size_t i = 0; i < 20 - stack_content.length(); ++i) cout << " ";
    cout << "| ";

    int print_ptop = p_top;
    if (p_top >= 0) {
        print_ptop = p_top - 1;
    }

    if (symbol == ' ' && p_top == -1) {
        print_ptop = -2;
    }

    string top_str = to_string(print_ptop);
    for(size_t i = 0; i < 4 - top_str.length(); ++i) cout << " ";
    cout << print_ptop << " | ";


    for(int i = 0; str[i] != '\0'; ++i) {
        cout << str[i] << " ";
    }
    
    cout << endl;
}

void print_estep(char symbol) {
    cout << "      " << symbol;
    for(int i = 0; i < 6 - 1; ++i) cout << " ";
    cout << "| ";

    string stack_content = "";
    for (int i = 0; i <= e_top; ++i) {
        stack_content += to_string(e_stack[i]);
        stack_content += " ";
    }
    cout << stack_content;
    for(size_t i = 0; i < 30 - stack_content.length(); ++i) cout << " ";
    cout << "| ";

    int print_top = e_top;
    if (e_top == 0) {
        print_top = -1;
    } else if (e_top > 0) {
        print_top = e_top - 1;
    }

    string top_str = to_string(print_top);
    for(size_t i = 0; i < 4 - top_str.length(); ++i) cout << " ";
    cout << print_top << endl;
}

void e_push(int item) {
    if (e_top == MAX_STACK_SIZE - 1) {
        cout << "스택이 가득 찼습니다." << endl;
        return ;
    }
    e_stack[++e_top] = item;
}

int e_pop()
{
    if (e_top == -1) {
        cout << "스택이 비었습니다." << endl;
        exit(1);
    }
    return e_stack[e_top--];
}


void p_push(precedence item) {
    if (p_top == MAX_STACK_SIZE - 1) {
        cout << "스택이 가득 찼습니다." << endl;
        return ;
    }
    p_stack[++p_top] = item;
}

precedence p_pop()
{
    if (p_top == -1) {
        cout << "스택이 비었습니다." << endl;
        exit(1);
    }
    return p_stack[p_top--];
}

char printToken(precedence token)
{
    switch (token) {
        case lparen : return '(';
        case rparen : return ')';
        case p_plus : return '+';
        case p_minus : return '-';
        case divide : return '/';
        case times : return '*';
        case mod : return '%';
        case eos : return 'e';
        default : return token + '0';
    }
}

void postfix(char *expr, char *new_expr) 
{
    char symbol;
    precedence token;
    int n = 0;
    p_top = -1;
    idx = 0;

    p_push(eos);
    for(token = getToken(expr,&symbol, &n); token != eos; token = getToken(expr, &symbol, &n)) {
        if (token == operand)
            new_expr[idx++] = symbol;
        else if (token == rparen) {
            while (p_stack[p_top]!= lparen)
                new_expr[idx++] = printToken(p_pop());
            p_pop();
        } else {
            while (isp[p_stack[p_top]] >= icp[token]) {
                new_expr[idx++] = printToken(p_pop());
            }
            p_push(token);
        }
        new_expr[idx] = '\0';
        print_pstep(symbol, new_expr);
    }
    while ((token = p_pop()) != eos) {
        new_expr[idx++] = printToken(token);
    }
    new_expr[idx] = '\0';
    print_pstep(' ', new_expr);
    cout << "\n" << endl;
}

int main()
{
    char infix_expr[MAX_EXPR_SIZE];

    cout << "Infix : ";
    cin >> infix_expr;
    strcpy(expr, infix_expr);
    cout << "Infix to Postfix :" << endl;
    cout << "      Token | Stack\t\t  |  Top | Output" << endl;
    
    postfix(expr, new_expr);
    cout << "Postfix : " << new_expr << endl;

    strcpy(expr, new_expr);
    cout << "Eval of Postfix :" << endl;
    cout << "      Token | Stack\t\t\t    |  Top" << endl;

    int result = eval(expr);
    cout << "Eval : " << result << endl;

    return 0;
}

