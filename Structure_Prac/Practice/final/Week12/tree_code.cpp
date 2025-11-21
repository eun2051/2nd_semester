#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct node *treePointer;
struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};

// 새 노드를 만드는 헬퍼 함수
treePointer createNode(int data) {
    treePointer newNode = (treePointer)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

// 이진 트리의 복사
// 주어진 트리를 복사하고 복사된 트리의 treePointer를 반환
treePointer copy(treePointer original)
{
    treePointer temp;
    if (original) {
        temp = (treePointer)malloc(sizeof(struct node));
        temp->lchild = copy(original->lchild);
        temp->rchild = copy(original->rchild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

// 이진 트리의 동일성
// 두 이진 트리가 동일하면 TRUE, 그렇지 않으면 FALSE 반환
int equal(treePointer first, treePointer second)
{
    return((!first && !second) || (first && second &&
        (first->data == second->data) &&
        equal(first->lchild, second->lchild) &&
        equal(first->rchild, second->rchild)));
}

int main() {
    // 원본 트리 생성
    /*
         10
        /  \
       20  30
    */
    treePointer root1 = createNode(10);
    root1->lchild = createNode(20);
    root1->rchild = createNode(30);

    // 1. 트리 복사 테스트
    treePointer root2 = copy(root1);
    printf("트리가 복사되었습니다.\n");

    // 2. 동일성 검사 테스트
    if (equal(root1, root2)) {
        printf("두 트리는 동일합니다.\n");
    } else {
        printf("두 트리는 다릅니다.\n");
    }

    // 3. 트리가 달라지는 경우 테스트
    root2->lchild->data = 99; // 복사본의 데이터 변경
    if (equal(root1, root2)) {
        printf("두 트리는 동일합니다.\n");
    } else {
        printf("두 트리는 다릅니다. (데이터 변경 후)\n");
    }

    return 0;
}