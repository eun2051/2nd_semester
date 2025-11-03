#include <iostream>
#include <cstring>
#include <cctype> 
#include <string>
#define MAX_EXPR_SIZE 100
#define MAX_STACK_SIZE 100
#define ERROR_KEY -999
using namespace std;

typedef enum {
    lparen, rparen, plus, minus,
    times, divide, mod, eos,
    operand, err_code
} precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

precedence getToken(char* expr, char* symbol, int* n) {
    int i = *n;
    char ch = expr[i];

    while (ch == ' ') {
        ch = expr[++i];
    }

    *symbol = ch;
    
    if (isdigit(ch)) {
        *n = i + 1;
        return operand;
    } else {
        *n = i + 1;
        switch (ch) {
            case '(': return lparen;
            case ')': return rparen;
            case '+': return plus;
            case '-': return minus;
            case '*': return times;
            case '/': return divide;
            case '%': return mod;
            case '\0': return eos;
            default: return eos;
        }
    }
}

char printToken(precedence token) {
    switch (token) {
        case lparen: return '(';
        case rparen: return ')';
        case plus: return '+';
        case minus: return '-';
        case times: return '*';
        case divide: return '/';
        case mod: return '%';
        case eos: return '\0';
        default: return ' ';
    }
}

string int_to_string(int n) {
    if (n == 0) return "0";
    bool is_negative = n < 0;
    if (is_negative) n = -n;
    
    string s = "";
    while (n > 0) {
        s = (char)('0' + (n % 10)) + s;
        n /= 10;
    }
    
    if (is_negative) s = "-" + s;
    return s;
}

string align_right(const string& s, int width) {
    if ((int)s.length() >= width) {
        return s;
    } else {
        return string(width - s.length(), ' ') + s;
    }
}

string align_left(const string& s, int width) {
    if ((int)s.length() >= width) {
        return s;
    } else {
        return s + string(width - s.length(), ' ');
    }
}

struct IntStack {
    int data[MAX_STACK_SIZE];
    int top;

    IntStack() : top(-1) {}
    bool is_empty() { return top == -1; }
    void push_internal(int item) { data[++top] = item; }
    int pop_internal() { return is_empty() ? ERROR_KEY : data[top--]; }
    
    string get_stack_string() {
        string s = "";
        for (int i = 0; i <= top; ++i) {
            s += int_to_string(data[i]);
            s += " ";
        }
        return s;
    }
};

struct PrecedenceStack {
    precedence data[MAX_STACK_SIZE];
    int top;

    PrecedenceStack() : top(-1) {}
    bool is_empty() { return top == -1; }
    void push_internal(precedence item) { data[++top] = item; }
    precedence pop_internal() { return is_empty() ? eos : data[top--]; }
    precedence peek_internal() { return is_empty() ? eos : data[top]; }

    string get_stack_string() {
        string s = "";
        for (int i = 0; i <= top; ++i) {
            s += printToken(data[i]);
            s += " ";
        }
        return s;
    }
};

void postfix(char* expr, char* new_expr) {
    PrecedenceStack stack;
    char symbol;
    precedence token;
    int n = 0;
    int new_expr_idx = 0;
    string output = "";

    cout << "\n--- (1) Infix -> Postfix 변환 시작 ---" << endl;
    cout << "Infix: " << expr << endl;
    
    const int W_TOKEN = 8;
    const int W_STACK = 25;
    const int W_TOP = 5;
    
    cout << align_right("Token", W_TOKEN) << " | " 
         << align_left("Stack", W_STACK) << " | " 
         << align_right("Top", W_TOP) << " | " 
         << "Output" << endl;
    cout << string(W_TOKEN + W_STACK + W_TOP + 6, '-') << endl;

    stack.push_internal(eos); 

    token = getToken(expr, &symbol, &n);
    while (token != eos) {
        cout << align_right(string(1, symbol), W_TOKEN) << " | " 
             << align_left(stack.get_stack_string(), W_STACK) << " | " 
             << align_right(int_to_string(stack.top), W_TOP) << " | " 
             << output << endl;
        
        if (token == operand) {
            new_expr[new_expr_idx++] = symbol;
            new_expr[new_expr_idx++] = ' ';
            output += symbol;
            output += " ";
        } else if (token == rparen) {
            while (stack.peek_internal() != lparen && stack.peek_internal() != eos) {
                char op_char = printToken(stack.pop_internal());
                new_expr[new_expr_idx++] = op_char;
                new_expr[new_expr_idx++] = ' ';
                output += op_char;
                output += " ";
            }
            if (stack.peek_internal() == lparen) {
                stack.pop_internal();
            }
        } else {
            while (isp[stack.peek_internal()] >= icp[token] && stack.peek_internal() != eos) {
                char op_char = printToken(stack.pop_internal());
                new_expr[new_expr_idx++] = op_char;
                new_expr[new_expr_idx++] = ' ';
                output += op_char;
                output += " ";
            }
            stack.push_internal(token);
        }
        token = getToken(expr, &symbol, &n);
    }

    cout << align_right("\\0", W_TOKEN) << " | " 
         << align_left(stack.get_stack_string(), W_STACK) << " | " 
         << align_right(int_to_string(stack.top), W_TOP) << " | " 
         << output << endl;

    while (stack.peek_internal() != eos) {
        char op_char = printToken(stack.pop_internal());
        new_expr[new_expr_idx++] = op_char;
        new_expr[new_expr_idx++] = ' ';
        output += op_char;
        output += " ";
    }
    
    new_expr[new_expr_idx] = '\0';

    cout << string(W_TOKEN + W_STACK + W_TOP + 6, '-') << endl;
    cout << "\n--- (1) Postfix 변환 완료 ---" << endl;
    cout << align_right("Final", W_TOKEN) << " | " 
         << align_left("", W_STACK) << " | " 
         << align_right(int_to_string(stack.top), W_TOP) << " | " 
         << output << endl;
    cout << "------------------------------------------" << endl;
}

