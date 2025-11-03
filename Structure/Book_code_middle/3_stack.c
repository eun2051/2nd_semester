#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int key;
} element;
element stack[MAX_STACK_SIZE];
int top = -1;

bool IsEmpty() {
    return top == -1;
}

bool IsFull() {
    return top >= MAX_STACK_SIZE -1;
}

void push (element item) {
    if (IsFull()) {
        return ;
    }
    stack[++top] = item;
}

element pop()
{
    if (IsEmpty()) {
        element error_element = {-999};
        return error_element;
    }
    return stack[top--];
}

int main() {
    element item1 = {10}, item2 = {20};
    
    push(item1);
    push(item2);
    
    element p1 = pop();
    printf("Popped element key: %d\n", p1.key);
    
    element p2 = pop();
    printf("Popped element key: %d\n", p2.key);
    
    pop(); // 스택이 비었을 때 시도
    
    return 0;
}