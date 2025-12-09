#include <stdio.h>
#include <stdlib.h>

// 힙의 문제점을 해결하기 위한 이진 탐색 트리

struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};

// 이진 검색 트리 - 검색 연산
struct node *search(struct node *root, int key)
{
	if (!root) return NULL;
	if (key == root->data) return root;
	if (key < root->data)
		return search(root->lchild, key);
	return search(root->rchild, key);
}

//iterative search 반복적 검색
// key를 포함하고 있는 노드의 포인터를 반환
// 해당되는 노드가 없을 경우, return NULL
struct node *iterSearch(struct node *tree, int key)
{
	while (tree != NULL) {
		if (key == tree->data) return tree;
		if (key < tree->data)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return NULL;
}

// 이진 검색 트리 -> 노드 추가
// 추가할 키 값이 트리에 이미 존재하는지 확인
// 검색 알고리즘 수행 후, 알고리즘이 종료되는 곳에 새로운 노드 추가
struct node *modified_search(struct node *root, int key)
{
    for (struct node *ptr = root; ptr != NULL;) {
		if (ptr->data == key) //기존에 존재하는 키 입력 
			return NULL;
		if (key < ptr->data) {
			if (ptr->lchild == NULL)
                return ptr;
			else ptr = ptr->lchild;
		} else {
			if (ptr->rchild == NULL)
                return ptr;
			else ptr = ptr->rchild;
		}
	}
	return NULL;
}

// 노드 추가하는 알고리즘
void insert_node(struct node **root, int num)
{
	struct node *parent = modified_search(*root, num);
	
	if (parent || !(*root)) {
		struct node *ptr = (struct node *)malloc(sizeof(struct node));
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		
		if (*root) // parent 의 child node로 삽입
		{
			if (num < parent->data)
				parent->lchild = ptr;
			else
				parent->rchild = ptr;
		} else *root = ptr; //tree empty-> root로 등록
	}
}

// 이진 검색 트리 - 노드 삭제
// child가 하나밖에 없는 노드의 삭제 -> 삭제된 자리에 child node 위치
// child가 두개인 노드의 삭제 -> 왼쪽 서브 트리에서 가장 큰 노드나, 오른쪽 서브트리에서 가장 작은 노드를 삭제된 자리에 위치시킴
