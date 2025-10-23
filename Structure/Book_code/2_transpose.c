/* 2차원 배열에서 transpose의 구현
    for (int i = 0; i <. rows; i++)
        for (int j = 0; j < col; j++)
            b[i][j] = a[j][i];*/
#define MAX_TERMS 101
#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
} term;
term a[MAX_TERMS];

void transpose(term a[], term b[])
{
    int count, i, j, currentb;
    count = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = count;
    if (count > 0) {
        currentb = 1;
        for (i = 0; i < a[0].col; i++) {
            for (j = 1; j <= count; j++) {
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}