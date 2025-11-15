/* 정렬 알고리즘의 구현 */
/* 모든 알고리즘은 실수 배열 이름과 배열의 원소 수를 인자로 받아서, 배열에
    저장된 정수들을 오름차순으로 정렬하도록 구현하자*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1000001
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    double key;
} element;

int is_sorted(element a[], int n);
void copy_array(element src[], element dest[], int n);
void print_array(int n, double times[]);
void mesure_timesort(int n, element *A, element *B, double time_array[]);
void selectionSort(element a[], int n);
void insert(element e, element a[], int i);
void insertionSort(element a[], int n);
void descending_sort(element a[], int n);
void quickSort(element a[], int left, int right);

int main(void)
{
    int i, n;
    double times[3];
    element *A = (element *)malloc(sizeof(element) * MAX_SIZE);
    element *B = (element *)malloc(sizeof(element) * MAX_SIZE);

    if (A == NULL || B == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        if (A) free(A);
        if (B) free(B);
        return 1;
    }
    srand((unsigned int)time(NULL));

    printf("정렬할 원소의 갯수 (n, 최대 %d)를 입력하세요 : ", MAX_SIZE - 1);
    if (scanf("%d", &n) != 1 || n < 1 || n >= MAX_SIZE) {
        fprintf(stderr, "부적절 n값\n");
        free(A);
        free(B);
        return 1;
    }

    for (i = 1; i <= n; i++) {
        A[i].key = ( (double)rand() / (RAND_MAX * 1.0) ) * 1000000000.0;
    }

    printf("12.1. 난수 생성 데이터의 정렬");
    mesure_timesort(n, A, B, times);
    print_array(n, times);
    selectionSort(A, n);
    printf("12.2. 정렬된 데이터의 정렬");
    mesure_timesort(n, A, B, times);
    print_array(n, times);
    printf("12.2.2 내림차순 정렬된 데이터의 정렬\n");
    descending_sort(A, n);
    mesure_timesort(n, A, B, times);
    print_array(n, times);

    free(A);
    free(B);
    return 0;
}

void mesure_timesort(int n, element *A, element *B, double time_array[])
{
    clock_t start, end;

    copy_array(A, B, n);
    start = clock();
    selectionSort(B, n); 
    end = clock();
    time_array[0] = (double)(end - start) / CLOCKS_PER_SEC;

    copy_array(A, B, n);
    start = clock();
    insertionSort(B, n); 
    end = clock();
    time_array[1] = (double)(end - start) / CLOCKS_PER_SEC;

    copy_array(A, B, n);
    start = clock();
    quickSort(B, 1, n); 
    end = clock();
    time_array[2] = (double)(end - start) / CLOCKS_PER_SEC;
}
void descending_sort(element a[], int n) {
    element tmp;
    for (int i = 1; i <= n / 2; i++) {
        SWAP(a[i], a[n - i + 1], tmp);
    }
}

int is_sorted(element a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i].key > a[i + 1].key) {
            return 0; 
        }
    }
    return 1;
}

void print_array(int n, double times[]) 
{
    printf(" 원소 수 : %d\n", n);
    printf(" selection sort time: %.6f\n", times[0]);
    printf(" insertion sort time: %.6f\n", times[1]);
    printf("       quick sort time: %.6f\n", times[2]);
}

void copy_array(element src[], element dest[], int n)
{
    for (int i = 1; i <= n; i++) {
        dest[i] = src[i];
    }
}

void selectionSort(element a[], int n)
{
    int i, j, min;
    element tmp;

    for (i = 1; i <= n - 1; i++) {
        min = i;
        for (j = i + 1; j <= n; j++)
            if (a[j].key < a[min].key)
                min = j;
        SWAP(a[i], a[min], tmp);
    }
}

void insert(element e, element a[], int i)
{
    a[0] = e;
    while (e.key < a[i].key)
    {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}
void insertionSort(element a[], int n)
{
    int j;
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1);
    }
}

void quickSort(element a[], int left, int right)
{
    int i , j;
    double pivot;
    element temp;
    
    if (left < right) {
        i = left;
        j = right + 1;
        pivot = a[left].key;
        
        do {
            do i++; while (i <= right && a[i].key < pivot);
            do j--; while (a[j].key > pivot);
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);
        SWAP(a[left], a[j], temp);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}