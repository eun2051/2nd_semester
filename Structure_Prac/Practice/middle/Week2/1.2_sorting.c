#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
void sort (int list[], int n);
int main (void) {
    int i, j, n;
    int *A;
    double duration;
    clock_t start;

    int n_values[] = {
        100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
        2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
        10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,
        200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000
    };

    /* for (n = 0; n < MAX_SIZE; n += step) {
            for(i = 0; i < n; i++)
                B[i] = n - i;
            start = clock();
            sort(B, n);
            duration = ((double)(clock()- start()) / CLOCKS_PER_SEC;
            // is sorted 할거 하고...
            if (n == 100) step = 100;
            if (n == 1000) step = 1000;
            if (n == 10000) step = 10000;
            if (n == 100000) step = 100000;
    } 
    */
    int num_values = sizeof(n_values) / sizeof(n_values[0]);
    
    printf("   n       시간       정렬상태  \n");
    for (i = 0; i < num_values; i++) {
        n = n_values[i];
        A = (int *)malloc(sizeof(int) * n); //malloc
        if (A == NULL) {
            printf("메모리할당 실패\n");
            break;
        }
        for (j = 0; j < n; j++) //rev_sort
            A[j] = n - j;
        start = clock();
        sort(A, n);
        duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
        printf("%6d   %f       정렬됨\n", n, duration);
        free(A); //free malloc
    }
}

void sort (int list[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], temp);
    }
}