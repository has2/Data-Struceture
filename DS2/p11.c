#include <string.h> 
#include <stdio.h> 
#include <stdlib.h>

#define KEY_SIZE 10 // 탐색키의 최대길이 
#define TABLE_SIZE 13 // 해싱 테이블의 크기=소수 
#define equal(e1,e2) (!strcmp(e1.key,e2.key)) 

typedef struct { 
	char key[KEY_SIZE]; // 다른 필요한 필드들 
} element; 

struct list { 
	element item; 
	struct list *link; 
}; struct list *hash_table[TABLE_SIZE];

void hash_chain_print(struct list *ht[]) { 
	struct list *node; 
	int i; 
	for (i = 0; i<TABLE_SIZE; i++) { 
		printf("[%d] ->", i); 
		for (node = ht[i]; node; node = node->link) { 
			printf("%s->", node->item.key); 
		} 
		printf("\n"); } 
}

// 문자로 된 탐색키를 숫자로 변환 
int transform(char *key) { 
	int number=0; // 간단한 덧셈 방식 사용 자연수 생성 
	while(*key) number += *(key++); 
	return number; 
} 

// 제산 함수를 사용한 해싱 함수 
int hash_function(char *key) { 
	// 키를 자연수로 변환한 다음 테이블의 크기로 나누어 나머지를 반환 
	return transform(key) % TABLE_SIZE; 
}

void hash_chain_add(element item, struct list *ht[]) { 
	//0. 우측의 설명 
	int hash_value = hash_function(item.key); 
	struct list *ptr; 
	struct list *node_before=NULL, *node = ht[hash_value]; 
	//1. 우측의 설명 
	for(; node; node_before=node, node=node->link){ 
		if(equal(node->item, item)){ 
			printf("이미 탐색키가 저장되어 있음\n"); 
			return; } 
	} 
	
	//2. fill inthe blank 
	ptr = (struct list*)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;


}

void main() { 
	element tmp; 
	strcpy(tmp.key, "a"); 
	hash_chain_add(tmp, hash_table); 
	strcpy(tmp.key, "b"); 
	hash_chain_add(tmp, hash_table); 
	strcpy(tmp.key, "c"); 
	hash_chain_add(tmp, hash_table); 
	strcpy(tmp.key, "d"); 
	hash_chain_add(tmp, hash_table);
	strcpy(tmp.key, "e");
	hash_chain_add(tmp, hash_table);
	hash_chain_print(hash_table); 
}
