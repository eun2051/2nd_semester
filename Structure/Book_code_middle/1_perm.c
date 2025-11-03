#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

/* list[i] ~ list[n]까지의 원소로 구성된 모든 순열 출력
{a, b, c, d}의 경우 초기 호출 = perm(list, 0, 3) */
void perm(char *list, int i, int n)
{
    int j;
    char temp;
    if (i == n) { //단 하나의 순열만 존재, 그냥 출력
        for (j = 0; j <= n; j++)
            printf("%c", list[j]);
        printf("\n");
    } else { //하나 이상의 순열 존재, 재귀적으로 출력
        for (j = i; j <= n; j++)
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
    }
}

int main() {
    char data[] = "ABC"; 
    int n = strlen(data) - 1; 
    printf("--- 문자열 '%s'의 순열 ---\n", data);
    perm(data, 0, n);

    return 0;
}