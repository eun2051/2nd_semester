#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
} element;
element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

bool IsFull() {
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

bool IsEmpty() {
    return front == rear;
}

void addq(element item) {
    if (IsFull()) {
        printf("원형 큐가 다 찼습니다.\n");
        return ;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}

element deleteq() {
    if (IsEmpty()) {
        printf("원형 큐가 비었습니다.\n");
        exit(1);
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}