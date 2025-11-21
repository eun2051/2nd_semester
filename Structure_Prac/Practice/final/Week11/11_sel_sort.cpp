#include <stdio.h>
#include <math.h>
#define MAX_SIZE 101
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void sort(int list[], int n);

void main(void)
{
    int i, n;
    int list[MAX_SIZE];

    printf("만들 수의 갯수를 입력하세요 : ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, "Improper value\n");
        exit(0);
    }
    for (i = 0; i < n; i++) {
        list[i] = rand() % 1000;
        printf("%d ", list[i]);
    }
    sort(list, n);
    printf("\n Sorted array : \n");
    for (i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void sort(int list[], int n)
{
    int i, j, min, tmp;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], tmp);
    }
}