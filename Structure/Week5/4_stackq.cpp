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

    bool Stack_isEmpty() {
        return top == -1;
    }

    bool Stack_isFull() {
        return top == max_stack_size - 1;
    }

    void push(int item) {
        if (Stack_isFull()) {
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
        if (Stack_isEmpty()) {
            cerr << "스택이 비었습니다." << endl;
            exit(1);
        }
        return stack[top--];
    }

    void printState() {
        cout << "  index : item" << endl;
        if (Stack_isEmpty()) {
            cout << " " << endl;
            return;
        }
        for (int i = 0; i <= top; ++i) {
            cout << "      " << i << " :  " << stack[i] << endl;
        }
    }
};

class SimpleQueue {
private:
    int *queue;
    int front;
    int rear;
    int max_size;

public:
    SimpleQueue(int initial_size) {
        queue = (int*)malloc(initial_size * sizeof(int));
        if (queue == nullptr) {
            cerr << "메모리 할당 실패." << endl;
            exit(1);
        }
        front = -1;
        rear = -1;
        max_size = initial_size;
    }

    ~SimpleQueue() {
        free(queue);
    }

    bool Queue_isEmpty() {
        return front == rear;
    }

    bool Queue_isFull() {
        return rear == max_size - 1;
    }

    void add_q(int item) {
        if (Queue_isEmpty()) {
            cout << "일반 큐가 가득 찼습니다. 크기를 두 배로 재할당합니다." << endl;
            int new_size = max_size * 2;
            int* new_queue = (int*)realloc(queue, new_size * sizeof(int));
            if (new_queue == nullptr) {
                cerr << "메모리 재할당 실패." << endl;
                exit(1);
            }
            queue = new_queue;
            max_size = new_size;
        }
        queue[++rear] = item;
    }

    int deleteq() {
        if (Queue_isEmpty()) {
            cerr << "일반 큐가 비었습니다." << endl;
            exit(1);
        }
        return queue[++front];
    }

    void printState() {
        cout << "  index : item" << endl;
        if (Queue_isEmpty()) {
            cout << " " << endl;
            return;
        }
        for (int i = front + 1; i <= rear; ++i) {
            cout << "      " << i << " :  " << queue[i] << endl;
        }
    }
};

class CircularQueue {
private:
    int *queue;
    int front;
    int rear;
    int max_size;

public:
    CircularQueue(int initial_size) {
        queue = (int*)malloc(initial_size * sizeof(int));
        if (queue == nullptr) {
            cerr << "메모리 할당 실패." << endl;
            exit(1);
        }
        front = 0;
        rear = 0;
        max_size = initial_size;
    }

    ~CircularQueue() {
        free(queue);
    }

    bool isEmpty() {
        return front == rear;
    }

    bool isFull() {
        return (rear + 1) % max_size == front;
    }

    void add_cq(int item) {
        if (isFull()) {
            cout << "원형 큐가 가득 찼습니다. 크기를 두 배로 재할당합니다." << endl;
            int old_size = max_size;
            max_size *= 2;
            int* new_queue = (int*)realloc(queue, max_size * sizeof(int));
            if (new_queue == nullptr) {
                cerr << "메모리 재할당 실패." << endl;
                exit(1);
            }
            if (front > rear) {
                for (int i = 0; i < front; ++i) {
                    new_queue[i + old_size] = new_queue[i];
                }
                front += old_size;
            }
            queue = new_queue;
        }
        rear = (rear + 1) % max_size;
        queue[rear] = item;
    }

    int deleteq() {
        if (isEmpty()) {
            cerr << "원형 큐가 비었습니다." << endl;
            exit(1);
        }
        front = (front + 1) % max_size;
        return queue[front];
    }

    void printState() {
        cout << "  index : item" << endl;
        if (isEmpty()) {
            cout << " " << endl;
            return;
        }
        for (int i = front + 1; i <= rear; ++i) {
            cout << "      " << i << " :  " << queue[i] << endl;
        }
    }
};


int main() {
    DynamicStack myStack(10);
    SimpleQueue myqueue(10);
    CircularQueue circlequeue(10);
    int choice;
    int item_to_push;
    int item_add;
    

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
    cout << "\n" << endl;

    cout << "4.2. 큐" << endl;

    while (true) {
        cout << "큐 - 1.addCQ 2.deleteCQ : ";
        cin >> choice;

        if (cin.fail() || choice == -1) {
            break;
        }
        
        switch (choice) {
            case 1:
                cout << "addQ item : ";
                cin >> item_add;
                myqueue.add_q(item_add);
                break;
            case 2:
                try {
                    int delete_item = myqueue.deleteq();
                    cout << "deleteQ item : " << delete_item << endl;
                } catch (const exception& e) {
                    cout << "delete 실패 "<< endl;
                    break;
                }
            default:
                cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                break;
        }
        myqueue.printState();
        cout << endl;
    }
    cout << "\n" << endl;
    cout << "4.3. 원형 큐" << endl;

    while (true) {
        cout << "원형큐 - 1.addCQ 2.deleteCQ : ";
        cin >> choice;

        if (cin.fail() || choice == -1) {
            break;
        }
        switch (choice) {
            case 1:
                cout << "addCQ item : ";
                cin >> item_add;
                circlequeue.add_cq(item_add);
                break;
            case 2:
                try {
                    int delete_item = circlequeue.deleteq();
                    cout << "deleteQ item : " << delete_item << endl;
                } catch (const exception& e) {
                    cout << "delete 실패 "<< endl;
                    break;
                }
            default:
                cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                break;
        }
        circlequeue.printState();
        cout << endl;
    }
    return 0;
}