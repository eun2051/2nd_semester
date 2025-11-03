#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
struct node *temp, *ptr, *A = NULL;

void insert_front(struct node **list, int data);
void print_list(struct node *list, const char *name);
void insert_last(struct node **list, int data);
int search (struct node *list, int data);
int delete_front (struct node **list);
int delete_(struct node **list, int data);
void push(int data);
int pop();
void addq(int data);
int deleteq();
void clear_list(struct node **list);
void list_print();
void stack_print();
void Que_print();

int main()
{
    list_print();
    stack_print();
    Que_print();
    while(delete_front(&A) != -1);
    return 0;
}

void clear_list(struct node **list)
{
    int data;
    while ((data = delete_front(list)) != -1);
}

void list_print() {
    int ans, data, result;
    while(1) {
        printf("\n리스트 기본연산\n");
        printf("0. print list\n1. insert_front\n2. insert_last\n");
        printf("3. delete_front\n4. delete_\n5. search\n-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &ans);
        if (ans == -1) {
            printf("Bye-bye ~");
            return ;
        }
        switch (ans) {
            case 0:
                print_list(A, "리스트");
                break;
            case 1:
                printf("데이터 : ");
                scanf("%d", &data);
                insert_front(&A, data);
                print_list(A, "리스트");
                break;
            case 2:
                printf("데이터 : ");
                scanf("%d", &data);
                insert_last(&A, data);
                print_list(A, "리스트");
                break;
            case 3:
                result = delete_front(&A);
                if (result != -1) {
                    printf("삭제 데이터 : %d\n", result);
                } else {
                    exit(1);
                }
                print_list(A, "리스트");
                break;
            case 4:
                printf("데이터 : ");
                scanf("%d", &data);
                result = delete_(&A, data);
                if (result) {
                    printf("삭제 데이터 : %d\n", data);
                } else {
                    printf("삭제 데이터 : -999\n");
                }
                print_list(A, "리스트");
                break;
            case 5:
                printf("찾을 데이터 : ");
                scanf("%d", &data);
                result = search(A, data);
                if (result != -1) {
                    printf("노드번호 : %d\n", result);
                } else {
                    printf("노드번호 : -1 (데이터 %d)를 찾을 수 없습니다.)\n", data);
                }
                print_list(A, "리스트");
                break;
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
        }
    }
}

void stack_print() {
    int ans, data, result;
    clear_list(&A);
    while(1) {
        printf("\n리스트로 구현한 스택\n");
        printf("1. push\n2. pop\n-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &ans);
        if (ans == -1) {
            printf("Bye-bye ~");
            return ;
        }
        switch (ans) {
            case 1:
                printf("push item : ");
                scanf("%d", &data);
                push(data);
                print_list(A, "Stack");
                break;
            case 2:
                result = pop();
                if (result != -1) {
                    printf("pop item : %d\n", result);
                }
                print_list(A, "Stack");
                break;
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
        }
    }
}

void Que_print() {
    int ans, data, result;
    clear_list(&A);
    while(1) {
        printf("\n리스트로 구현한 큐\n");
        printf("1. addq\n2. deleteq\n-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &ans);
        if (ans == -1) {
            printf("Bye-bye ~");
            return ;
        }
        switch (ans) {
            case 1:
                printf("addq item : ");
                scanf("%d", &data);
                addq(data);
                print_list(A, "Queue");
                break;
            case 2:
                result = deleteq();
                if (result != -1) {
                    printf("deleteq item : %d\n", result);
                }
                print_list(A, "Queue");
                break;
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
        }
    }
}

void insert_front(struct node **list, int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    temp->data = data;
    temp->next = *list;
    *list = temp;
}

void print_list(struct node *list, const char *name)
{
    struct node *ptr;
    printf("%s : Head", name);
    for (ptr = list; ptr != NULL; ptr = ptr->next)
        printf("->%d ", ptr->data);
    printf("->NULL\n");
}

void insert_last(struct node **list, int data)
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
    if (*list == NULL) {
        *list = temp;
        return ;
    }
    for (ptr = *list; ptr->next != NULL; ptr = ptr->next);
    ptr->next = temp;
}

int search (struct node *list, int data)
{
    struct node *now;
    int index = 0;
    now = list;
    while (now != NULL){
        if (now->data == data) {
            return index;
        }
        now = now->next;
        index++;
    }
    return -1;
}

int delete_front (struct node **list)
{
    if (*list == NULL) {
        return -1;
    }
    struct node *del_node = *list;
    int del_data = del_node->data;
    *list = (*list)->next;
    free(del_node);
    return del_data;
}

int delete_(struct node **list, int data)
{
    struct node *now = *list;
    struct node *before = NULL;
    while (now != NULL){
        if (now->data == data) {
            break;
        }
        before = now;
        now = now->next;
    }
    if (now == NULL) return 0;
    if (before == NULL) {
        *list = now->next;
    } else {
        before->next = now->next;
    }
    free(now);
    return 1;
}

void push(int data)
{
    insert_front(&A, data);
}

int pop()
{
    return delete_front(&A);
}

void addq(int data)
{
    insert_last(&A, data);
}

int deleteq()
{
    return delete_front(&A);
}