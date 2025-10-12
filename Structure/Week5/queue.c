void addq(element item)
{ /*queue에 item 삽입*/
    if (rear == MAX_QUEUE_SIZE - 1)
        queueFull();
    queue[++rear] = item;
}

element deleteq()
{ /*queue 앞에 있는 원소 삭제*/
    if (front == rear)
        return queueEmpty();
    return queue[++front];
}