#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10

typedef struct polynomial {
    float coef;
    int expon;
} polynomial;


void print_polynomial(polynomial* poly);
polynomial* padd(polynomial* A, polynomial* B);
polynomial* single_mul(polynomial* A, polynomial B_term);
polynomial* pmul(polynomial* A, polynomial* B);
void free_polynomial(polynomial* poly);

int main() {
    printf("3.3 다항식 곱셈\n");

    // 예시 출력을 위해 다항식 A와 B를 직접 생성
    polynomial* A = (polynomial*)malloc(sizeof(polynomial) * 6);
    if (!A) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }
    A[0] = (polynomial){3.0, 20};
    A[1] = (polynomial){-1.0, 5};
    A[2] = (polynomial){1.0, 4};
    A[3] = (polynomial){-5.0, 3};
    A[4] = (polynomial){4.0, 0};
    A[5] = (polynomial){-1.0, -1};

    polynomial* B = (polynomial*)malloc(sizeof(polynomial) * 5);
    if (!B) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }
    B[0] = (polynomial){2.0, 4};
    B[1] = (polynomial){10.0, 3};
    B[2] = (polynomial){-3.0, 2};
    B[3] = (polynomial){1.0, 0};
    B[4] = (polynomial){-1.0, -1};

    polynomial* D = pmul(A, B);
    printf("다항식 곱셈 결과 : D(x)\n");
    print_polynomial(D);

    // 메모리 해제
    free_polynomial(A);
    free_polynomial(B);
    free_polynomial(D);

    return 0;
}

// 다항식을 출력하는 함수
void print_polynomial(polynomial* poly) {
    if (!poly) return;
    printf("    coef    expon\n");
    for (int i = 0; poly[i].expon != -1; i++) {
        printf("%8.2f%8d\n", poly[i].coef, poly[i].expon);
    }
}

// 두 다항식을 더하는 함수 (padd)
polynomial* padd(polynomial* A, polynomial* B) {
    int i = 0, j = 0, k = 0;
    int max_size_D = INITIAL_SIZE;
    polynomial* D = (polynomial*)malloc(sizeof(polynomial) * max_size_D);
    if (!D) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    
    while (A[i].expon != -1 || B[j].expon != -1) {
        if (k >= max_size_D - 1) {
            max_size_D *= 2;
            D = (polynomial*)realloc(D, sizeof(polynomial) * max_size_D);
            if (!D) exit(1);
        }
        
        if (A[i].expon == -1) {
            D[k++] = B[j++];
        } else if (B[j].expon == -1) {
            D[k++] = A[i++];
        } else if (A[i].expon > B[j].expon) {
            D[k++] = A[i++];
        } else if (A[i].expon < B[j].expon) {
            D[k++] = B[j++];
        } else {
            float sum = A[i].coef + B[j].coef;
            if (sum != 0) {
                D[k].coef = sum;
                D[k].expon = A[i].expon;
                k++;
            }
            i++;
            j++;
        }
    }
    D[k].coef = -1.0f;
    D[k].expon = -1;
    D = (polynomial*)realloc(D, sizeof(polynomial) * (k + 1));
    if (!D) exit(1);
    return D;
}

// 단일 항과 다항식을 곱하는 함수 (single_mul)
polynomial* single_mul(polynomial* A, polynomial B_term) {
    int k = 0;
    int max_size_C = INITIAL_SIZE;
    polynomial *C = (polynomial*)malloc(sizeof(polynomial) * max_size_C);
    if (!C) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    
    for (int i = 0; A[i].expon != -1; i++) {
        if (k >= max_size_C - 1) {
            max_size_C *= 2;
            C = (polynomial*)realloc(C, sizeof(polynomial) * max_size_C);
             if (!C) exit(1);
        }
        C[k].coef = A[i].coef * B_term.coef;
        C[k].expon = A[i].expon + B_term.expon;
        k++;
    }
    
    C[k].coef = -1.0f;
    C[k].expon = -1;
    
    C = (polynomial*)realloc(C, sizeof(polynomial) * (k + 1));
    if (!C) exit(1);
    return C;
}

// 두 다항식을 곱하는 함수 (pmul)
polynomial* pmul(polynomial* A, polynomial* B) {
    polynomial *D = (polynomial*)malloc(sizeof(polynomial) * (INITIAL_SIZE * 2));
    if (!D) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    D[0].coef = -1.0f;
    D[0].expon = -1;
    
    int C_count = 1;
    for (int i = 0; A[i].expon != -1; i++) {
        polynomial* C_temp = single_mul(B, A[i]);
        printf("singul_mul - C%d(x)\n", C_count++);
        print_polynomial(C_temp);

        polynomial* D_new = padd(D, C_temp);
        
        free_polynomial(D);
        free_polynomial(C_temp);
        D = D_new;
    }
    return D;
}

// 동적 할당된 메모리를 해제하는 함수
void free_polynomial(polynomial* poly) {
    if (poly) {
        free(poly);
    }
}