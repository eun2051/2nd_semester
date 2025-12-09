#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

// 만족성 문제
// 논리식을 만족하는 진리값들의 할당
typedef enum {
    logic_not,
    logic_and,
    logic_or,
    logic_true,
    logic_false
} logical;
struct node {
	struct node *lchild;
	struct node *rchild;
	logical data;
	short int value;
};

// 만족성 알고리즘
// 논리식 트리를 계산하기 위한 postorder()의 변형
void post_order_eval(struct node *node)
{
	if (node) {
		post_order_eval(node->lchild);
		post_order_eval(node->rchild);
		switch(node->data) {
			case logic_not:
                node->value = !node->rchild->value;
				break;
			case logic_and:
                node->value = node->lchild->value && node->rchild->value;
				break;
			case logic_or:
                node->value = node->lchild->value  || node->rchild->value;
				break;
			case logic_true:
                node->value = TRUE;
                break; //단말노드
			case logic_false:
                node->value = FALSE; //단말노드
                break;
		}
	}
}