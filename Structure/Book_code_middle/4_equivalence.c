#include <stdio.h>
#include <stdlib.h> // malloc, exit 사용
#include <string.h> // (비록 여기서는 사용되지 않지만, malloc을 위해 stdlib.h가 필수적임)

#define MAX_SIZE 24
#define IS_FULL(ptr) (!(ptr))
#define FALSE 0
#define TRUE 1

// 그래프의 인접 리스트 노드 및 스택 요소를 겸하는 구조체
struct node {
    int data; // 연결된 정점의 인덱스
    struct node *link;
};

int main()
{
    // out: 방문 여부 체크 (TRUE=미방문/미출력)
    short int out[MAX_SIZE]; 
    // seq: 인접 리스트의 헤드 포인터 배열 (seq[i]는 정점 i의 인접 리스트 시작)
    struct node *seq[MAX_SIZE], *x, *y, *top;
    int i, j, n;

    printf("Enter the number of vertices (<= %d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n > MAX_SIZE) {
        fprintf(stderr, "Invalid size entered or size exceeds %d.\n", MAX_SIZE);
        return 1;
    }
    
    // 초기화: 모든 정점은 미방문(TRUE), 인접 리스트는 NULL
    for (i = 0; i < n; i++)
    { 
        out[i] = TRUE; 
        seq[i] = NULL;
    }
    
    // 1. 그래프 입력 (무방향 그래프: i와 j를 연결)
    printf("Enter pair of numbers (edge: i j, -1 -1 to quit) (0 to %d): \n", n - 1);
    
    // 두 번의 scanf를 한 번의 if(scanf(...))로 묶어 입력 오류 처리
    while (scanf("%d %d", &i, &j) == 2 && i >= 0 && j >= 0)
    {
        if (i >= n || j >= n) {
            printf("Vertex index out of range (0 to %d). Enter again.\n", n - 1);
            continue;
        }
        
        // 정점 i에 j 추가 (인접 리스트의 맨 앞에 삽입)
        x = (struct node *)malloc(sizeof(struct node));
        if (IS_FULL(x)) { perror("Memory allocation failed"); exit(1); }
        x->data = j; 
        x->link = seq[i]; 
        seq[i] = x;

        // 정점 j에 i 추가 (무방향 그래프)
        x = (struct node *)malloc (sizeof(struct node));
        if (IS_FULL(x)) { perror("Memory allocation failed"); exit(1); }
        x->data = i; 
        x->link = seq[j]; 
        seq[j] = x;

        printf("Enter a pair of num (-1 -1 to quit): ");
    }
    
    // 2. 연결 요소 찾기 (DFS 기반)
    printf("\n--- Connected Components ---\n");
    for (i = 0; i < n; i++) {
        
        // 이미 출력된 정점(다른 연결 요소에 속함)이면 건너뜀
        if (!out[i]) continue;
        
        printf("\nNew class: %5d ", i ); // 새로운 연결 요소(클래스) 출력 시작
        out[i] = FALSE; // i를 방문/출력 완료 처리
        
        // --- DFS/스택 초기화 로직 (주석에서 가져옴) ---
        x = seq[i]; // 현재 정점(i)의 인접 리스트를 시작 노드로 설정
        top = NULL; // DFS 스택 초기화
        
        for ( ; ; ) { // 클래스의 나머지 원소를 찾자 (DFS 루프)
            
            while (x) { // 현재 정점의 인접 리스트를 스캔
                j = x->data;
                
                if (out[j]) { // j가 아직 출력되지 않았다면 (미방문 정점이라면)
                    printf("%5d", j); 
                    out[j] = FALSE; // j를 방문/출력 완료 처리
                    
                    // Push 로직: 현재 노드(x)를 스택에 PUSH (탐색 경로 저장)
                    y = x->link;      // 다음 노드를 y에 임시 저장
                    x->link = top;    // x의 link를 현재 top으로 연결
                    top = x;          // top을 x로 이동 (x가 새 top)
                    x = seq[j];       // x를 j의 인접 리스트 시작으로 설정 (탐색 깊이 증가)
                }
                else {
                    // 이미 방문한 노드라면, 현재 리스트의 다음 노드로 이동
                    x = x->link;
                }
            }
            
            if (!top)
                break; // 스택이 비었다면, 현재 클래스의 모든 원소를 출력하였음.
            
            // Pop 로직: 스택에서 노드를 POP (백트래킹)
            x = top; // top 노드를 x에 저장 (pop 할 노드)
            top = top->link; // top을 다음 노드로 이동
            
            // x의 인접 리스트를 스캔 (다음 백트래킹 지점)
            x = seq[x->data]; 
        }
    }
    printf("\n");
    
    // 메모리 해제 로직은 복잡하므로 간단한 테스트 코드에서는 생략합니다.
    
    return 0;
}