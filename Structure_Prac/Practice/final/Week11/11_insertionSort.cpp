// 삽입 정렬
// a[1: n]을 비감소 키 순서대로 정렬
#include <stdio.h>

typedef struct {
    int key;
} element;

void insertionSort(element a[], int n)
{
    int j;
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1);
    }
}

void insert(element e, element a[], int i)
{
    a[0] = e;
    while (e. key < a[i].key)
    {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}