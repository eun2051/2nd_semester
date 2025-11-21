#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10
#define MAX_QUEUE_SIZE 10
#define MAX_CQUEUE_SIZE 10
#define ERROR_KEY -999

int *stack;
int top = -1;
int stack_max_size = MAX_STACK_SIZE;
int *queue;
int front = -1, rearq = -1;
int queue_max_size = MAX_QUEUE_SIZE;
int *cqueue;
int frontcq = 4, rearcq = 4;
int cqueue_max_size = MAX_CQUEUE_SIZE;