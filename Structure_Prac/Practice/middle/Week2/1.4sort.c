void sort(int list[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[min]) {
                min = j;
            }
            SWAP(list[i], list[min], temp);
        }
    }
}
//제일 작은 것을 잡아서 정렬을 한다
//프로그램 1.4 sort 함수
