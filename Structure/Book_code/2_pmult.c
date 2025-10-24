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

void attach(float coefficient, int exponent)
{
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "너무 많은 항\n");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

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

void pmult(int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{
    int i, j;
    int current_d_start, current_d_finish; // 현재까지 누적된 D(x)의 위치
    int temp_start, temp_finish;            // A[i]와 B를 곱한 임시 결과의 위치
    int next_start, next_finish;            // 다음 반복을 위한 임시 변수
    
    // 1. D(x)의 시작 위치를 avail로 지정합니다.
    *startd = avail;
    *finishd = avail - 1; // 초기에는 빈 다항식으로 설정

    // A(x)의 모든 항을 순회합니다.
    for (i = starta; i <= finisha; i++) {
        
        // 2. 임시 배열에 A[i]와 B(x)의 곱셈 결과를 저장합니다.
        temp_start = avail;
        for (j = startb; j <= finishb; j++) {
            float coef = terms[i].coef * terms[j].coef;
            int expon = terms[i].expon + terms[j].expon;
            if (coef != 0) {
                attach(coef, expon);
            }
        }
        temp_finish = avail - 1; // 임시 결과의 끝

        // 3. 기존의 누적 결과 D(x)와 현재 임시 결과를 padd로 합산/정리합니다.

        // 기존 D의 위치를 가져옵니다.
        current_d_start = *startd;
        current_d_finish = *finishd;
        
        // 새로운 D가 저장될 위치를 avail로 지정합니다.
        next_start = avail; 

        // padd를 사용하여 기존 D와 임시 결과를 합치고 새로운 D를 만듭니다.
        // *startd와 *finishd가 다음 D의 범위가 됩니다.
        padd(current_d_start, current_d_finish, temp_start, temp_finish, startd, finishd);
        
        // 참고: padd가 실행된 후, 이전의 D와 Temp 영역은 버려지고, 
        // 새로운 D가 avail 이후에 저장됩니다. (terms 배열의 비효율적 사용)
    }
    // 루프가 완료되면 *startd와 *finishd가 최종 결과 D(x)를 가리킵니다.
}