int eval(char* expr) {
    IntStack stack;
    char symbol;
    precedence token;
    int n = 0;
    int op1, op2;
    int result = ERROR_KEY;

    cout << "\n--- (2) Postfix 계산 시작 ---" << endl;
    cout << "Postfix: " << expr << endl;

    // 헤더 출력 폭 설정
    const int W_TOKEN = 8;
    const int W_STACK = 35;
    
    cout << align_right("Token", W_TOKEN) << " | " 
         << align_left("Stack", W_STACK) << " | " 
         << "Top" << endl;
    cout << string(W_TOKEN + W_STACK + 5, '-') << endl;

    token = getToken(expr, &symbol, &n);
    while (token != eos) {
        if (token == operand) {
            stack.push_internal(symbol - '0'); // 문자를 숫자로 변환
            cout << align_right(string(1, symbol), W_TOKEN) << " | " 
                 << align_left(stack.get_stack_string(), W_STACK) << " | " 
                 << stack.top << endl;
        } else {
            // 연산자일 경우, 스택에서 두 피연산자를 pop
            op2 = stack.pop_internal();
            op1 = stack.pop_internal();

            if (op1 == ERROR_KEY || op2 == ERROR_KEY) return ERROR_KEY;

            int sub_result = 0;
            switch (token) {
                case plus: sub_result = op1 + op2; break;
                case minus: sub_result = op1 - op2; break;
                case times: sub_result = op1 * op2; break;
                case divide: 
                    if (op2 == 0) { cerr << "Division by zero!" << endl; return ERROR_KEY; }
                    sub_result = op1 / op2; 
                    break;
                case mod: sub_result = op1 % op2; break;
                default: break;
            }
            
            stack.push_internal(sub_result);
            cout << align_right(string(1, symbol), W_TOKEN) << " | " 
                 << align_left(stack.get_stack_string(), W_STACK) << " | " 
                 << stack.top << endl;
        }
        token = getToken(expr, &symbol, &n);
    }
    
    // 최종 결과
    if (stack.top == 0) {
        result = stack.pop_internal();
    } else {
        result = ERROR_KEY;
    }
    
    cout << string(W_TOKEN + W_STACK + 5, '-') << endl;
    cout << "\n--- (2) Postfix 계산 완료 ---" << endl;
    return result;
}

//---------------------------------------------------------
// Main 함수
//---------------------------------------------------------

int main() {
    char expr[MAX_EXPR_SIZE];
    char new_expr[MAX_EXPR_SIZE * 2]; 
    int final_result;

    // Infix: ((((6/2)-3+(4*2))-5*3))
    strcpy(expr, "((((6/2)-3+(4*2))-5*3))");

    // (1) postfix(expr, new_expr) 호출 및 과정 관찰
    postfix(expr, new_expr);

    // (2) eval(new_expr) 호출 및 과정 관찰
    final_result = eval(new_expr);
    
    // (2) 실행 결과 출력
    if (final_result != ERROR_KEY) {
        cout << "==========================================" << endl;
        cout << "최종 연산 결과: " << final_result << endl;
        cout << "==========================================" << endl;
    } else {
        cout << "연산 오류로 결과를 출력할 수 없습니다." << endl;
    }

    return 0;
}