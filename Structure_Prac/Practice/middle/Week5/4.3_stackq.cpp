/*원형 큐의 구성
정수 배열
전역변수 : int queue[10], front = 4, rear = 4;

add, delete 함수 구현
- void add_cq(int item)
- int delete_cq()
*/
#include <iostream>
#include <cstdlib>

using namespace std;

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
            // 기존 원소들을 새로운 배열의 앞쪽으로 이동
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
            cout << "큐가 비어있습니다." << endl;
            return;
        }
        for (int i = front + 1; i <= rear; ++i) {
            cout << "      " << i << " :  " << queue[i] << endl;
        }
    }
};

int main() {
    CircularQueue circlequeue(10);
    int choice;
    int item_add;

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
                int delete_item = circlequeue.deleteq();
                cout << "deleteCQ item : " << delete_item << endl;
                break;
            default:
                cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
                break;
        }
        circlequeue.printState();
        cout << endl;
    }
    return 0;
}