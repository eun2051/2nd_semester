/*스택의 구성
정수배열
전역변수 : int stack[10], top = -1;

push , pop 함수 구현
- void push(int item)
- int pop()

> main에서 여러번 push(), pop() 연산을 호출하고,
각 연산이 실행된 후의 스택 상황을 관찰하여 관찰지 작성
*/
#include <iostream>
#include <cstdlib>

using namespace std;

class DynamicStack {
private:
    int *stack;
    int top;
    int max_stack_size;

public:
    DynamicStack(int initial_size) {
        stack = (int*)malloc(initial_size * sizeof(int));
        if (stack == nullptr) {
            cerr << "메모리 할당 실패." << endl;
            exit(1);
        }
        top = -1;
        max_stack_size = initial_size;
    }

    ~DynamicStack() {
        free(stack);
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == max_stack_size - 1;
    }

    void push(int item) {
        if (isFull()) {
            cout << "스택이 가득 찼습니다. 크기를 두 배로 재할당합니다." << endl;
            max_stack_size *= 2;
            int* new_stack = (int*)realloc(stack, max_stack_size * sizeof(int));
            if (new_stack == nullptr) {
                cerr << "메모리 재할당 실패." << endl;
                exit(1);
            }
            stack = new_stack;
        }
        stack[++top] = item;
    }

    int pop() {
        if (isEmpty()) {
            cerr << "스택이 비었습니다." << endl;
            exit(1);
        }
        return stack[top--];
    }

    void printState() {
        cout << "  index : item" << endl;
        if (isEmpty()) {
            cout << "스택이 비어있습니다." << endl;
            return;
        }
        for (int i = 0; i <= top; ++i) {
            cout << "      " << i << " :  " << stack[i] << endl;
        }
    }
};

int main() {
    DynamicStack myStack(10);
    int choice;
    int item_to_push;

    cout << "4.1. 스택" << endl;
    
    while (true) {
        cout << "스택 - 1.push 2.pop : ";
        cin >> choice;

        if (cin.fail() || choice == -1) {
            break;
        }

        switch (choice) {
            case 1:
                cout << "push item : ";
                cin >> item_to_push;
                myStack.push(item_to_push);
                break;
            case 2:
                try {
                    int popped_item = myStack.pop();
                    cout << "pop item : " << popped_item << endl;
                } catch (const exception& e) {
                    cout << "pop 실패 "<< endl;
                    break;
                }
                break;
            default:
                cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                break;
        }
        myStack.printState();
        cout << endl;
    }
    return 0;
}