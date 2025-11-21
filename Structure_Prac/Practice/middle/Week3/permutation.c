#include <stdio.h>

int main() {

}

void perm(char *list, int i, int n) {
    //list[i] ~ list[n] 까지 순열
    int j, temp;
    if (i == n) { //종료 조건
        for (j = 0; j <= n; j++)
            printf("%c", list[j]);
        printf("    ");
    } else {
        //list[i] ~ list[n]이 하나의 순열보다 많을때
        //역순으로 생성
        for (j = i; j <= n; j++) {
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}