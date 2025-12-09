#include <stdio.h>
#include <stdlib.h>

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