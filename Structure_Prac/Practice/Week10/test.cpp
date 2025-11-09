#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

typedef struct polyNode *polyPointer;
polyPointer avail = NULL;
typedef struct polyNode {
    float coef;
    int expon;
    polyPointer link;
} polyNode;

polyPointer getNode(void);
void retNode(polyPointer node);
void cerease(polyPointer *ptr);
polyPointer create_polynomial();
void attach(float coefficient, int exponent, polyPointer *ptr);
polyPointer cpadd(polyPointer A, polyPointer B);
void print_polynomial(polyPointer C);
polyPointer single_cpmul(polyNode Ai, polyPointer B);
polyPointer cpmul(polyPointer A, polyPointer B);

// 사용할 노드를 제공하는 함수
polyPointer getNode()
{
    polyPointer node;
    if (avail) //avail이 빈 리스트가 아니라면
    {
        node = avail;
        avail = avail->link;
    } else { //avail이 빈 리스트라면
        node = (polyPointer)malloc(sizeof(polyNode));
    }
    return node;
}

// 가용 리스트에 노드를 반환하기
void retNode(polyPointer node)
{
    node->link = avail;
    avail = node;
}

// 원형 리스트를 가용 리스트에 반환하기
void cerease(polyPointer *ptr)
{
    polyPointer tmp;

    if (*ptr)
    { // ptr이 빈 리스트가 아니라면
        tmp = (*ptr)->link; //tmp는 *ptr의 두번째 노드를 가리킴
        (*ptr)->link = avail; //*ptr의 첫번째 노드의 link는 avail의 첫번째 노드를 가리킴
        avail = tmp; //avail은 *ptr의 두번째 노드를 가리킴
        *ptr = NULL; // 빈 리스트를 가리킴
        // *ptr의 두번째 노드부터 첫번쨰 노드까지 avail의 앞 쪽 노드에 삽입되는 것
    }
}

// 원형 연결 리스트의 끝에 노드 삽입하기
void attach(float coefficient, int exponent, polyPointer *ptr)
{
    polyPointer tmp = getNode();

    tmp->coef = coefficient;
    tmp->expon = exponent;
    tmp->link = (*ptr)->link; // 첫번째 노드와 연결
    (*ptr)->link = tmp;
    *ptr = tmp;
}

// <계수, 지수> 쌍을 입력받아 원령 연결리스트로 구현하기
polyPointer create_polynomial() {
    polyPointer head = getNode();
    polyPointer tmp;
    float coef;
    int expon;

    head->coef = -1;
    head->expon = -1;
    head->link = head;
    tmp = head;

    while (true)
    {
        printf("다항식의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &coef, &expon);
        if (coef == -1 && expon == -1) {
            tmp->link = head;
            break;
        }
        attach(coef, expon, &tmp);
    }
    return head;
}

void print_polynomial(polyPointer C)
{
    polyPointer tmp;
    
    tmp = C->link;
    printf("\tcoef\texpon\n");
    while (tmp != C)
    {
        printf("\t%.2f\t%d\n", tmp->coef, tmp->expon);
        tmp = tmp->link;
    }
}

//다항식 덧셈
polyPointer cpadd(polyPointer A, polyPointer B)
{
    polyPointer startA, C, lastc;
    int sum, done = false;

    startA = A;
    A = A->link;
    B = B->link;
    C = getNode();

    C->coef = -1;
    C->expon = -1;
    C->link = C;
    lastc = C;
    do {
        switch(COMPARE(A->expon, B->expon)) {
            case -1:
                attach(B->coef, B->expon, &lastc);
                B = B->link;
                break;
            case 0:
                if (startA == A) done = true;
                else {
                    sum = A->coef + B->coef;
                    if (sum) attach(sum, A->expon, &lastc);
                    A = A->link; B = B->link;
                }
                break;
            case 1:
                attach(A->coef, A->expon, &lastc);
                A = A->link;
        }
    } 
    while (!done);
    return C;
}

//다항식 곱셈
/* A 항 하나와 B 다항식을 곱한 다항식 Ai를 결과값 C에 더하기
   A의 항을 다 돌때까지 위 과정을 반복*/
polyPointer cpmul(polyPointer A, polyPointer B)
{
    polyPointer C, startA, lastc;
    int i = 1;
    startA = A;
    A = A->link;

    C = getNode();
    C->coef = -1;
    C->expon = -1;
    C->link = C;
    lastc= C;

    while (true)
    {
        if (startA == A) break;
        polyPointer Ci = single_cpmul(*A, B);
        A = A->link;

        printf("single_mul - C%d(x)\n", i);
        print_polynomial(Ci);

        C = cpadd(C, Ci);
        i++;
    }
    return C;
}

// A의 항 하나와 B의 다항식을 곱하는 함수
polyPointer single_cpmul(polyNode Ai, polyPointer B)
{
    polyPointer C, startB, lastc;
	startB = B;
	B = B->link;
	
	C = getNode();
	C->coef = -1;
	C->expon = -1;
	C->link = C;
	lastc = C;

	while (true) {
		if (startB == B) break;
		attach(Ai.coef * B->coef, Ai.expon + B->expon, &lastc);
		B = B->link;
	}
	C = lastc->link;
	return C;
}

int main()
{
    polyPointer A, B, D, Dmul;
    
    printf("7.1. 다항식 생성\n");
    printf("다항식 A(x)\n");
    A = create_polynomial();
    printf("다항식 A(x) : \n");
    print_polynomial(A);

    printf("다항식 B(x)\n");
    B = create_polynomial();
    printf("다항식 B(x) : \n");
    print_polynomial(B);

    printf("7.2. 다항식 덧셈\n");
    D = cpadd(A, B);
    printf("다항식 덧셈 결과 : D(x)\n");
    print_polynomial(D);

    printf("7.3. 다항식 곱셈\n");
    Dmul = cpmul(A, B);
    printf("다항식 곱셈 결과 : D(x)\n");
    print_polynomial(Dmul);

    cerease(&Dmul);
    cerease(&D);
    cerease(&A);
    cerease(&B);
}
