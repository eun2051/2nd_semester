#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10

typedef struct polynomial {
    float coef;
    int expon;
} polynomial;

// 전역변수
polynomial* D_poly;
int D_size = 0;
int D_capacity = INITIAL_SIZE;

polynomial* create_polynomial_manual(const char* poly_name);
void print_polynomial(polynomial* poly);
polynomial* padd(polynomial* A, polynomial* B);
void attach(float coefficient, int exponent);
void free_polynomial(polynomial* poly);

int main() {
    printf("3.1. 다항식 생성\n");
    
    // 다항식 A 생성
    polynomial* A = create_polynomial_manual("A(x)");
    printf("다항식 A(x)\n");
    print_polynomial(A);

    printf("\n");

    // 다항식 B 생성
    polynomial* B = create_polynomial_manual("B(x)");
    printf("다항식 B(x)\n");
    print_polynomial(B);
    
    printf("\n3.2 다항식 덧셈\n");
    
    // A와 B를 더해 D 다항식 생성
    polynomial* D = padd(A, B);
    printf("다항식 덧셈 결과 : D(x)\n");
    print_polynomial(D);


    polynomial* D = pmul(A, B);
    printf("다항식 곱셈 결과 : D(x)\n");
    print_polynomial(D);

    // 할당된 메모리 해제
    free_polynomial(A);
    free_polynomial(B);
    free_polynomial(D);
    
    return 0;
}

// 다항식을 사용자로부터 입력받아 동적으로 생성하는 함수
polynomial* create_polynomial_manual(const char* poly_name) {
    int current_size = 0;
    int current_capacity = INITIAL_SIZE;
    
    polynomial* poly = (polynomial*)malloc(sizeof(polynomial) * current_capacity);
    if (!poly) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    
    float coef;
    int expon;
    
    while (1) {
        printf("%s의 항을 입력하세요. (coef expon) : ", poly_name);
        
        if (scanf("%f %d", &coef, &expon) != 2) {
            while (getchar() != '\n');
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            continue;
        }
        
        if (expon == -1) {
            poly[current_size].coef = -1.0f;
            poly[current_size].expon = -1;
            break;
        }

        if (current_size >= current_capacity - 1) {
            current_capacity *= 2;
            poly = (polynomial*)realloc(poly, sizeof(polynomial) * current_capacity);
            if (!poly) {
                fprintf(stderr, "메모리 재할당 실패\n");
                exit(1);
            }
        }
        
        int i = 0;
        while (i < current_size && poly[i].expon > expon) {
            i++;
        }
        memmove(&poly[i + 1], &poly[i], sizeof(polynomial) * (current_size - i));
        
        poly[i].coef = coef;
        poly[i].expon = expon;
        current_size++;
    }
    
    poly = (polynomial*)realloc(poly, sizeof(polynomial) * (current_size + 1));
    if (!poly) {
        fprintf(stderr, "메모리 재할당 실패\n");
        exit(1);
    }
    
    return poly;
}

// 새로운 항을 첨가하는 함수
void attach(float coefficient, int exponent) {
    if (D_size >= D_capacity) {
        D_capacity *= 2;
        D_poly = (polynomial*)realloc(D_poly, sizeof(polynomial) * D_capacity);
        if (!D_poly) {
            fprintf(stderr, "메모리 재할당 실패\n");
            exit(1);
        }
    }
    D_poly[D_size].coef = coefficient;
    D_poly[D_size++].expon = exponent;
}

// 다항식을 출력하는 함수
void print_polynomial(polynomial* poly) {
    if (!poly) return;
    printf("    coef    expon\n");
    for (int i = 0; poly[i].expon != -1; i++) {
        printf("%8.2f%8d\n", poly[i].coef, poly[i].expon);
    }
}

// 두 다항식의 덧셈
polynomial* padd(polynomial* A, polynomial* B) {
    D_poly = (polynomial*)malloc(sizeof(polynomial) * INITIAL_SIZE);
    if (!D_poly) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    D_size = 0;
    D_capacity = INITIAL_SIZE;

    int i = 0, j = 0;

    while (A[i].expon != -1 || B[j].expon != -1) {
        if (A[i].expon == -1) {
            attach(B[j].coef, B[j].expon);
            j++;
        } else if (B[j].expon == -1) {
            attach(A[i].coef, A[i].expon);
            i++;
        } else if (A[i].expon > B[j].expon) {
            attach(A[i].coef, A[i].expon);
            i++;
        } else if (A[i].expon < B[j].expon) {
            attach(B[j].coef, B[j].expon);
            j++;
        } else {
            float sum = A[i].coef + B[j].coef;
            if (sum != 0) {
                attach(sum, A[i].expon);
            }
            i++;
            j++;
        }
    }
    
    attach(-1.0f, -1);
    
    D_poly = (polynomial*)realloc(D_poly, sizeof(polynomial) * D_size);
    if (!D_poly) exit(1);

    return D_poly;
}

// 동적 할당된 메모리를 해제하는 함수
void free_polynomial(polynomial* poly) {
    if (poly) {
        free(poly);
    }
}
