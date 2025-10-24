#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
void sort(int [], int); //selection sort
void main(void)
{
	int i, n, list[MAX_SIZE];
	printf("만들어질 수의 수를 입력하시오 : ");
	scanf("%d", &n);
	if (n < 1 || n > MAX_SIZE) {
	//error 처리
		fprintf(stderr, "잘못된 n 범위\n");
		exit(1);
	}
	for (i = 0; i < n; i++) { 
	//n개의 정수를 랜덤하게 생성
		list[i] = rand() % 1000;
		printf("%d", list[i]);
	}
	sort(list, n);
	//sort 함수 호출, 인자는 배열과 정수의 개수
	printf("\n정렬된 배열: \n");
	for (i = 0; i < n; i++)
	//정렬된 정수를 출력
		printf("%d ", list[i]);
	printf("\n");
}

//list[i] ~ list[n-1]까지 정렬
void sort(int list[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n-1; i++)
	{
		min = i; //최소값이 i에 있다고 일단 가정
		for (j = i+1; j < n; j++)
		//i 위치 다음의 모든 대상에 대해
			if (list[j] < list[min])
			//더 작은 것이 있으면?
				min = j; //최소값을 그 대상으로 바꾼다
		SWAP(list[i], list[min], temp);
		// 최소값과 i의 내용을 교체
	}
}