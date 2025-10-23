#include <stdio.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100 //m x p
#define MAX_ROW 7
#define MAX_COL 7
#define FALSE 0
#define TRUE 1
#define EXIT_ROW MAX_ROW
#define EXIT_COL MAX_COL

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;
element stack[MAX_STACK_SIZE];
int top = -1;

typedef struct {
    short int x;
    short int y;
} offsets;

offsets move[8] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, 
    {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};
int maze[MAX_ROW + 2][MAX_COL + 2] = {
    // 0 1 2 3 4 5 6 7 8 (인덱스)
    {1, 1, 1, 1, 1, 1, 1, 1, 1}, // 0번 행 (경계)
    {1, 0, 0, 0, 1, 1, 1, 1, 1}, // 1번 행
    {1, 1, 1, 0, 1, 1, 1, 1, 1}, // 2번 행
    {1, 1, 1, 0, 0, 0, 1, 1, 1}, // 3번 행
    {1, 1, 1, 0, 1, 0, 0, 0, 1}, // 4번 행
    {1, 1, 1, 0, 1, 1, 1, 0, 1}, // 5번 행
    {1, 1, 0, 0, 0, 0, 0, 0, 1}, // 6번 행
    {1, 1, 0, 1, 1, 1, 1, 0, 1}, // 7번 행 (7, 7)이 출구입니다.
    {1, 1, 1, 1, 1, 1, 1, 1, 1}  // 8번 행 (경계)
};
int mark[MAX_ROW + 2][MAX_COL + 2] = {0,};

void push (element item) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack[++top] = item;
}

element pop()
{
    if (top == -1) {
        element error_e = {-1, -1, -1};
        return error_e;
    }
    return stack[top--];
}

void path(void) 
{
    int i, row, col, next_row, next_col, dir;
    int found = FALSE;
    element position;

    mark[1][1] = 1; top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 2;
    while (top > -1 && !found) {
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 8 && !found) {
            next_row = row + move[dir].x;
            next_col = col + move[dir].y;
            if (next_row == EXIT_ROW && next_col == EXIT_COL)
                found = TRUE;
            else if (!maze[next_row][next_col] && !mark[next_row][next_col])
            {
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = next_row;
                col = next_col;
                dir = 0;
            }
            else ++dir;
        }
    }
    if (found) {
        printf(" The path is : \n");
        printf(" row col \n");
        for (i = 0; i <= top; i++)
            printf("%4d %4d\n", stack[i].row, stack[i].col);
        printf("%4d %4d\n", EXIT_ROW, EXIT_COL);
    }
    else printf(" the maze doesn't have a path\n");
}

int main() {
    path();
    return 0;
}