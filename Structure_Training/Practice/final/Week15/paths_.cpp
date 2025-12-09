#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 50
#define FALSE 0
#define TRUE 1

/* 최저 비용 간선의 선택 */
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

/* 하나의 출발점에서 최단 경로*/
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
        found[u] = TRUE;
        for (w = 0; w < n; w++) {
            if (!found[w]) {
                if (distance[u] + cost[u][w] < distance[w])
                    distance[w] = distance[u] + cost[u][w];
            }
        }
    }
}

/* 모든 쌍의 최단 경로를 구하는 함수 */
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
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}
