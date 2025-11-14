#include <stdio.h>

typedef struct node *tree_pointer;
struct node {
    int data;
    struct node *left_child;
    struct node *right_child;
};