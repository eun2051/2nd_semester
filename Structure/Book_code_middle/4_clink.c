#include <stdio.h>
#include <stdlib.h>

typedef int element;

struct node {
    element data;
    struct node *link;
};

struct node *last = NULL;

void insert_front (struct node **last, struct node *node)
{
    if (*last == NULL) {
        *last = node;
        node->link = node;
    } else {
        node->link = (*last)->link;
        (*last)->link = node;
    }
}

// ptr이 가리키는 원형 리스트의 노드 수를 return
int length(struct node *ptr)
{
    struct node *t;
    int count = 0;
    if (ptr != NULL) {
        t = ptr;
        do {
            count++;
            t = t->link;
        } while (t != ptr);
    }
    return count;
}

void addq(struct node *ptr) {
    if (last == NULL) {
        last = ptr;
        last->link = last;
    } else {
        ptr->link = last->link;
        last->link = ptr;
        last = ptr;
    }
}

struct node *deletecq() {
    struct node *delete_ptr;
    if (last == NULL) {
        return NULL;
    } else {
        delete_ptr = last->link;
        if (delete_ptr == last) {
            last = NULL;
        } else {
            last->link = delete_ptr->link;
        }
        delete_ptr->link = NULL;
        return delete_ptr;
    }
}

struct node *create_node(element data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->link = NULL;
    return new_node;
}

int main() {
    struct node *deleted_node;

    printf("--- 원형 큐 간편 테스트 ---\n");

    // 1. 삽입 (Enqueue) - 간결하게 create_node 함수 호출
    printf("1. 삽입: 10, 20, 30\n");
    addq(create_node(10));
    addq(create_node(20));
    addq(create_node(30));

    printf("   [확인] Front (last->link->data): %d\n", last->link->data); 
    
    // 2. 삭제 (Dequeue)
    printf("2. 삭제:\n");
    
    deleted_node = deletecq();
    printf("   삭제 요소 1: %d\n", deleted_node->data);
    free(deleted_node);

    deleted_node = deletecq();
    printf("   삭제 요소 2: %d\n", deleted_node->data);
    free(deleted_node);

    deleted_node = deletecq();
    printf("   삭제 요소 3: %d\n", deleted_node->data);
    free(deleted_node);

    // 3. 최종 확인
    printf("3. 최종: last가 NULL? %s\n", (last == NULL ? "예" : "아니오")); 

    return 0;
}