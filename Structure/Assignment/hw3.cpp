//22412051 이승은
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define SIZE 9
#define MAX_STACK_SIZE 81

struct Sudoku{
    int row;
    int column;
    int value;
};

Sudoku stck[MAX_STACK_SIZE];
int board[SIZE][SIZE];
int first_board[SIZE][SIZE];
int top = -1;
int sol_count = 0;

void push(int row, int col, int val) {
    if (top < MAX_STACK_SIZE - 1) {
        top++;
        stck[top].row = row;
        stck[top].column = col;
        stck[top].value = val;
    }
}

Sudoku pop() {
    if (top >= 0) {
        return stck[top--];
    }
    Sudoku empty = {-1, -1, -1};
    return empty;
}

int sudoku_rule(int row, int col, int val) {
    int check_row, check_col;
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == val) return 0;
        if (board[i][col] == val) return 0;
    }
    check_row = (row / 3) * 3;
    check_col = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[check_row + i][check_col + j] == val) return 0;
        }
    }
    return 1;
}

void print_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) cout << "- ";
            else cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != SIZE - 1) cout << "| ";
        }
        cout << "\n";
        if ((i + 1) % 3 == 0 && i != SIZE - 1)
            cout << "------+-------+------\n";
    }
    cout << "\n";
}

void solve_stack() {
    int change;
    do {
        change = 0;
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (board[r][c] == 0) {
                    int count = 0;
                    int last_val = 0;
                    for (int val = 1; val <= SIZE; val++) {
                        if (sudoku_rule(r, c, val)) {
                            count++;
                            last_val = val;
                        }
                    }
                    if (count == 1) {
                        board[r][c] = last_val;
                        change = 1;
                    }
                }
            }
        }
    } while (change);
}

int find_next_empty(int *row, int *col, int start_row, int start_col) {
    int r = start_row;
    int c = start_col;
    while (r < SIZE) {
        while (c < SIZE) {
            if (first_board[r][c] == 0) {
                *row = r;
                *col = c;
                return 1;
            }
            c++;
        }
        r++;
        c = 0;
    }
    return 0;
}

void solve_all_sudoku() {
    int r = 0, c = 0;
    
    while(r < SIZE) {
        if(first_board[r][c] == 0) break;
        c++;
        if(c == SIZE) {
            c = 0;
            r++;
        }
    }
    if(r == SIZE) {
        sol_count++;
        cout << "하나의 해답 행렬:\n";
        print_board();
        return;
    }

    push(r, c, 0);

    while (top >= 0) {
        Sudoku current = pop();
        int row = current.row;
        int col = current.column;
        int val = current.value + 1;

        board[row][col] = 0;

        int found_next = 0;
        for (; val <= SIZE; val++) {
            if (sudoku_rule(row, col, val)) {
                board[row][col] = val;
                push(row, col, val);
                
                int next_row = row;
                int next_col = col;
                if (find_next_empty(&next_row, &next_col, next_row, next_col + 1)) {
                    push(next_row, next_col, 0);
                    found_next = 1;
                } else {
                    sol_count++;
                    cout << "해답 행렬 " << sol_count << ":\n";
                    print_board();
                
                    found_next = 1;
                    board[row][col] = 0;
                }
                break;
            }
        }
        if (!found_next) {
            if(top >= 0 && first_board[stck[top].row][stck[top].column] != 0) {
                 while(top >= 0 && first_board[stck[top].row][stck[top].column] != 0) {
                    pop();
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    string filename;
    cout << "파일 이름? ";
    cin >> filename;

    ifstream fp(filename);
    if (!fp) {
        cerr << "파일을 열 수 없습니다.\n";
        return 1;
    }

    int n, r, c, v;
    fp >> n;
    for (int i = 0; i < n; i++) {
        fp >> r >> c >> v;
        board[r][c] = v;
        first_board[r][c] = v;
    }
    fp.close();

    cout << "문제 행렬을 예쁘게 출력\n";
    print_board();

    solve_stack();
    cout << "후보 값이 하나인 cell에 값을 할당한 결과\n";
    print_board();

    solve_all_sudoku();
    cout << "해답의 수: " << sol_count << "\n";

    return 0;
}