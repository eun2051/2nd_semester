//22412051 이승은
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

struct node *reverse(const char *numstr)
{
    struct node *head = NULL;
    int len = strlen(numstr);
    for (int i = 0; i < len; i++) {
        if (numstr[i] >= '0' && numstr[i] <= '9') {
            int digit = numstr[i] - '0';
            struct node *newNode = createNode(digit);
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
    {
        int sum = carry;
        if (num1)
        {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2)
        {
            sum += num2->data;
            num2 = num2->next;
        }
        carry = sum / 10;
        int digit = sum % 10;

        struct node *result = createNode(digit);
        if (!head) {
            head = result;
            current = result;
        } else {
            current->next = result;
            current = result;
        }
    }
    return head;
}

struct node *mul_onenum(struct node *num, int n, int shift)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    int carry = 0;

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
    while (num || carry) {
        int mul = carry;

        if (num) {
            mul += num->data * n;
            num = num->next;
        }
        carry = mul / 10;
        int digit = mul % 10;

        struct node *N_node = createNode(digit);
        if (!head) {
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
    int shift_cnt = 0;

    while (current) {
        int digit2 = current->data;
        if (digit2) {
            struct node *part = mul_onenum(num1, digit2, shift_cnt);
            if (mul_result == NULL) {
                mul_result = part;
            } else {
                struct node *temp;
                temp = numplus(mul_result, part);
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

    while ((c = fgetc(fp)) != EOF) {
        if (c >= '0' && c <= '9') {
            size++;
            buffer = (char *)realloc(buffer, size + 1);
            if (!buffer) {
                printf("메모리 재할당 실패\n");
                exit(1);
            }
            buffer[size - 1] = (char)c;
            buffer[size] = '\0';
        } else if (c == '\n') {
            break; 
        }
    }
    return buffer;
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