#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

// 필수 구조체
typedef struct {
    int key;
} element;
element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

bool IsFull() {
    return rear == MAX_QUEUE_SIZE - 1;
}

bool IsEmpty() {
    return front == rear;
}

void addq(element item) {
    if (IsFull()) {
        printf("큐가 가득 찼습니다.\n");
        exit(1);
    }
    queue[++rear] = item;
}

element deleteq() {
    if (IsEmpty()) {
        printf("큐가 비었습니다.\n");
        exit(1);
    }
    return queue[++front];
}