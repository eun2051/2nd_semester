/* 다항식을 계수, 지수 쌍으로 이루어진 구조체 배열로 표현
두개의 다항식 A, B를 입력받아, A -B 를 계산하여 D 출력 
D의 값 계산하는 프로그램
다항식 D의 해를 이분법으로 구하는 프로그램*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TERMS 100
#define INITIAL_SIZE 10
#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

typedef struct {
    float coef;
    int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 0;
polynomial* D_poly;
int D_size = 0;
int D_capacity = INITIAL_SIZE;
polynomial* create_polynomial_manual(char* poly_name);
void free_polynomial(polynomial* poly);
void print_polynomial(polynomial* poly);
polynomial* psub(polynomial* A, polynomial* B);
void attach(float coefficient, int exponent);

int main() {
    polynomial *A, *B, *D;
    A = create_polynomial_manual("A(x)");
    B = create_polynomial_manual("B(x)");

    D = psub(A, B);
    printf("다항식 D : A - B\n");
    print_polynomial(D);

    printf("다항식의 해 계산범위 (a b TOL) : ");
    
    printf("다항식 D의 해 : ");

    free_polynomial(A);
    free_polynomial(B);
    free_polynomial(D);
    return 0;
}

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
    D_poly[D_size].expon = exponent;
}

polynomial* psub(polynomial* A, polynomial* B)
{
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
            float sub = A[i].coef - B[j].coef;
            if (sub != 0) {
                attach(sub, A[i].expon);
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


int bisection(int list[], int key, int left, int right)
{
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        switch(COMPARE(list[middle], key)) {
            case -1 : left = middle + 1;
                    break;
            case 0 : return middle;
            case 1 : right = middle - 1;
        }
    }
    return -1;
}

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
        printf("%s의 항을 입력하세요. (계수 지수) : ", poly_name);
        
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

void print_polynomial(polynomial* poly) {
    if (!poly) return;
    printf("\tcoef\texpon\n");
    for (int i = 0; poly[i].expon != -1; i++) {
        printf("%8.2f%8d\n", poly[i].coef, poly[i].expon);
    }
}

void free_polynomial(polynomial* poly) {
    if (poly) {
        free(poly);
    }
}