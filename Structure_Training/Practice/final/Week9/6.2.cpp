#include <stdio.h>
#include <stdlib.h>

struct stack {
    struct node data;
    struct stack *next;
};
struct stack *top;

struct Que {
    struct node data;
    struct Que *next;
};
struct node {
    int data;
    struct node *next;
};
struct node *temp, *ptr, *A = NULL;
struct node *front = NULL;
struct node *rear = NULL;

//스택
/* A리스트에 데이터를 저장하고 삭제
insert_front를 이용하여 push() 구현
delete_front를 이용하여 pop() 구현 */
void insert_front(struct node **A, int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    temp->data = data;
    temp->next = *A;
    // temp와 기존 리스트가 연결되도록 함
    
    *A = temp;
    // 새 노드가 리스트의 top이 되도록 설정
}

void delete_front(struct node **start, struct node *before, struct node *A)
{
    //start : 시작 노드의 주소, before, A : 포인터
    if (before != NULL)
        before->next = A->next;
    else *start = (*start)->next;
    free(A);
}

void push(struct node **A, int data)
{
    insert_front(A, data);
}

int pop(struct node **A)
{
    if (*A == NULL) {
        fprintf(stderr, "stack empty\n");
        exit(1);
    }
    struct node *ptr = *A;
    int pop_data = ptr->data;
    delete_front(A, NULL, ptr);
    return pop_data;
}
//큐
/* A 리스트에 데이터를 저장하고 삭제
제일 마지막 노드는 rear에서 저장ㄴ
insert_last를 이용하여 add() 구현
delete_front를 이용하여 delete() 구현 */
void insert_last(struct node **A, int data)
{
    struct node *temp;
    struct node *ptr;

    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    temp->data = data;
    temp->next = NULL;
    if (*A == NULL) {
        *A = temp;
        return ;
    }
}

void insert_front(struct node **A, int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    temp->data = data;
    temp->next = *A;
    // temp와 기존 리스트가 연결되도록 함
    
    *A = temp;
    // 새 노드가 리스트의 top이 되도록 설정
}

void addq(int data)
{
    insert_last(&temp, data);
    //큐가 비어있을 경우
    if (front == NULL) {
        front = temp;
        //front와 rear 모드 새 노드 가리키게 함
        rear = temp;
    //큐가 비어있지 않은 경우
    } else {
        rear->next = temp;
        //기존 rear 뒤에 새 노드 연결
        rear = temp;
        // rear 포인터를 새 노드로 업데이트
    }
}

int deleteq()
{
    if (front == NULL) {
        fprintf(stderr, "Que empty\n");
        return -1;
    }
    //삭제할 노드 저장
    struct node *del_node = front;
    //데이터 저장
    int del_data = del_node->data;
    delete_front(&front, NULL, del_node);
    if (front==NULL) {
        rear = NULL;
    }
    return del_data;
}
