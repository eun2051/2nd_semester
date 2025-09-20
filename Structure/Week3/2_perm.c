#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void perm(char *list, int i, int n);

int main() {
    int num, count, i, j, k;
    double duration;
    double duration_times[11];
    clock_t start;
    char *A = NULL;
    char buffer[10];
    char *B = NULL;
    char *C = NULL;

    printf("2.1. 순열 알고리즘 호출\n");
    for(i = 0; i < 4; i++) {
        printf("제시 문자열 : ");
        scanf("%s", buffer);

        A = (char *)malloc(strlen(buffer) + 1);
        if (A == NULL) {
            printf("메모리 할당 실패\n");
            return -1;
        }
        strcpy(A, buffer);
        perm(A, 0, strlen(A) - 1);
        printf("\n");
        free(A);
    }

    printf("2.2. 1부터 n사이의 숫자들을 이용한 순열\n");
    while (1) {
        printf("입력 : ");
        scanf("%d", &num);

        if (num == -1) {
            printf("종료\n");
            break;
        }
        if (num < 0 || num > 32) {
            printf("입력 범위(1~32)를 벗어났습니다.\n");
            continue;
        } else {
            B = (char *)malloc(num + 1);
            if (B == NULL) {
                printf("메모리 할당 실패\n");
                return 1;
            }
            for (int j = 0; j < num; j++)
                B[j] = (char)(j + '0');
            B[num] = '\0';
            printf("순열 :\n");
            start = clock();
            perm(B, 0, num - 1);
            duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
            printf("\n");
            printf("실행시간 : %f\n", duration);
            free(B);
        }
    }

    printf("2.3. 순열 원소 개수를 변화시키면서 실행 시간 관찰\n");
    for (count = 0; count <= 10; count++) {
        if (count == 0) {
            printf("0\n");
            duration_times[0] = 0.0;
            continue;
        }

        C = (char *)malloc(num + 1);
        if (C == NULL) {
            printf("메모리 할당 실패\n");
            return 1;
        }
        
        for (k = 0; k < count; k++) {
            C[k] = (char)(k + '0');
        }
        C[count] = '\0';
        printf("\n");

        int repeat_count = 10;
        start = clock();
        for (int k = 0; k < repeat_count; k++) {
            perm(C, 0, count - 1);
        }
        duration_times[count] = ((double)(clock() - start)) / CLOCKS_PER_SEC / repeat_count;
        printf("\n");
        free(C);
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
        printf("\t");
    } else {
        for (j = i; j <= n; j++) {
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}