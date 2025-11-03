#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

struct poly {
    int coef;
    int expon;
    struct poly *link;
};
struct poly *a, *b, *d;
struct poly* create_node(int coef, int expon, struct poly *current_rear);
void attach(float coefficient, int exponent, struct poly **rear);
struct poly *padd(struct poly *a, struct poly *b);

struct poly *padd(struct poly *a, struct poly *b)
{
    struct poly *front, *rear, *temp;
    int sum;
    rear = (struct poly *)malloc(sizeof(struct poly));
    if (rear == NULL) {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    front = rear;
    while (a && b) 
        switch(COMPARE(a->expon, b->expon)) {
            case -1 : 
                attach(b->coef, b->expon, &rear);
                b= b->link;
                break;
            case 0 :
                sum = a->coef + b->coef;
                if (sum) attach(sum, a->expon, &rear);
                a = a->link; b = b->link; break;
            case 1 :
                attach(a->coef, a->expon, &rear);
                a = a->link;
        }
    for (; a; a = a->link) attach(a->coef, b->expon, &rear);
    for (; b; b = b->link) attach(b->coef, b->expon, &rear);        rear->link = NULL;
     //초기 노드 삭제
    temp = front;
    front = front->link;
    free(temp);
    return front;
}

void attach(float coefficient, int exponent, struct poly **rear)
{
    struct poly *temp;
    temp = (struct poly *)malloc(sizeof(struct poly));
    if (temp == NULL) {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    temp->coef = coefficient;
    temp->expon = exponent;
    (*rear)->link = temp;
    *rear = temp;
}

struct poly* create_node(int coef, int expon, struct poly *current_rear) {
    struct poly *new_node = (struct poly *)malloc(sizeof(struct poly));
    if (new_node == NULL) {
        fprintf(stderr, "memory full\n");
        exit(1);
    }
    new_node->coef = coef;
    new_node->expon = expon;
    new_node->link = NULL;

    if (current_rear != NULL) {
        current_rear->link = new_node;
    }
    return new_node;
}

int main() {
    struct poly *poly_a = NULL, *rear_a = NULL;
    struct poly *poly_b = NULL, *rear_b = NULL;
    struct poly *poly_d = NULL;

    // --- 다항식 A 생성 (3x^10 + 2x^2) ---
    // 주의: 연결 리스트는 차수 내림차순으로 만들어야 padd가 작동합니다.
    poly_a = rear_a = create_node(3, 10, NULL);
    rear_a = create_node(2, 2, rear_a);
    
    // --- 다항식 B 생성 (5x^5 - 2x^2 + 1) ---
    poly_b = rear_b = create_node(5, 5, NULL);
    rear_b = create_node(-2, 2, rear_b); // A의 2x^2와 더해져 0이 됨
    rear_b = create_node(1, 0, rear_b);

    printf("--- 다항식 덧셈 (A + B) 테스트 ---\n");
    printf("A: 3x^10 + 2x^2\n");
    printf("B: 5x^5 - 2x^2 + 1\n");
    // 기대 결과: 3x^10 + 5x^5 + 1

    poly_d = padd(poly_a, poly_b);

    printf("\n--- 덧셈 결과 (D) ---\n");
    
    // 결과 다항식 D의 첫 번째 항만 간단하게 확인합니다.
    if (poly_d != NULL) {
        printf("첫 번째 항: %dx^%d\n", poly_d->coef, poly_d->expon);
        // 다음 항도 확인
        if (poly_d->link != NULL) {
             printf("두 번째 항: %dx^%d\n", poly_d->link->coef, poly_d->link->expon);
        }
    } else {
        printf("결과 다항식이 0입니다.\n");
    }
    
    printf("\n테스트 완료\n");
    
    return 0;
}
