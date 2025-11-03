#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

typedef struct {
    float coef; //계수
    int expon; //차수
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 0;
void attach(float coefficient, int exponent);

void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{
    float coefficient;
    *startd = avail;
    while (starta <= finisha && startb <= finishb)
        switch(COMPARE(terms[starta].expon, terms[startb].expon))
        {
            case -1 : 
                attach(terms[startb].coef, terms[startb].expon);
                startb++;
                break;
            case 0 :
                coefficient = terms[starta].coef + terms[startb].coef;
                if (coefficient) attach(coefficient, terms[starta].expon);
                starta++; startb++;
                break;
            case 1 :
                attach(terms[starta].coef, terms[starta].expon);
                starta++;
        }
        for ( ; starta <= finisha; starta++)
            attach(terms[starta].coef, terms[starta].expon);
        for ( ; startb <= finishb; startb++)
            attach(terms[startb].coef, terms[startb].expon);
        *finishd = avail - 1;
}

void attach(float coefficient, int exponent)
{
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "너무 많은 항\n");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

int main() {
    // 다항식 A: 3x^10 + 2x^0
    int starta = 0, finisha;
    attach(3.0, 10); 
    attach(2.0, 0); 
    finisha = avail - 1;

    // 다항식 B: 5x^5 - 3x^10 + 7x^0
    int startb = avail, finishb;
    attach(5.0, 5); 
    attach(-3.0, 10); // A의 3x^10과 더해져 0이 됨
    attach(7.0, 0); 
    finishb = avail - 1;

    int startd, finishd;
    
    // 덧셈 실행: D = A + B
    // (3x^10 + 2) + (5x^5 - 3x^10 + 7) 
    // 기대 결과: 5x^5 + 9x^0  (두 항)
    padd(starta, finisha, startb, finishb, &startd, &finishd);

    printf("--- 다항식 덧셈 결과 (D = A + B) ---\n");
    printf("시작 인덱스: %d, 끝 인덱스: %d\n", startd, finishd);
    
    if (startd > finishd) {
        printf("결과 다항식은 0입니다.\n");
    } else {
        printf("계수 | 차수\n");
        printf("-------\n");
        for (int i = startd; i <= finishd; i++) {
            printf("%.1f  | %d\n", terms[i].coef, terms[i].expon);
        }
    }

    /*
      기대 출력:
      계수 | 차수
      -------
      5.0  | 5
      9.0  | 0
    */
    
    printf("\n테스트 완료\n");
    
    return 0;
}