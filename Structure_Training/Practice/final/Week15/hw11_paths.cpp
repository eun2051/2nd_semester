#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 50
#define MAX_PRINT 99999
#define FALSE 0
#define TRUE 1

void q1_print_graph(int G[][MAX_VERTICES], int n);
void q2_print_distance(int distance[], int n);
void q3_print_all_distance(int distance[][MAX_VERTICES], int n);
int choose(int distance[], int n, short int found[]);
void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]);
void allCosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n);

int main()
{
    int G[MAX_VERTICES][MAX_VERTICES];
    int all_distance[MAX_VERTICES][MAX_VERTICES];
    int n = 0;
    int s_vertex, f_vertex, w;
    int distance[MAX_VERTICES];
    short int found[MAX_VERTICES];


    while (1) {

        printf("11.1. 인접 행렬 형태의 방향성 그래프 생성\n");
        printf(" 노드 수 (n) : ");
        scanf("%d", &n);
    
        if (n == -1)
            break;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    G[i][j] = 0;
                else  
                    G[i][j] = INT_MAX;
            }
        }

        while (1) {
            printf(" 에지 정보 (from to weight) : ");
            scanf("%d %d %d", &s_vertex, &f_vertex, &w);

            if (s_vertex == -1 || f_vertex == -1 || w == -1 ) {
                break;
            }
            G[s_vertex][f_vertex] = w;
        }
        q1_print_graph(G, n);

        printf("\n11.2. 최단 경로 (단일 출발점)\n");
        int v;
        while (1) {
            printf(" 시작 노드 (v) : ");
            scanf("%d", &v);

            if (v == -1) {
                break;
            }
            if (v < 0 || v >= n) {
                printf(" [오류] 0부터 %d 사이의 노드를 입력하세요.\n", n - 1);
                continue;
            }
            shortestPath(v, G, distance, n, found);
            q2_print_distance(distance, n);
        }
        printf("\n11.3. 최단 경로 (모든 경로)\n");
        allCosts(G, all_distance, n);
        q3_print_all_distance(all_distance, n);
    }
    return 0;
}


int choose(int distance[], int n, short int found[])
{  
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[])
{
    int i, u, w;
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = cost[v][i];
    }
    found[v] = TRUE;
    distance[v] = 0;
    for (i = 0; i < n - 2; i++) {
        u = choose(distance, n, found);
        if (u == -1)
            break;
        found[u] = TRUE;
        for (w = 0; w < n; w++) {
            if (!found[w]) {
                if (distance[u] != INT_MAX && cost[u][w] != INT_MAX) {
                    if (distance[u] + cost[u][w] < distance[w])
                        distance[w] = distance[u] + cost[u][w];
                }
            }
        }
    }
}

void allCosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n)
{
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            distance[i][j] = cost[i][j];
        }
    }
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX) {
                    if (distance[i][k] + distance[k][j] < distance[i][j])
                        distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

void q1_print_graph(int G[][MAX_VERTICES], int n)
{
    int i, j;

    printf("\n 인접 행렬을 이용한 그래프의 구성 :\n");
    printf("     ");
    for (j = 0; j < n; j++) {
        printf("    [%2d]", j);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("    [%2d]", i);
        for (j = 0; j < n; j++) {
            if (G[i][j] == INT_MAX) {
                printf(" %6d", MAX_PRINT);
            } else {
                printf(" %6d", G[i][j]);
            }
        }
        printf("\n");
    }
}

void q2_print_distance(int distance[], int n) {
    printf(" Distance : ");
    for (int i = 0; i < n; i++) {
        if (distance[i] == INT_MAX) {
            printf(" %4d", MAX_PRINT);
        } else {
            printf(" %4d", distance[i]);
        }
    }
    printf("\n");
}

void q3_print_all_distance(int distance[][MAX_VERTICES], int n)
{
    int i, j;

    printf("  All Path Distance :\n");
    printf("     ");
    for (j = 0; j < n; j++) {
        printf("    [%2d]", j);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("    [%2d]", i);
        for (j = 0; j < n; j++) {
            if (distance[i][j] == INT_MAX) {
                printf(" %6d", MAX_PRINT);
            } else {
                printf(" %6d", distance[i][j]);
            }
        }
        printf("\n");
    }
}