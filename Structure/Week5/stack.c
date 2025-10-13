#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100

typedef struct {
    int key;
    // 다른 필드
} element;
element stack[MAX_STACK_SIZE];
int top = -1;
//스택이 가득 찼는지 확인
bool IsFull() {
    return top == MAX_STACK_SIZE - 1;
}
//스택이 비었는지 확인
bool IsEmpy() {
    return top == -1;
}

void push(element item) {
    if (IsFull()) {
        printf("스택이 가득 찼습니다.\n");
        return ;
    }
    stack[++top] = item;
}

element pop()
{
    if (IsEmpty()) {
        printf("스택이 비었습니다.\n");
        exit(1); //프로그램 종료
    }
    return stack[top--];
}