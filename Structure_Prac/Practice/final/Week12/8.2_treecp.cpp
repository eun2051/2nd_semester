#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};

struct node *make_tree_by_code();
struct node* create_node(int data);
struct node *copy(struct node *original);
void inorder(struct node *ptr);
void preorder(struct node *ptr);
void postorder(struct node *ptr);

int main()
{
    printf("\n8.2.1. 트리 복사 (B = copy(A))\n");
    struct node *A = make_tree_by_code();
    struct node *B = copy(A);
    printf("\n8.2.2. 트리 순회(B)\n");
    printf("inorder(B) : ");
    inorder(B);
    printf("\n");
    printf("preorder(B) : ");
    preorder(B);
    printf("\n");
    printf("postorder(B) : ");
    postorder(B);
    printf("\n");
}

struct node *copy(struct node *original)
{
    struct node *temp;
    if (original) {
        temp = (struct node *)malloc(sizeof(struct node));
        temp->lchild = copy(original->lchild);
        temp->rchild = copy(original->rchild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
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