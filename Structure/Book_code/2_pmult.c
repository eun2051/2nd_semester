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

void pmult(int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{  /* A(x)와 B(x)를 곱하여 D(x)를 생성한다. */
    float coefficient;
    int exponent;
    int i,j;
    int s;
    *startd = avail;
 
    for(i = starta; i<=finisha;i++)
    {
        for(j=startb;j<=finishb;j++)
        {
            coefficient = terms[i].coef * terms[j].coef;   //계수의 곱
            exponent = terms[i].expon + terms[j].expon;  // 지수의 합
            s=finisha+finishb;                        // s의 위치 지정
            attach2(coefficient,exponent,s);          //곱셈항 첨가   
        }
    }
    *finishd = avail - 1;
}
