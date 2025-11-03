#include <stdio.h>
#include <stdbool.h>
#define MAX_Q_SIZE 100
typedef struct {
    int key;
} element;
element queue[MAX_Q_SIZE];
int rear = -1, front = -1;

bool IsEmptyQ() {
    return front == rear;
}

bool IsFullQ() {
    return rear == MAX_Q_SIZE - 1;
}

void addq(element item)
{
    if (IsFullQ())
        return ;
    queue[++rear] = item;
}

element deleteq()
{
    if (IsEmptyQ()) {
        element empty_e = {-999};
        return empty_e;
    }  
    return queue[++front];
}
