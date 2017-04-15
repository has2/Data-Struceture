#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

void display(TreeNode *p)
{

	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%d", p->key);
		display(p->right);
		printf(")");
	}
}

/*
We will implement binary search tree ADT with the three main functions
using iteration: insert, delete, and search.
*/
TreeNode *search(TreeNode *node, int key)
{
	TreeNode* cur = node;

	
	while (cur != NULL) {
		// 노드의 key가 찾으려는 key와 같을 때
		if (cur->key == key)
			return cur;
		// 노드의 key가 더 작을 때 right child로 이동
		else if (cur->key < key)
			cur = cur->right;
		// 노드의 key가 더 클 때 left child로 이동
		else if (cur->key > key)
			cur = cur->left;
	}
	return NULL;

}

void insert_node(TreeNode **root, int key)
{
	TreeNode *p; // 현재 탐색중이 node를 저장	
    TreeNode *q; // parent node를 저장
	TreeNode *n;

	p = *root;   // tree의 root로 초기화
	q = NULL;   

	
	while (p != NULL)
	{
		
		if (key == p->key) return;
		q = p;	// 현재 node의 key가 다르면 parent에 현재 node를 저장

		// 현재 node의 key 값이 더 크면 left child로 감 
		if (p->key > key)
			p = p->left;
		// 현재 node의 key 값이 더 작으면 right child로 감
		else
			p = p->right;
	}

	// insert할 node 초기화
	n = (TreeNode*)malloc(sizeof(TreeNode));
	n->key = key; n->left = n->right = NULL;

	// q가 null인 경우는 root가 비어있는 경우
	if (q == NULL)
		*root = n;
	else {
		// insert하려는 key 값이 더 크면 right child에 붙혀줌
		if (key > q->key)
			q->right = n;
		else
			q->left = n;
	}
}

/* node의 right subtree중 key 값이 가장 작은 node를 반환 */
TreeNode* find_right_min(TreeNode *node) {
	TreeNode* cur = node->right;
	TreeNode* p = NULL;

	// left child가 NULL일때까지 반복
	while (cur != NULL) {
		p = cur;
		cur = cur->left;
	}
	return p;
}

/* node c의 parent node를 반환하는 함수 */
TreeNode *find_previous(TreeNode *node, TreeNode *c)
{
	if (node == c) return NULL;
	TreeNode* parent = NULL;
	TreeNode* cur = node;

	while (cur != NULL) {
		if (cur->key == c->key)
			return parent;
		else if (cur->key < c->key) {
			parent = cur;
			cur = cur->right;
		}
		else if (cur->key > c->key) {
			parent = cur;
			cur = cur->left;
		}
	}
	return NULL;
}


void delete_node(TreeNode **head, TreeNode *node, int key)
{
	TreeNode *temp,*target,*root = node; // temp : right_min node와 previous node 저장에 이용
										 // target : 현재 지울 node
										 // root : 지우려는 target을 포함한 subtree의 root

	target = search(root, key); // key의 위치

	// key가 없는 경우
	if (!target) {
		printf("key is not in the tree : %d\n", key);
		return;
	}

	while (1) {
		
		// target의 child가 left,right 둘다 있는 경우
		if (target->right && target->left) {
			temp = find_right_min(target);	// target의 right subtree중 가장 작은 key 값을 가진 node
			target->key = temp->key;		// temp의 key 값을 target으로 복사
            
            // target의 right subtre의 min이 right subtree의 root인 경우
			if (target->right == temp) {
                target->right = temp->right;
                free(temp);
				return;
			}
			root = target->right;			// 이제 target의 right subtree에서 temp를 지워야 하므로 root를 target->right로 update
			target = temp;					// target을 temp으로 update
		}

		// target의 child가 하나라도 없는경우
		else {
		
			temp = find_previous(root, target); // target의 parent node를 반환

			// 현재 지우려는 node가 root이면서 child가 없을 때
			if (temp == NULL) {
				free(root);
				*head = NULL;
				return;
			}

			// target이 temp의 right child인 경우
			if (temp->key < target->key)	
				temp->right = target->right ? target->right : target->left; // target의 right child가 존재하면 temp의 right child로 
																			// target의 right child를 붙혀주고 아닐시 left child를 붙혀줌
			else 
				temp->left = target->right ? target->right : target->left;

			free(target);
			break;
		}
	}
}


void main(int argc, char *argv[])
{
	char command;
	int key;
	FILE *input;
	TreeNode *root = NULL;

	if (argc == 1) input = fopen("input.txt", "r");
	else input = fopen(argv[1], "r");
	while (1) {
		command = fgetc(input);
		if (feof(input)) break;
		switch (command) {
		case 'i':
			fscanf(input, "%d", &key);
			insert_node(&root, key);
			break;
		case 'd':
			fscanf(input, "%d", &key);
			delete_node(&root,root, key);
			break;
		case 's':
			fscanf(input, "%d", &key);
			if (search(root, key) != NULL)printf("key is in the tree: %d\n", key);
			else printf("key is not in the tree: %d\n", key);
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		default:
			break;
		}
	}
}

