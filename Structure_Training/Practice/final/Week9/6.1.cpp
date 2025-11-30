#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
struct node *A = NULL;

// A리스트의 제일 앞의 data를 갖는 새로운 노드 추가
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

// A리스트의 내용을 앞에서부터 차례대로 출력
void print_list(struct node *A)
{
    struct node *ptr;

    for (ptr = A; ptr != NULL; ptr = ptr->next)
        printf("%d ", ptr->data);
}

// A리스트의 제일 뒤에 data를 갖는 새로운 노드 추가
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

/* A리스트에서 몇 번째 노드에서 data가 저장되어 있는지를 출력
(노드 번호는 0부터 시작된다고 가정) */
int search (struct node *A, int data)
{
    struct node *now;
    int index = 0;
    now = A;
    while (now != NULL){
        if (now->data == data) {
            return index;
        }
        now = now->next;
        index++;
    }
    return -1;
}

/* A 리스트에서 첫번째 노트를 삭제하고, 
그 노드에 저장된 data를 return */
int delete_front (struct node **A)
{
    if (*A == NULL) {
        fprintf(stderr, "list empty\n");
        return -1;
    }
    struct node *delete_node = *A;
    int del_data = delete_node->data;
    *A = (*A)->next;
    free(delete_node);
    return del_data;
}

/* A리스트에서 data가 저장된 노드를 삭제*/
int delete_(struct node **A, int data)
{
    struct node *now = *A;
    struct node *before = NULL;
    while (now != NULL){
        if (now->data == data) {
            break;
        }
        before = now;
        now = now->next;
    }
    if (now == NULL)
        return 0;
    if (before == NULL) {
        *A = now->next;
    } else {
        before->next = now->next;
    }
    free(now);
    return 1;
}