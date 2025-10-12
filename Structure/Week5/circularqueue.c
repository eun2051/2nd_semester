void addq(element item)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == rear)
        queueFull();
    queue[rear] = item;
}

element deleteq()
{
    if (front == rear)
        return queueEmpty();
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}