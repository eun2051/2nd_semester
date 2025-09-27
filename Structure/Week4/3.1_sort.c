//정적배열을 동적배열로 만드는 것이 실습
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float coef;
    int expon;
} polynomial;

// 1. polynomical 구조체 배열을 동적으로 생성 (처음엔 10개의 항을 갖도록)
polynomial *A, *B, *D;

// 배열에 항들이 지수의 내림차순으로 저장
// 제일 마지막 항은 다항식의 끝 표시 -> 지수를 -1 지정

// <다항식 생성방법>
// 1) 각 항읙 계수와 지수를 입력받아 저장
// 2) 무작위로 계수를 생성하여 저장
// 각 항은 지수의 내림차순으로 정렬되어야함
// if 항 수 > 10 , realloc -> 배열 크기 증가
int main() {
    int capacity = 10;
    int count = 0;
    A = (polynomial *)malloc(capacity * sizeof(polynomial));
    if (A == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    printf("3.1. 다항식 생성\n");
    while (1) {
        float coef;
        int expon;
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &coef, &expon);
        if (expon == -1) break;
        if (count >= capacity) {
            capacity *= 2;
            A = (polynomial *)realloc(A, capacity * sizeof(polynomial));
            if (A == NULL) {
                printf("메모리 재할당 실패\n");
                return 1;
            }
        }
        A[count].coef = coef;
        A[count].expon = expon;
        count++;
    }
    printf("다항식 A(x)\n");
    printf("\tcoef\texpon\n");
    for (int i = 0; i < count; i++) {
        printf("\t%.2f\t%d\n", A[i].coef, A[i].expon);
    }
    free(A);
    printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &coef, &expon);
        if (expon == -1) break;
        if (count >= capacity) {
            capacity *= 2;
            A = (polynomial *)realloc(A, capacity * sizeof(polynomial));
            if (A == NULL) {
                printf("메모리 재할당 실패\n");
                return 1;
            }
        }
        A[count].coef = coef;
        A[count].expon = expon;
        count++;
    }
    printf("다항식 B(x)\n");
    printf("\tcoef\texpon\n");
    for (int i = 0; i < count; i++) {
        printf("\t%.2f\t%d\n", A[i].coef, A[i].expon);
    }
    free(B);
}