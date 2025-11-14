#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "TreeNode.h"
#include "BST.h"
#define LINE_SIZE 400

using std::string;
using std::ofstream;
using std::ios;
using std::endl;

void insert_record(BST<string,int> *);
void bulk_insert(BST<string,int> *);
void print_tree(BST<string, int> *);
void convert_to_lower(char *);

int main()
{
	BST<string,int> *tree = new BST<string,int>;
	TreeNode<string,int> *node;
	int menu;
	char input[50];

	while (1) {
		printf("\n메뉴: 파일 입력(1), 트리 출력(2), 검색(3), 삽입(4), 삭제(5), 정보(6), 종료(7) ? ");
		scanf("%d", &menu);
		gets_s(input);
		switch (menu) {

			case 1:	
				bulk_insert(tree);
				break;
			case 2:
				print_tree(tree);
				break;
			case 3:
				printf("검색할 단어? ");
				gets_s(input);
				node = tree->searchNode(input);
				if (node == NULL)
					printf("없는 단어입니다.\n");
				else
					printf("%s의 발생 빈도수 = %d\n", input, node->getValue());
				break;
			case 4:	
				insert_record(tree);
				break;
			case 5:
				printf("삭제할 단어? ");
				gets_s(input);
				tree->deleteNode(input);
				break;
			case 6:	
				printf("\n트리의 상태: "); 
				tree->treeStatus();
				printf("\n");
				break;
			case 7:	
				return -1;
		}
	}
}

void insert_record(BST<string, int> *tree)
{
	int result;
	char input[50];

	printf("추가할 단어? ");
	gets_s(input);

	result = tree->insertNode(input, 1);
	printf("삽입 후 %s의 빈도수 = %d\n", input, result);
}

void bulk_insert(BST<string, int> *tree)
{
	FILE	*fp;
	char	fname[50], line[LINE_SIZE];
	char	seps[] = " \t\n.,\'\"?![]:;-_", *token;
	int		count = 0;

	printf("입력 파일 이름? ");
	gets_s(fname);
	fp = fopen(fname, "rt");

	if (!fp) {
		printf("###%s 파일이 존재하지 않습니다.\n", fname);
		return;
	}

	while (fgets(line, LINE_SIZE, fp) != NULL) {
		for (token = strtok(line, seps); token != NULL; token = strtok(NULL, seps)) {
			convert_to_lower(token);
			tree->insertNode(token, 1);
			count++;
		}
	}
	printf("~~~ %d개의 레코드가 성공적으로 추가되었습니다.\n", count);
	fclose(fp);
}

void convert_to_lower(char *token)
{
	for (int i = 0; token[i] != '\0'; i++) {
		if (isupper(token[i]))
			token[i] = 'a' + token[i] - 'A';
	}
}

void print_tree(BST<string, int> *tree)
{
	ofstream fp;
	char fname[50];

	printf("출력 파일 이름? ");
	gets_s(fname);
	fp.open(fname, ios::out);
	if (!fp) {
		printf("File open error at print_tree\n");
	}

	tree->printTree(fp);
	fp.close();
}