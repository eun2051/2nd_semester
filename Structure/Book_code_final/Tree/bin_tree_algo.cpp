#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};
typedef struct node *Binarytree;

// 이진 트리의 복사
// 입력 이진 트리의 노드 구조와 동일한 새로운 이진 트리 생성하여 루트 노드의 주소 반환
Binarytree copy(struct node *original)
{
    struct node *temp;
    if (original)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        temp->lchild = copy(original->lchild);
        temp->rchild = copy(original->rchild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

//swap_tree()

// 이진 트리의 동일성 검사
int equal(struct node *first, struct node *second)
{
	return ((!first && !second) || (first && second && (first->data == second->data) && equal (first->lchild, second->lchild) && equal(first->rchild, second->rchild)));
}

// 노드 수 계산
int get_node_count(struct node *ptr)
{
	int count = 0;
	if (ptr != NULL)
		count = 1 + get_node_count(ptr->lchild) + get_node_count(ptr->rchild);
	return count;
}

// 단말 노드 수 계산
int get_leaf_count(struct node *ptr)
{
	int count = 0;
	
	if (ptr != NULL) {
		if (ptr->lchild == NULL && ptr->rchild == NULL)
			return 1;
		else count = get_leaf_count(ptr->lchild) + get_leaf_count(ptr->rchild);
	}
	return count;
}