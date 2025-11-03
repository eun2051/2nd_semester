/* 큰 수의 곱 알고리즘 */
/* 분할 정복 방법도 있지만 필산 방식을 기반으로 한 곱셈 함수를 구현할 것임
1. 단일 숫자 곱셈 함수 구현 : 큰수 리스트와 한자리 숫자를 곱하는 보조 함수
1-1. 올림수와 자릿값 보정을 처리해야한다
2. 메인 곱셈 함수 구현 및 누적 덧셈
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

struct node *createNode(int digit);
struct node *reverse(const char *numstr);
struct node *numplus(struct node *num1, struct node *num2);
struct node *mul_onenum(struct node *num, int n, int shift);
struct node *nummul(struct node *num1, struct node *num2);
char        *readstr(FILE *fp);
void        printList(struct node *head);
void        freeList(struct node *head);

struct node *createNode(int digit)
{
    struct node *newNode;

    newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        return NULL;
    }
    newNode->data = digit;
    newNode->next = NULL;
    return newNode;
}
/* 역순으로 저장하는 로직 */
struct node *reverse(const char *numstr)
{
    struct node *head = NULL;
    int len = strlen(numstr);
    //문자열을 앞에서부터 읽음
    for (int i = 0; i < len; i++) {
        if (numstr[i] >= '0' && numstr[i] <= '9') {
            int digit = numstr[i] - '0';
            struct node *newNode = createNode(digit);
            //역순으로 저장하는 과정
            newNode->next = head;
            head = newNode;
        }
    }
    return head;
}

struct node *numplus(struct node *num1, struct node *num2)
{
    struct node *head = NULL;
    struct node *current = NULL;
    int carry = 0;

    while (num1 || num2 || carry)
    {   //덧셈은 반드시 이전 자리에서 넘어온 올림수부터 계산
        int sum = carry;
        // 첫 번째 수의 현재 자리 값 더하기
        if (num1) // num1이 NULL이 아닐때
        {
            sum += num1->data;
            num1 = num1->next;
        }
        // 두 번째 수의 현재 자리 값 더하기
        if (num2) // num2이 NULL이 아닐때
        {
            sum += num2->data;
            num2 = num2->next;
        }
        // 현재 자리의 올림수와 자릿값 계산
        carry = sum / 10; //다음 자리로 올라갈 올림수 (몫)
        int digit = sum % 10; //현재 자리에 저장되는 값(나머지/일의 자리수)

        struct node *result = createNode(digit);
        if (!head) { // 첫번째 노드일 경우
            head = result;
            current = result;
        } else { // 두번째 이후 노드일 경우
            current->next = result;
            current = result;
        }
    }
    return head; //결과 리스트의 시작 주소를 반환
}

struct node *mul_onenum(struct node *num, int n, int shift)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    //위치 보정 : shift 만큼 0 노드 추가
    for (int i = 0; i < shift; i++) {
        struct node *newNode = createNode(0);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int carry = 0;
    while (num || carry) {
        int mul = carry;

        if (num) {
            // 곱셈 연산 : (현재 노드 데이터 * 한자리수) + carry
            mul += num->data * n;
            num = num->next;
        }
        carry = mul / 10;
        int digit = mul % 10;

        struct node *N_node = createNode(digit);
        if (!head) { //리스트가 비어있을때 (shift = 0)일때
            head = N_node;
            tail = N_node;
        } else {
            tail->next = N_node;
            tail = N_node;
        }
    }
    return head;
}

struct node *nummul(struct node *num1, struct node *num2)
{
    struct node *mul_result = NULL;
    struct node *current = num2;
    int shift_cnt = 0; //뒤에 붙일 0의 개수

    while (current) {
        int digit2 = current->data;
        /* 단일 숫자 곱셈 실행 : num1 * digit2
        (digit2가 0이면 곱셈 결과 = 0 -> 건너뛰기 가능) */
        if (digit2) {
            struct node *part = mul_onenum(num1, digit2, shift_cnt);
            // 누적 덧셈
            // 첫번째 부분 곱 (누적 덧셈의 시작)
            if (mul_result == NULL) {
                mul_result = part;
            } else { // 두번째 이후 부분 곱 (기존 결과에 더하기)
                struct node *temp;
                //이전 결과와 부분 곱을 더하고, 결과를 result에 저장
                temp = numplus(mul_result, part);
                //이전 최종 결과와 부분 곱 리스트 해제 필수
                freeList(mul_result);
                freeList(part);
                mul_result = temp;
            }
        }
        current = current->next;
        shift_cnt++;
    }
    if (mul_result == NULL) {
        return createNode(0);
    }
    return mul_result;
}

char    *readstr(FILE *fp) 
{
    char *buffer = NULL;
    size_t size = 0;
    int c;

    // 파일 포인터가 가리키는 위치부터 한 글자씩 읽음
    while ((c = fgetc(fp)) != EOF) {
        if (c >= '0' && c <= '9') {
            // 숫자일 경우, 버퍼에 추가 (동적 재할당)
            size++;
            buffer = (char *)realloc(buffer, size + 1);
            if (!buffer) {
                perror("메모리 재할당 실패");
                exit(EXIT_FAILURE);
            }
            buffer[size - 1] = (char)c;
            buffer[size] = '\0'; // 문자열 끝 표시
        } else if (c == '\n') {
            // 개행 문자를 만나면 숫자 읽기 중단
            break; 
        }
        // 그 외 문자는 무시
    }
    return buffer; // 숫자가 저장된 문자열 반환 (사용 후 free 필요!)
}

void    printList(struct node *head)
{
    if (head == NULL) {
        return ;
    }
    printList(head->next);
    printf("%d", head->data);
}

void    freeList(struct node *head)
{
    struct node *temp;

    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    FILE *fp = NULL;
    struct node *n1 = NULL;
    struct node *n2 = NULL;
    struct node *result = NULL;
    struct node *result_mul = NULL;
    char    filename[100];
    char *num1 = NULL;
    char *num2 = NULL;

    printf("파일 이름? : ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("파일 열기 실패");
        return 1;
    }

    num1 = readstr(fp);
    num2 = readstr(fp);
    fclose(fp);
    if (num1) n1 = reverse(num1);
    if (num2) n2 = reverse(num2);

    printf("첫 번째 수 = %s\n", num1);
    printf("두 번째 수 = %s\n", num2);

    result = numplus(n1, n2);
    result_mul = nummul(n1, n2);

    printf("두 수의 합 = ");
    printList(result);
    printf("\n");
    printf("두 수의 곱 = ");
    printList(result_mul);
    printf("\n");

    free(num1);
    free(num2);
    freeList(n1);
    freeList(n2);
    freeList(result);
    freeList(result_mul);
    return 0;
}