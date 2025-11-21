#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
};

struct node *make_tree_by_code();
struct node* create_node(int data);
struct node* copy(struct node *original);
struct node* make_random_tree(int n);
int equal(struct node *first, struct node *second);
void swap(struct node *ptr);
void inorder(struct node *ptr);
void preorder(struct node *ptr);
void postorder(struct node *ptr);

int main() {
    int n;

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

    printf("\n8.2.1. 트리 복사 (B = copy(A))");
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

    printf("\n8.2.3. 트리 동질성 검사 (equal(A, B))\n");
    if (equal(A, B))
        printf("equal(A, B) : TRUE\n");
    else
        printf("equal(A, B) : FALSE\n");

    printf("\n8.2.4. 트리 swap (C = swap(A))\n");
    struct node *C = copy(A);
    swap(C);

    printf("8.2.5. 트리 순회 (C)\n");
    printf("inorder(C) : ");
    inorder(C);
    printf("\n");
    printf("preorder(C) : ");
    preorder(C);
    printf("\n");
    printf("postorder(C) : ");
    postorder(C);
    printf("\n");
    
    printf("\n8.3.1. 랜덤 트리 자동 생성 (D)\n");
    printf("Input n : ");
    scanf("%d", &n);
    srand(time(NULL));
    struct node *D = make_random_tree(n);

    printf("8.3.2. 트리 순회 (D)\n");
    printf("inorder(D) : ");
    inorder(D);
    printf("\n");
    printf("preorder(D) : ");
    preorder(D);
    printf("\n");
    printf("postorder(D) : ");
    postorder(D);
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

// 트리 복사 함수
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

// 좌우 대칭 함수
void swap(struct node *ptr) {
    if (ptr) {
        struct node *temp = ptr->lchild;
        ptr->lchild = ptr->rchild;
        ptr->rchild = temp;
        
        swap(ptr->lchild);
        swap(ptr->rchild);
    }
}

//동일성 검사
int equal(struct node *first, struct node *second)
{
    return((!first && !second) || (first && second &&
        (first->data == second->data) &&
        equal(first->lchild, second->lchild) &&
        equal(first->rchild, second->rchild)));
}

//랜덤 트리 생성 함수
struct node* make_random_tree(int n)
{
    if (n < 1)
        return NULL;
    struct node *root = create_node(1);
    for (int i = 2; i <= n; i++) {
        struct node *current = root;
        while (1) {
            int direction = rand() % 2;

            if (direction == 0) {
                if (current->lchild == NULL) {
                    current->lchild = create_node(i);
                    break;
                } else {
                    current = current->lchild;
                }
            } else {
                if (current->rchild == NULL) {
                    current->rchild = create_node(i);
                    break;
                } else {
                    current = current->rchild;
                }
            }
        }
    }
    return root;
}
