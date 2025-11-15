// 정렬된 리스트로 삽입하는 함수
#include <stdio.h>

typedef struct {
    int key;
} element;

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