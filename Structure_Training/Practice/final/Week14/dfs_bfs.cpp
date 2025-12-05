#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct node *nodePointer;
struct node {
    int vertex;
    struct node *link;
};

nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];
nodePointer front = NULL, rear = NULL;

void addq(int v) {
    nodePointer temp = (nodePointer)malloc(sizeof(struct node));
    temp->vertex = v;
    temp->link = NULL;

    if (front == NULL) {
        front = temp;
    } else {
        rear->link = temp;
    }
    rear = temp;
}

int deleteq() {
    if (front == NULL) return -1;

    nodePointer temp = front;
    int item = temp->vertex;
    front = front->link;
    free(temp);
    
    if (front == NULL) rear = NULL;

    return item;
}

void dfs(int v)
{
    nodePointer w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex])
            dfs(w->vertex);
    }
}

void bfs(int v)
{
    nodePointer w;
    front = rear = NULL;
    printf("%5d", v);
    visited[v] = TRUE;
    addq(v);
    while(front) {
        v = deleteq();
        for (w = graph[v]; w; w = w->link) {
            if (!visited[w->vertex]) {
                printf("%5d", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
        }
    }
}