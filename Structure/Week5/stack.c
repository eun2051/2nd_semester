void push(element item)
{
    /*전역 stack에 item 삽입*/
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

element pop()
{ /*stack의 최상위 원소를 삭제하고 반환*/
    if (top == -1)
        emptyStack
}