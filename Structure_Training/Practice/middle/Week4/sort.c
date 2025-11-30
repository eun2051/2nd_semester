#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TERMS 100
int avail = 0;

typedef struct {
    float coef;
    int expon;
} polynomical;
polynomical terms[MAX_TERMS];

int COMPARE(int x, int y) {
    if (x < y) return -1;
    if (x == y) return 0;
    return 1;
}

// 두 다항식을 더하는 함수
void padd (int startA, int finishA, int startB, int finishB, int *startD, int *finishD) {
    /*A(x)와 B*(x)를 더하여 D(x)를 생성*/
    float coefficient;
    *startD = avail;
    while (startA <= finishA && startB <= finishB){
        switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
            case -1: /* a의 expon < b의 expon*/
                attach(terms[startB].coef, terms[startB].expon);
                startB++;
                break;
            case 0: /*지수가 같은 경우*/
                coefficient = terms[startA].coef + terms[startB].coef;
                if (coefficient)
                    attach(coefficient, terms[startA].expon);
                startA++;
                startB++;
                break;
            case 1:
                attach(terms[startA].coef, terms[startA].expon);
                startA++;
        }
        //A()의 나머지 항들을 첨가
        for(; startA<= finishA; startA++)
            attach(terms[startA].coef, terms[startA].expon);
    }
    //B(x)의 나머지 항들을 첨가한다
    for(; startB <= finishB; startB++)
        attach(terms[startB].coef, terms[startB].expon);
    *finishD = avail - 1;
}

// 새로운 항을 첨가하는 함수
void attach (float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "다항식에 항이 너무 많음");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}