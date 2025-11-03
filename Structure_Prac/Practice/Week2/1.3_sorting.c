#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
void sort (int list[], int n);
int is_sorted (int list[], int n);
int binsearch(int list[], int searchnum, int left, int right);

int main (void) {
    int i, search_val, counter_val;
    int A[MAX_SIZE];

    for (i = 0; i < MAX_SIZE; i++) //무작위 정수 생성
            A[i] = rand() % 1000;
    sort(A, MAX_SIZE);
    
    while (1) { // 무한 루프 시작
        printf("검색 데이터 ( 1 ~ 100000 ): ");
        scanf("%d", &search_val);

        if (search_val == -1) {
            printf("검색 종료.\n");
            break;
        }
        counter_val = binsearch(A, search_val, 0, MAX_SIZE - 1);
        
        if (counter_val != -1) {
            printf("검색 데이터 : %6d, Counter : %d\n", search_val,counter_val);
        } else {
            printf("검색 데이터 %d는 배열에 없습니다.\n", search_val);
        }
    }
    return 0;
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

int binsearch(int list[], int searchnum, int left, int right) {
    //
    int middle;
    int counter = 0;
    while (left <= right) {
        middle = (left + right) / 2;
        switch (COMPARE(list[middle], searchnum)) {
            case -1 : 
                left = middle + 1;
                break;
            case 0 : return counter;
            //return counter + 1 이 맞는거임
            //case 0 > 성공했기 때문
            case 1 : right = middle - 1;
        }
        counter++;
    }
    return -1;
}