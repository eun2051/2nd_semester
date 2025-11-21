#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void perm(char *list, int i, int n);

int main() {
    char *A;
    char buffer[10];
    int i = 0;
    printf("2.1. 순열 알고리즘 호출\n");
    while (i < 4) {
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
        i++;
    }
    free(A);
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