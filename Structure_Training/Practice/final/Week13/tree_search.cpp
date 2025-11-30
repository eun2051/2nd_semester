#include <stdio.h>
#include <stdlib.h>

typedef int iType;
typedef struct {
    int key;
    iType item;
} element;

typedef struct treeNode {
    element data;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
} *treePointer;

/* <이원 탐색 트리의 순환적 탐색> */
// key 값이 k인 노드에 대한 포인터를 반환
// 그런 노드가 없는 경우 NULL 반환
element *search(treePointer tree, int k)
{
    if (!tree) return NULL;
    if (k == tree->data.key) return &(tree->data);
    if (k < tree->data.key)
        return search(tree->leftChild, k);
    return search(tree->rightChild, k);
}

/* <이원 탐색 트리의 반복적 탐색*/
// key 값이 k인 노드에 대한 포인터 반환
// 그런 노드가 없는 경우 NULL 반환
element *iterSearch(treePointer tree, int k)
{
    while (tree)
    {
        if (k == tree->data.key) return &(tree->data);
        if (k < tree->data.key)
            tree = tree->leftChild;
        else
            tree = tree->rightChild;
    }
    return NULL;
}

treePointer modifiedSearch(treePointer tree, int k) {
    treePointer temp = NULL; // 부모 노드를 저장할 변수
    while (tree) {
        if (k == tree->data.key) return NULL; // [중요] 키가 이미 존재함
        
        temp = tree; // 현재 노드를 부모로 기억해둠
        if (k < tree->data.key)
            tree = tree->leftChild;
        else
            tree = tree->rightChild;
    }
    return temp; // 마지막으로 방문한 노드(새 노드의 부모가 될 노드) 반환
}

/* <이원 탐색 트리에 사전 쌍의 삽입> */
// 트리 내 노드가 k를 가리키고 있으면 아무 일도 하지 않음
// 그렇지 않은 경우, data = (k, theItem)인 새 노드를 삽입
void insert(treePointer *node, int k, iType theItem)
{
    treePointer ptr, temp = modifiedSearch(*node, k);
    if (temp == NULL && (*node) != NULL) {
        return; // 이미 존재하거나 트리가 비어있음
    }
    ptr = (treePointer)malloc(sizeof(struct treeNode));
    ptr->data.key = k;
    ptr->data.item = theItem;
    ptr->leftChild = ptr->rightChild = NULL;
    if (*node == NULL) { 
        // 트리가 비어있는 경우, 새 노드가 루트가 됩니다.
        *node = ptr; 
    } else {
        // 트리가 비어있지 않은 경우, temp(부모)의 자식으로 연결합니다.
        if (k < temp->data.key) 
            temp->leftChild = ptr;
        else 
            temp->rightChild = ptr;
    }
}