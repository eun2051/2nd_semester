#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

/* list[0] <= list[1] <= .. <= list[n-1] search for key
        Return position if found, otherwise return -1 */
int binsearch(int list[], int key, int left, int right)
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

int main() {
	int searchnum;
	int data[] = {1, 4, 8, 11, 13, 16, 23};
	int dataSize = sizeof(data) / sizeof(int);
	for (int i = 0; i < dataSize ; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
	printf("찾을 숫자: ");
	scanf("%d", &searchnum);
	int ans = binsearch(data, searchnum, 0, dataSize - 1);
	printf("%d번째 인덱스, 값: %d\n", ans, data[ans]);
}

/*
int compare (int x, int y)
{
    if (x < y) return -1;
    else if (x == y) return 0;
    else return 1;
}*/
