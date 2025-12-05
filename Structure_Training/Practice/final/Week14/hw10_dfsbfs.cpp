#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
struct node {
    int data;
    struct node *next;
};
struct node **graph;
int visited[MAX_VERTICES];
int queue[MAX_VERTICES];
int front = 0, rear = 0;

void insert_front(int i, int value);
void add_edge(int i, int value);
void print_graph(int n);
void find_maxdegree(int n);
void init_visited(int n);
void dfs(int v);
void bfs(int v);
void dfs_tree(int v);
void bfs_tree(int v);
void addq(int v);
int deleteq();

int main()
{
    int n, vi, vj;
    while (1) {
        printf("10.1. 인접 리스트 형태의 무방향성 그래프 생성\n");
        printf("노드 개수(n): ");
        scanf("%d", &n);
        if (n == -1) break;
        
        graph = (struct node **)calloc(n, sizeof(struct node *));

        while (1) {
            printf("  에지 정보(vi vj) : ");
            scanf("%d %d", &vi, &vj);
            if (vi == -1 && vj == -1) {
                break;
            }
            if (vi >= 0 && vi < n && vj >= 0 && vj < n) {
                add_edge(vi, vj);
            }
        }
        print_graph(n);
        find_maxdegree(n);

        printf("10.2. 탐색 알고리즘(DFS, BFS)\n");
        printf("  깊이 우선 탐색 (DFS)\n");
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                printf("  시작노드 %d :   ", i);
                init_visited(n);
                dfs(i);
                printf("\n");
            }
        }
        printf("  너비 우선 탐색 (BFS)\n");
        for (int i = 0; i < n; i++) {
            if (i % 2 != 0) {
                printf("  시작노드 %d :   ", i);
                init_visited(n);
                bfs(i);
                printf("\n");
            }
        }

        printf("10.3. 신장트리 알고리즘(DFS, BFS 기반)\n");
        printf("  DFS 신장트리\n");
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                printf("  시작노드 %d : ", i);
                init_visited(n);
                dfs_tree(i);
                printf("\n");
            }
        }
        printf("  BFS 신장트리\n");
        for (int i = 0; i < n; i++) {
            if (i % 2 != 0) {
                printf("  시작노드 %d : ", i);
                init_visited(n);
                bfs_tree(i);
                printf("\n");
            }
        }
    }
    
    return 0;
}

void insert_front(int i, int value)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = graph[i];
    graph[i] = newNode;
}

void add_edge(int i, int value)
{
    insert_front(i, value);
    insert_front(value, i);
}

void print_graph(int n)
{
    printf("\n인접 리스트를 이용하여 구성한 그래프\n");
    for (int i = 0; i < n; i++) {
        printf("  [%d]: ", i);
        struct node *curr = graph[i];
        while(curr != NULL) {
            printf("%d -> ", curr->data);
            curr = curr->next;
        }
        printf("end\n");
    }
}

void find_maxdegree(int n) {
    int max_degree = -1;
    int max_node = -1;

    for (int i = 0; i < n; i++) {
        int count = 0;
        struct node *curr = graph[i];
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }
        if (count > max_degree) {
            max_degree = count;
            max_node = i;
        }
    }
    printf("\n degree가 가장 큰 노드와 degree 값 : 노드 %d, degree %d\n", max_node, max_degree);
    printf(" 노드 %d와 연결된 노드들 :  ", max_node);
    
    struct node *curr = graph[max_node];
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("end\n");
}

void addq(int v)
{
    queue[rear++] = v;
}

int deleteq()
{
    return queue[front++];
}

void init_visited(int n)
{
    for(int i=0; i<n; i++)
        visited[i] = FALSE;
    front = rear = 0;
}

void dfs(int v)
{
    struct node *w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph[v]; w; w = w->next) {
        if (!visited[w->data])
            dfs(w->data);
    }
}

void bfs(int v)
{
    struct node *w;
    front = rear = 0;
    printf("%5d", v);
    visited[v] = TRUE;
    addq(v);
    while(front < rear) {
        v = deleteq();
        for (w = graph[v]; w; w = w->next) {
            if (!visited[w->data]) {
                printf("%5d", w->data);
                addq(w->data);
                visited[w->data] = TRUE;
            }
        }
    }
}

void dfs_tree(int v)
{
    struct node *w;
    visited[v] = TRUE;
    for (w = graph[v]; w; w = w->next) {
        if (!visited[w->data]) {
            printf(" (%d, %d) ", v, w->data);
            dfs_tree(w->data);
        }
    }
}

void bfs_tree(int v)
{
    struct node *w;
    front = rear = 0;
    visited[v] = TRUE;
    addq(v);
    while(front < rear) {
        int curr = deleteq();
        for (w = graph[curr]; w; w = w->next) {
            if (!visited[w->data]) {
                printf(" (%d, %d) ", curr, w->data);
                visited[w->data] = TRUE;
                addq(w->data);
            }
        }
    }
}