#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void perm(char *list, int i, int n);

int main() {
    printf("2.3. 순열 원소 개수를 변화시키면서 실행 시간 관찰\n");
    int num, i;

    double duration_times[11];
    
    for (num = 0; num <= 10; num++) {
        clock_t start;
        char *A = NULL;

        if (num == 0) {
            printf("0\n");
            duration_times[0] = 0.0;
            continue;
        }

        A = (char *)malloc(num + 1);
        if (A == NULL) {
            printf("메모리 할당 실패\n");
            return 1;
        }
        
        for (i = 0; i < num; i++) {
            A[i] = (char)(i + '0');
        }
        A[num] = '\0';
        printf("\n");

        start = clock();
        perm(A, 0, num - 1);
        duration_times[num] = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        printf("\n");
        free(A);
    }

    printf("원소 갯수\t실행시간\n");
    for (int j = 1; j <= 10; j++) {
        printf("%d\t\t%f\n", j, duration_times[j - 1]);
    }
    return 0;
}

void perm(char *list, int i, int n) {
    int j, temp;
    if (i == n) {
        for (j = 0; j <= n; j++)
            printf("%c", list[j]);
        printf(" ");
    } else {
        for (j = i; j <= n; j++) {
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}