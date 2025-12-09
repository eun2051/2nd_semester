#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};
typedef struct node *Binarytree;
struct node *top = NULL;
struct node *front = NULL;
struct node *rear = NULL;

// 중위 순회
// L -> V -> R
void inorder(struct node *ptr) 
{
    if (ptr) {
        inorder(ptr->lchild);
        printf("%d", ptr->data);
        inorder(ptr->rchild);
    }
}

// 전위 순회
// V -> L -> R
void preorder(struct node *ptr)
{
    if (ptr) {
        printf("%d", ptr->data);
        preorder(ptr->lchild);
        preorder(ptr->rchild);
    }
}

// 후위 순회
// L -> R -> V
void postorder(struct node *ptr)
{
    if (ptr) {
        postorder(ptr->lchild);
        postorder(ptr->rchild);
        printf("%d", ptr->data);
    }
}

// 반복적 중위 탐색 iterative inorder traversal
// 스택을 이용하여 비순환적으로 inorder traversal 구현
void iter_inorder(struct node *node)
{
    for (; ;) {
        for (; node; node = node->lchild)
            push(node);
        node = pop();
        if (!node) break;
        printf("%d", node->data);
        node = node->rchild;
    }
}

void push(struct node *ptr)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node)); 
    if (temp == NULL) {
        fprintf(stderr, "memory error\n");
        exit(0);
    }
    temp->lchild = ptr;
    temp->rchild = top;
    top = temp;
}

// stack에서 '트리 노드 포인터'를 꺼내는 pop
struct node *pop()
{
    if (top == NULL) 
        return NULL;
    struct node *temp = top;
    struct node *save_node = temp->lchild;

    top = top->rchild;
    free(temp);
    return save_node;
}

// 레벨 순회 level order traversal
// 큐를 이용하여 level 순서대로 이진 트리 순회
void level_order(struct node *ptr)
{
    if (!ptr)
        return;
    addq(ptr);
    for (;;) {
        ptr = deleteq();
        if (ptr == NULL)
            break;
        printf("%d", ptr->data);
        if (ptr->lchild)
            addq(ptr->lchild);
        if (ptr->rchild)
            addq(ptr->rchild);
    }
}

void addq(struct node *ptr)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        fprintf(stderr, "empty queue\n");
        exit(0);
    }
    temp->lchild = ptr;
    temp->rchild = NULL;

    if (front == NULL) {
        front = temp;
    } else {
        rear->rchild = temp;
    }
    rear = temp;
}

struct node *deleteq()
{
    if (front == NULL)
        return NULL;
    struct node *temp = front;
    struct node *save_val = temp->lchild;

    front = front->rchild;

    if (front == NULL)
        rear = NULL;
    free(temp);
    return save_val;
}