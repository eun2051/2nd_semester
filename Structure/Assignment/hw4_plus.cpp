/* 큰 수의 덧셈 알고리즘 */
/* 1. 단일 연결리스트를 사용한다면 계산 전에 두 입력 리스트를 역순으로 뒤집음
   2. 순차적으로 덧셈을 해준다. 받아올림(carry) 처리
   2-1. 리스트 길이 차이 : 두 숫자의 길이가 다를 경우, 짧은 리스트가 끝나면 남은 긴 리스트의 
   노드 와 올림수만 더하면 됨
   2-2. 마지막 올림수 : 모든 노드 처리가 끝난 후에도 올림수가 남아있다면, 새 노드를 만들어
   저장해야함
   3. 결과 리스트 생성해준다
   4. 최종으로 다시 뒤집어준다 (역순으로 저장하여 덧셈을 해주었기 떄문)*/
/* 리스트 길이의 차이 ? */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

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

char    *readstr(FILE *fp) {
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

int main()
{
    FILE *fp = NULL;
    struct node *n1 = NULL;
    struct node *n2 = NULL;
    struct node *result = NULL;
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

    printf("두 수의 합 = ");
    printList(result);
    printf("\n");

    free(num1);
    free(num2);
    freeList(n1);
    freeList(n2);
    freeList(result);
    return 0;
}