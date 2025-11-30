#include <iostream>
#include <stdlib.h>
using namespace std;

class DynamicStack {
private:
    int *stack;
    int top;
    int max_stack_size;
public:
    DynamicStack(int initial_size) {
        if (initial_size <= 0) {
            throw invalid_argument("할당에 실패하였습니다.");
        }
        stack = new int[initial_size];
        top = -1;
        max_stack_size = initial_size;
    }

    ~DynamicStack() {
        delete[] stack;
    }

    bool Stack_isEmpty() {
        return top == -1;
    }

    bool Stack_isFull() {
        return top == max_stack_size - 1;
    }

    void push(int item) {
        if (Stack_isFull()) {
            cout << "스택이 가득 찼습니다." << endl;
            int new_size = max_stack_size * 2;
            int *new_stack = new int[new_size];
            copy(stack, stack + max_stack_size, new_stack);
            delete[] stack;
            stack = new_stack;
            max_stack_size = new_size;
        }
        stack[++top] = item;
    }

    int pop() {
        if (Stack_isEmpty()) {
            throw out_of_range("스택이 비었습니다");
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
        if (initial_size <= 0) {
            throw invalid_argument("할당에 실패하엿습니다.");
        }
        queue = new int[initial_size];
        front = -1;
        rear = -1;
        max_size = initial_size;
    }

    ~SimpleQueue() {
        delete[] queue;
    }

    bool Queue_isEmpty() {
        return front == rear;
    }

    bool Queue_isFull() {
        return rear == max_size - 1;
    }

    void add_q(int item) {
        if (Queue_isFull()) {
            cout << "큐가 가득 찼습니다." << endl;
            int new_size = max_size * 2;
            int *new_queue = new int[new_size];
            for (int i = front + 1; i <= rear; ++i) {
                new_queue[i - (front + 1)] = queue[i];
            }
            int current_count = rear - front;
            delete[] queue;
            queue = new_queue;
            max_size = new_size;
            front = -1;
            rear = current_count - 1;
        }
        queue[++rear] = item;
    }

    int deleteq() {
        if (Queue_isEmpty()) {
            throw out_of_range("큐가 비었습니다.");
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
    int *cqueue;
    int front;
    int rear;
    int max_size;
public:
    CircularQueue(int initial_size) {
        if (initial_size <= 0) {
            throw invalid_argument("할당에 실패했습니다.");
        }
        max_size = initial_size + 1;
        cqueue = new int[max_size];
        front = 4;
        rear = 4;
    }

    ~CircularQueue() {
        delete[] cqueue;
    }

    bool isEmpty() {
        return front == rear;
    }

    bool isFull() {
        return (rear + 1) % max_size == front;
    }

    void add_cq(int item) {
        if (isFull()) {
            cout << "원형 큐가 가득 찼습니다. 크기를 확장합니다." << endl;
            int old_size = max_size;
            int new_size = (old_size - 1) * 2 + 1;
            int* new_queue = new int[new_size];
            
            int count = 0;
            int current_index = (front + 1) % old_size;
            while (current_index != (rear + 1) % old_size) {
                new_queue[(4 + count) % new_size] = cqueue[current_index];
                current_index = (current_index + 1) % old_size;
                count++;
            }
            delete[] cqueue;
            cqueue = new_queue;
            max_size = new_size;
            front = 4;
            rear = (front + count - 1) % max_size;
        }
        rear = (rear + 1) % max_size;
        cqueue[rear] = item;
    }
    
    int deleteq() {
        if (isEmpty()) {
            throw out_of_range("원형 큐가 비었습니다.");
        }
        front = (front + 1) % max_size;
        return cqueue[front];
    }

    void printState() {
        cout << "  index : item" << endl;
        if (isEmpty()) {
            cout << " " << endl;
            return;
        }
        int current_index = (front + 1) % max_size;
        while (current_index != (rear + 1) % max_size) {
            cout << "      " << current_index << " :  " << cqueue[current_index] << endl;
            if (current_index == rear) break;
            current_index = (current_index + 1) % max_size;
        }
    }
};


int main() {
    try {
        DynamicStack myStack(10);
        SimpleQueue myqueue(10);
        CircularQueue circlequeue(10);
        int choice;
        int item;
        
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
                    cin >> item;
                    myStack.push(item);
                    break;
                case 2:
                    try {
                        int popped_item = myStack.pop();
                        cout << "pop item : " << popped_item << endl;
                    } catch (const out_of_range& e) {
                        cerr << "pop 실패 "<< endl;
                    }
                    break;
                default:
                    cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                    break;
            }
            myStack.printState();
            cout << endl;
        }

        cout << "\n4.2. 큐" << endl;
        while (true) {
            cout << "큐 - 1.addQ 2.deleteQ : ";
            cin >> choice;
            if (cin.fail() || choice == -1) {
                break;
            }
            switch (choice) {
                case 1:
                    cout << "addQ item : ";
                    cin >> item;
                    myqueue.add_q(item);
                    break;
                case 2:
                    try {
                        int delete_item = myqueue.deleteq();
                        cout << "deleteQ item : " << delete_item << endl;
                    } catch (const out_of_range& e) {
                        cerr << "delete 실패 "<< endl;
                    }
                    break;
                default:
                    cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                    break;
            }
            myqueue.printState();
            cout << endl;
        }

        cout << "\n4.3. 원형 큐" << endl;
        while (true) {
            cout << "원형큐 - 1.addCQ 2.deleteCQ : ";
            cin >> choice;
            if (cin.fail() || choice == -1) {
                break;
            }
            switch (choice) {
                case 1:
                    cout << "addCQ item : ";
                    cin >> item;
                    circlequeue.add_cq(item);
                    break;
                case 2:
                    try {
                        int delete_item = circlequeue.deleteq();
                        cout << "deleteQ item : " << delete_item << endl;
                    } catch (const out_of_range& e) {
                        cerr << "delete 실패 "<< endl;
                    }
                    break;
                default:
                    cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                    break;
            }
            circlequeue.printState();
            cout << endl;
        }
    } catch (const invalid_argument& e) {
        cerr << "초기화 오류: " << endl;
    } catch (const bad_alloc& e) {
        cerr << "메모리 할당 오류: " << endl;
    }
    return 0;
}