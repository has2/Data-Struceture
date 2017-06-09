#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define KEY_SIZE	20	// 탐색키의 최대길이  
#define TABLE_SIZE	7	// 해싱 테이블의 크기 
#define equal(e1,e2) (!strcmp(e1.key,e2.key))

typedef struct
{
	char key[KEY_SIZE];
} element;

struct list
{
	element item;
	struct list *link;
};
struct list *hash_table[TABLE_SIZE];

int transform(char* key);
///////숙제로 구현할 코드/////////////
int hash_function(char *key)
{
	int num = transform(key); // 숫자로 변환 
	int i, j;
	num *= num; // 제곱
	char binary[32]; // 2진수를 저장할 배열

	// 2진수로 변환
	for (i = 0; num > 0; i++) {
		binary[i] = num % 2;
		num /= 2;
	}

	// 2진수 출력
	for (j = i - 1; j >= 0; j--)
		printf("%d", binary[j]);

	// key값 출력
	printf("\tkey : %d %d %d\n", binary[i - i / 2], binary[i - i / 2 - 1], binary[i - i / 2 - 2]);
    
	return 4 * binary[i - i / 2] + 2 * binary[i - i / 2 - 1] + binary[i - i / 2 - 2];
}

void hash_chain_find(element item, struct list *ht[])
{
	//fill in the blank
	int hash_value = hash_function(item.key);
	struct list *node = ht[hash_value];
	for (; node; node = node->link) {
		if (equal(node->item, item)) {
			printf("키를 찾았음(item.key: %s)\n", item.key);
			return;
		}
	}
	
	printf("키를 찾지못했음(item.key: %s)\n", item.key);
	return;
}
////숙제로 구현할 코드:END////////////

////////실습시간에 다룬 코드(완성된 상태)//////////
void hash_chain_print(struct list *ht[])
{
	struct list *node;
	int i;
	for (i = 0; i<TABLE_SIZE; i++) {
		printf("[%d] ->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%s->", node->item.key);
		}
		printf("\n");
	}
}

// 문자로 된 탐색키를 숫자로 변환
int transform(char *key)
{
	int number = 0;
	// 간단한 덧셈 방식 사용 자연수 생성
	while (*key) number += *(key++);
	return number;
}

void hash_chain_add(element item, struct list *ht[])
{
	int hash_value = hash_function(item.key);
	struct list *ptr;
	struct list *node_before = NULL, *node = ht[hash_value];
	for (; node; node_before = node, node = node->link) {
		if (equal(node->item, item)) {
			printf("input err\n");
			return;
		}
	}

	ptr = (struct list *)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before) node_before->link = ptr;
	else ht[hash_value] = ptr;
}
////////실습시간에 다룬 코드(완성된 상태): END//////////

void main()
{

	FILE* f;
	element tmp;
	char input[KEY_SIZE] = " ";
	f = fopen("input.txt", "r");
	while (fscanf(f, "%s", input) != EOF) {
		strcpy(tmp.key, input);
		hash_chain_add(tmp, hash_table);
	}
	hash_chain_print(hash_table);

	strcpy(tmp.key, "x");
	hash_chain_find(tmp, hash_table);
	strcpy(tmp.key, "c");
	hash_chain_find(tmp, hash_table);
}
