#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

//Max heap에 삽입
void insert_max_heap(element item, int *n)
{
		int i;
		if (HEAP_FULL(*n)) {
			fprintf(stderr, "heap full\n");
			exit(1);
		}
		i = ++(*n);
		while((i != 1) && (item.key > heap[i/2].key)) {
			heap[i] = heap[i/2];
			i /= 2;
		}
		heap[i] = item;
}

// Max heap에서 노드 삭제
// 힙에서 삭제는 항상 root node에서만 발생
element delete_max_heap(int *n)
{
	int parent, child;
	element item, temp;
	
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "heap empty\n");
		exit(1);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1; child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
		child++;
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}