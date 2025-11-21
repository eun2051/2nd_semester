#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void perm(char *list, int i, int n);

int main(){
    int num, i = 0;
    double duration;
    clock_t start;
    char *A = NULL;

    printf("2.2. 1부터 n사이의 숫자들을 이용한 순열\n");
    while (1) {
        printf("입력 : ");
        scanf("%d", &num);

        if (num == -1) {
            printf("종료\n");
            return 0;
        }
        if (num < 0 || num > 32) {
            printf("입력 범위(1~32)를 벗어났습니다.\n");
            continue;
        } else {
            A = (char *)malloc(num + 1);
            if (A == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            for (int i = 0; i < num; i++)
                A[i] = (char)(i + '0');
            A[num] = '\0';
            printf("순열 :\n");
            start = clock();
            perm(A, 0, num - 1);
            duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("실행시간 : %f\n", duration);
            free(A);
        }
    }
    return 0;
}

void perm(char *list, int i, int n) {
    int j, temp;
    if (i == n) {
        for (j = 0; j <= n; j++)
            printf("%c", list[j]);
        printf("\t");
    } else {
        for (j = i; j <= n; j++) {
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}