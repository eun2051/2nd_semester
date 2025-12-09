#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};
typedef struct node *Binarytree;

// 빈 이진트리를 생성
Binarytree Create()
{
        return NULL;
}

// 이진트리가 비어있는지 확인한다
int IsEmpty(Binarytree ptr) 
{
    return(ptr == NULL);
}

// 두 개의 서브트리를 결합하여 새 트리 생성
// 주어진 item을 루트 node 데이터로 사용하고, bt1을 왼족, bt2을 오른쪽 자식으로 하는 새로운 트리 생성
Binarytree MakeBT(Binarytree bt1, int item, Binarytree bt2)
{
    Binarytree new_node = (Binarytree)malloc(sizeof(struct node));

    if (new_node == NULL) {
        fprintf(stderr, "memory error\n");
        exit(0);
    }
    new_node->data = item;
    new_node->lchild = bt1;
    new_node->rchild = bt2;

    return new_node;
}

// 루트 노드의 데이터 반환
// -> 트리가 비어있지 않다면 루트 노드의 데이터 반환
int Root(Binarytree ptr)
{
    if (ptr == NULL) {
        fprintf(stderr, "empty tree\n");
        exit(0);
    }
    return ptr->data;
}

// 오른쪽 자식 서브트리 반환
// 루트 노드의 오른쪽 자식 서브트리를 반환한다
Binarytree Rchild(Binarytree ptr)
{
    if (ptr == NULL)
        return NULL;
    return ptr->rchild;
}