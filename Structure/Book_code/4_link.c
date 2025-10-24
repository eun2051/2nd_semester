#include <stdio.h>

struct node {
    int data;
    struct node *link;
};
//리스트를 이용한 스택의 선언
typedef struct {
    int key;
    /* other fields*/
} element;
struct stack {
    element data;
    struct stack *link;
};
struct stack *top;

//리스트에 삽입
void insert(struct node **start, struct node *before)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    temp->data = 50;
    if (*start != NULL) {
        temp->link = before->link;
        before->link = temp;
    } else {
        temp->link = NULL;
        *start = temp;
    }
}

//리스트에서 노드 삭제
//delete(&start, before, A)
/* start가 가리키는 리스트에서 노드 A 삭제
    before는 A노드의 이전 노드를 가리키고 있음*/
void delete(struct node **start, struct node *before, struct node *A)
{
    if (before != NULL)
        before->link = A->link;
    else *start = (*start)->link;
    free(A);
}