#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void sort (int list[], int n);
int is_sorted (int A[], int n);

int main (void) {
    int i;
    int A[MAX_SIZE];
    for (i = 0; i < MAX_SIZE; i++) //무작위 정수 생성
            A[i] = rand() % 1000 + 1;
            //n = 100000;
            //(rand() % n) + 1;
    for (i = 0; i < 100; i++)
        printf("%d ", A[i]);
    printf("\n");
    printf("......\n");
    printf("완료.\n");

    sort(A, MAX_SIZE); // sorting

    for (i = 0; i < 100; i++)
        printf("%d ", A[i]);
    printf("\n");
    printf("......\n");
    printf("완료.\n");

    if (is_sorted(A, MAX_SIZE) == 1)
        printf("정렬 완료!!!\n");
    else
        printf("오름차순 정렬 실패.\n");
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

int is_sorted (int list[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (list[i] > list[i + 1]) {
            return 0;
        }
    }
    return 1;
}