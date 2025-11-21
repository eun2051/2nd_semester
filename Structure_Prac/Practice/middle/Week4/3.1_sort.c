//정적배열을 동적배열로 만드는 것이 실습
// 1. polynomical 구조체 배열을 동적으로 생성 (처음엔 10개의 항을 갖도록)
// 배열에 항들이 지수의 내림차순으로 저장
// 제일 마지막 항은 다항식의 끝 표시 -> 지수를 -1 지정
// <다항식 생성방법>
// 1) 각 항읙 계수와 지수를 입력받아 저장
// 2) 무작위로 계수를 생성하여 저장
// 각 항은 지수의 내림차순으로 정렬되어야함
// if 항 수 > 10 , realloc -> 배열 크기 증가
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memmove 함수 사용을 위한 헤더

#define INITIAL_SIZE 10

typedef struct polynomial {
    float coef;
    int expon;
} polynomial;

polynomial* create_polynomial_manual(const char* poly_name);
void print_polynomial(polynomial* poly);

int main() {
    printf("3.1. 다항식 생성\n");
    polynomial* A = create_polynomial_manual("A(x)");
    printf("다항식 A(x)\n");
    print_polynomial(A);
    free(A);

    printf("\n");

    polynomial* B = create_polynomial_manual("B(x)");
    printf("다항식 B(x)\n");
    print_polynomial(B);
    free(B);
    
    return 0;
}

// 다항식을 사용자로부터 입력받아 동적으로 생성하는 함수
polynomial* create_polynomial_manual(const char* poly_name) {
    int current_size = 0;
    int current_capacity = INITIAL_SIZE;
    
    // 10개의 항을 가질 수 있는 동적 배열 생성
    polynomial* poly = (polynomial*)malloc(sizeof(polynomial) * current_capacity);
    if (!poly) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    
    float coef;
    int expon;
    
    while (1) {
        printf("%s의 항을 입력하세요. (coef expon) : ", poly_name);
        
        // 올바른 입력이 들어오지 않으면 다시 시도
        if (scanf("%f %d", &coef, &expon) != 2) {
            while (getchar() != '\n');
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            continue;
        }
        
        // 지수가 -1이면 입력 종료
        if (expon == -1) {
            poly[current_size].coef = -1.0f;
            poly[current_size].expon = -1;
            break;
        }

        // if 항 수 > 10 , realloc -> 배열 크기 증가
        if (current_size >= current_capacity - 1) {
            current_capacity *= 2;
            poly = (polynomial*)realloc(poly, sizeof(polynomial) * current_capacity);
            if (!poly) {
                fprintf(stderr, "메모리 재할당 실패\n");
                exit(1);
            }
        }
        
        // 배열에 항들이 지수의 내림차순으로 저장
        int i = 0;
        while (i < current_size && poly[i].expon > expon) {
            i++;
        }
        memmove(&poly[i + 1], &poly[i], sizeof(polynomial) * (current_size - i));
        
        poly[i].coef = coef;
        poly[i].expon = expon;
        current_size++;
    }
    
    // 최종적으로 사용된 크기만큼 메모리 재조정
    poly = (polynomial*)realloc(poly, sizeof(polynomial) * (current_size + 1));
    if (!poly) {
        fprintf(stderr, "메모리 재할당 실패\n");
        exit(1);
    }
    return poly;
}

// 다항식 출력
void print_polynomial(polynomial* poly) {
    if (!poly) return;
    printf("\tcoef\texpon\n");
    for (int i = 0; poly[i].expon != -1; i++) {
        printf("%8.2f%8d\n", poly[i].coef, poly[i].expon);
    }
}