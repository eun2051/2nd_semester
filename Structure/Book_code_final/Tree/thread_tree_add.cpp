#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

struct thread_tree {
    short int           left_thread;
    struct thread_tree  *lchild;
    char                data;
    struct thread_tree  *rchild;
    short int           right_thread;   
};

// 한 노드의 inorder successor 발견
struct thread_tree *insucc(struct thread_tree *ptr)
{
    struct thread_tree *temp = ptr->rchild;

    if (!ptr->right_thread) {
        while (!temp->left_thread)
            temp = temp->lchild;
    }
    return temp;
}

// inorder traversal 중위 순환
// threaded binary tree를 inorder traversal
void tinorder(struct thread_tree *tree)
{
    struct thread_tree *temp = tree;
    for (;;) {
        temp = insucc(temp);
        if (temp == tree)
            break;
        printf("%5d", temp->data);
    }
}

// threaded binary tree에서 노드 추가
// 새로운 노드를 parent 노드의 right child로 추가
void insert_right(struct thread_tree *parent, struct thread_tree *child)
{
	struct thread_tree *temp;
	
	child->rchild = parent->rchild;
	child->right_thread = parent->right_thread;
	child->lchild = parent;
	child->left_thread = TRUE;
	
	parent->rchild = child;
	parent->right_thread = FALSE;
	if (!child->right_thread) {
		temp = insucc(child);
		temp->lchild = child;
	}
}

// 새로운 노드를 parent 노드의 left child로 추가
void insert_left(struct thread_tree *parent, struct thread_tree *child) 
{
	struct thread_tree *temp;
	child->lchild = parent->lchild;
	child->left_thread = parent->left_thread;
	child->rchild = parent;
	child->right_thread = TRUE;
	parent->lchild = child;
	parent->left_thread = FALSE;
	
	if (!child->left_thread) {
		temp = insucc(child);
		temp->rchild = child;
	}
}