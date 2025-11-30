#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};

struct node *make_tree_by_code();
struct node* create_node(int data);
void inorder(struct node *ptr);
void preorder(struct node *ptr);
void postorder(struct node *ptr);

int main() {
    printf("8.1.1. 트리 구성 (A = make_tree_by_code())\n");
    struct node *A = make_tree_by_code();
    printf("8.1.2. 트리 순회 (A)\n");
    printf("inorder(A) : ");
    inorder(A);
    printf("\n");
    printf("preorder(A) : ");
    preorder(A);
    printf("\n");
    printf("postorder(A) : ");
    postorder(A);
    printf("\n");
    
    return 0;
}

//트리 생성 함수
struct node *make_tree_by_code()
{
    struct node *root = create_node(5);
    struct node *n2 = create_node(3);
    struct node *n3 = create_node(8);
    struct node *n4 = create_node(1);
    struct node *n5 = create_node(4);

    root->lchild = n2;
    root->rchild = n3;
    
    n2->lchild = n4;
    n2->rchild = n5;

    return root;
}

struct node* create_node(int data)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

// 중위 순회 LVR
void inorder(struct node *ptr)
{
    if (ptr) {
        inorder(ptr->lchild);
        printf("%d ", ptr->data);
        inorder(ptr->rchild);
    }
}

// 전위 순회 VLR
void preorder(struct node *ptr)
{
    if (ptr) {
        printf("%d ", ptr->data);
        preorder(ptr->lchild);
        preorder(ptr->rchild);
    }
}

// 후위 순회 LRV
void postorder(struct node *ptr)
{
    if (ptr) {
        postorder(ptr->lchild);
        postorder(ptr->rchild);;
        printf("%d ", ptr->data);
    }
}
