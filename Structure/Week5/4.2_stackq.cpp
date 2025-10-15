/*큐의 구성
정수 배열
전역 변수 : int queue[10], front = -1, rear = -1

add, delete 함수 구현
- void add_q(int item)
- int delete_q()
*/
#include <iostream>
#include <cstdlib>

using namespace std;

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
            cout << "큐가 비어있습니다." << endl;
            return;
        }
        for (int i = front + 1; i <= rear; ++i) {
            cout << "      " << i << " :  " << queue[i] << endl;
        }
    }
};

int main() {
    SimpleQueue myqueue(10);
    int choice;
    int item_add;

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
                int delete_item = myqueue.deleteq();
                cout << "deleteQ item : " << delete_item << endl;
                break;
            default:
                cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                break;
        }
        myqueue.printState();
        cout << endl;
    }
    return 0;
}