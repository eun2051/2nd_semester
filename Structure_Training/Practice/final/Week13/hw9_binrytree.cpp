#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *treePointer;
struct node {
    int key;
    double value;
    struct node *lchild;
    struct node *rchild;
};

treePointer modified_search(treePointer tree, int key);
void        inorder(treePointer ptr);
void        insert(treePointer *node, int k, double theItem);
treePointer create_node(int key, double value);
treePointer search(treePointer tree, int key, int *count);
treePointer make_bst(int n);
int         count_node(treePointer ptr);
int         count_depth(treePointer ptr);
int         count_leaf(treePointer ptr);
treePointer make_bst(int n);

int         print_count = 0;
int         total_node = 0;
void        inorder_limited(treePointer ptr);

int main()
{
    treePointer root = NULL;
    int key;
    srand((unsigned int)time(NULL));

    printf("9.1. 12개의 (key, value)쌍을 생성하여 이진 탐색 트리 생성\n");
    int inputs[] = {10, 6, 15, 8, 18, 12, 3, 14, 9, 20, 5, 2};
    int input_size = sizeof(inputs) / sizeof(inputs[0]);

    for(int i=0; i<input_size; i++) {
        insert(&root, inputs[i], 1.0 / inputs[i]);
    }
    printf("생성 완료\n\n");

    printf("9.2. 생성된 이진 검색 트리에서 key값을 활용한 검색\n");
    while (1) {
        printf("찾고자 하는 key 값을 입력하세요. : ");
        if (scanf("%d", &key) != 1) {
            while(getchar() != '\n');
            continue;
        }
        if (key == -1) break;

        int search_count = 0;
        treePointer result = search(root, key, &search_count);
        if (result) {
            printf("count : %d, key: %d의 value: %f\n", search_count, result->key, result->value);
        } else {
            printf("key: %d 노드가 없습니다.\n", key);
        }
    }
    printf("\n\n");
    printf("9.3. n개의 노드를 가진 이진트리 생성시간 및 노드 수, 높이(깊이), 단말 노드 수 관찰\n");
    int n;
    while(1) {
        printf("n개의 노드를 가진 이진검색 트리 생성 (n) : ");
        if (scanf("%d", &n) != 1) {
             while(getchar() != '\n'); 
             continue;
        }
        if (n == -1) break;

        clock_t start = clock();
        treePointer newRoot = make_bst(n);
        clock_t end = clock();

        printf("이진검색트리 B :\n");
        printf("(      key,     value)\n");
        
        print_count = 0;
        total_node = n;
        inorder_limited(newRoot);

        double duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("이진검색트리 B의 생성시간: %.3f   \n", duration);
        printf("이진검색트리 B의 노드 수 : %d\n", count_node(newRoot));
        printf("이진검색트리 B의 높이(깊이) : %d\n", count_depth(newRoot));
        printf("이진검색트리 B의 단말노드 수 : %d\n\n", count_leaf(newRoot));
    }

    return 0;
}

treePointer modified_search(treePointer tree, int k) {
    treePointer temp = NULL;
    while (tree) {
        if (k == tree->key) return NULL;
        temp = tree;
        if (k < tree->key)
            tree = tree->lchild;
        else
            tree = tree->rchild;
    }
    return temp;
}

treePointer search(treePointer tree, int key, int *count)
{
    while (tree)
    {
        (*count)++;
        if (key == tree->key) return tree;
        if (key < tree->key)
            tree = tree->lchild;
        else
            tree = tree->rchild;
    }
    return NULL;
}

void insert(treePointer *node, int k, double theItem)
{
    treePointer parent = modified_search(*node, k);
    if (parent == NULL && (*node) != NULL) {
        return; 
    }
    treePointer ptr = create_node(k, theItem);
    if (*node == NULL) {
        *node = ptr; 
    } else {
        if (k < parent->key) 
            parent->lchild = ptr;
        else 
            parent->rchild = ptr;
    }
}

treePointer create_node(int key, double value)
{
    treePointer newNode = (treePointer)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

void inorder(treePointer ptr)
{
    if (ptr) {
        inorder(ptr->lchild);
        printf("key: %d의 value: %.2f\n", ptr->key, ptr->value);
        inorder(ptr->rchild);
    }
}

treePointer make_bst(int n) {
    treePointer tree = NULL;
    int count = 0;
    int check = 0;
    while (count < n) {
        double ratio = (double)rand() / RAND_MAX;
        int key = (int)(ratio * 100000000);
        if (key <= 0) key = 1;
        if (search(tree, key, &check) == NULL) {
            double value = 1.0 / key;
            insert(&tree, key, value);
            count++;
        }
    }
    return tree;
}

int count_node(treePointer ptr) {
    if (!ptr) return 0;
    return 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
}

int count_depth(treePointer ptr) {
    if (!ptr) return 0;
    int l = count_depth(ptr->lchild);
    int r = count_depth(ptr->rchild);
    if (l > r) {
        return l + 1;
    } else {
        return r + 1;
    }
}

int count_leaf(treePointer ptr) {
    if (!ptr) return 0;
    if (!ptr->lchild && !ptr->rchild) return 1;
    return count_leaf(ptr->lchild) + count_leaf(ptr->rchild);
}

void inorder_limited(treePointer ptr)
{
    if (ptr) {
        inorder_limited(ptr->lchild);
        
        print_count++;
        if (print_count <= 2 || print_count > total_node - 3) {
            printf("(%8d, %f)\n", ptr->key, ptr->value);
        }
        else if (print_count == 3) {
            printf("......\n");
        }

        inorder_limited(ptr->rchild);
    }
}