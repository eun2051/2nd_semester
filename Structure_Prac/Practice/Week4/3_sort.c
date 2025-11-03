#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#define COMPARE
#define SWAP
*/
#define INITIAL_SIZE 10

typedef struct polynomial {
    float coef;
    int expon;
} polynomial;
/*
polynomial *A, *B, *D;
int i, max_D; // *D -> attach 때문에 전역으로 관리해야함
//메모리 관리 -> max_D
*/
polynomial* D_poly;
int D_size = 0;
int D_capacity = INITIAL_SIZE;

polynomial* create_polynomial_manual(char* poly_name);
void print_polynomial(polynomial* poly);
polynomial* padd(polynomial* A, polynomial* B);
polynomial* single_mul(polynomial* B, polynomial A_term);
polynomial* pmul(polynomial* A, polynomial* B);
void free_polynomial(polynomial* poly);
void attach(float coefficient, int exponent);

int main() {
    polynomial *A, *B, *D_add, *D_mul;
    printf("3.1. 다항식 생성\n");
    A = create_polynomial_manual("A(x)");
    printf("다항식 A(x)\n");
    print_polynomial(A);
    
    printf("\n");
    B = create_polynomial_manual("B(x)");
    printf("다항식 B(x)\n");
    print_polynomial(B);

    printf("\n3.2 다항식 덧셈\n");
    D_add = padd(A, B);
    printf("다항식 덧셈 결과 : D(x)\n");
    print_polynomial(D_add);

    printf("\n3.3 다항식 곱셈\n");
    D_mul = pmul(A, B);
    printf("다항식 곱셈 결과 : D(x)\n");
    print_polynomial(D_mul);

    free_polynomial(A);
    free_polynomial(B);
    free_polynomial(D_mul);
    return 0;
}

// 다항식을 사용자로부터 입력받아 동적으로 생성하는 함수
polynomial* create_polynomial_manual(char* poly_name) {
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

// 새로운 항 첨가 함수
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

//항 하나와 다항식을 곱하는 함수
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

// 두 다항식 곱셈 함수
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

// 다항식 출력 함수
void print_polynomial(polynomial* poly) {
    if (!poly) return;
    printf("\tcoef\texpon\n");
    for (int i = 0; poly[i].expon != -1; i++) {
        printf("%8.2f%8d\n", poly[i].coef, poly[i].expon);
    }
}

// 메모리 해제 함수
void free_polynomial(polynomial* poly) {
    if (poly) {
        free(poly);
    }
}

/*int main () {
    float coef;
    int expon;
    int n, max_A, max_B;

    while (1) {
        max_A = max_B = MAX_TERMS;

        A = (polynomial *)malloc(sizeof(polynomial) * max_A);
        B = (polynomial *)malloc(sizeof(polynomial) * max_B);

        printf("3.1. 다항식 생성\n")
        for (n = 0; ; n++) {
            if (n == max_A) {
                max_A += MAX_TERMS;
                A = (polynomial *)realloc(A, sizeof(polynomial) * max_A);
            }
            printf("A(x)의 항을 입력하세요 : ");
            scanf();
            A[n].coef = coef;
            A[n].expon = expon;

            if (expon < 0)
                break;
        }
        sortpoly(A);
        printf("다항식A(X)\n");
        print(A);

        for (n = 0; ; n++) {
            if (n == max_B) {
                max_B += MAX_TERMS;
                B = (polynomial *)realloc(B, sizeof(polynomial) * max_B);
            }
            printf("B(x)의 항을 입력하세요 : ");
            scanf("%f %d", &coef, &expon));
            B[n].coef = coef;
            B[n].expon = expon;

            if (expon < 0)
                break;
        }
        sortpoly(B);
        printf("다항식B(X)\n");
        print(B);

        printf("3.2 다항식 덧셈\n");
        k = 0;
        max_D = MAX_TERMS;
        D = (polynomial *)re
    }
}

void sortpoly(polynomial *A)
{
    int i, j, max, temp;
    float tempf;
    for (i = 0; A[i].expon > -1; i++)
    {
        max = i;
        for (j = i + 1; A[j].expon > -1; j++)
            if (A[j].expon > A[max].expon)
                max = j;
        SWAP(A[i].expon, A[max].expon, temp);
        SWAP(A[i].coef, A[max].coef, tempf);
    }
}

polynomial * padd(polynomial){
    float cofficient;
    int i= 0, j = 0;
    while
}

void attach(float coefficient, int exponent) {
    if ( k == max_d) {
        max_D += mAX_TERMS;
        D = (polynomial *)realloc(D, sizeof(polynommial)* max_D)
    }
    D[n].coef = coefficient;
    D[n].expon = exponent;
    k++;
}
*/