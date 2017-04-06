#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *search(TreeNode *node, int key) { 

	TreeNode* cur = node;

	while (cur != NULL) {
		if (cur->key == key)
			return cur;
		else if (cur->key < key)
			cur = cur->right;
		else if (cur->key > key)
			cur = cur->left;
	}

	return NULL;

}

void insert_node(TreeNode **root, int key) {
	TreeNode *p, *q; 
	TreeNode *n; 
	
	p = *root; 
	q = NULL; 

	while (p != NULL)
	{
		if (key == p->key) return;
		q = p;
		if (p->key > key)
			p = p->left;
		else 
			p = p->right;
	}

	n = (TreeNode*)malloc(sizeof(TreeNode));
	n->key = key; n->left = n->right = NULL;

	if (q == NULL)
		*root = n;
	else {
		if (key > q->key)
			q->right = n;
		else
			q->left = n;
	}
}

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

int find_right_min(TreeNode *node) {
	TreeNode* cur = node->right;
	int min = cur->key;
	while (cur != NULL)
	{
		min = cur->key;
		cur = cur->left;
	}

	return min;
}

TreeNode* delete_node(TreeNode *root, int key)
{
	if (root == NULL) {
		printf("not exist\n");
		return root;
	}

	if (root->key > key)
		root->left  = delete_node(root->left, key);
	else if (root->key < key)
		root->right = delete_node(root->right, key);
	else {

		if (root->left&&root->right) {
			int right_min = find_right_min(root);
			root->key = right_min;
			root->right = delete_node(root->right, right_min);
		}
		else {
			TreeNode* tmp = root;
			root = root->right == NULL ? root->left : root->right;
			free(tmp);
		}
	}

	return root;
}

void main()
{
	TreeNode *root = NULL;
	TreeNode *tmp;
	insert_node(&root, 3);
	insert_node(&root, 2);
	insert_node(&root, 5);
	insert_node(&root, 1);
	insert_node(&root, 4);


	if (search(root, 5) != NULL)
		printf("search success: %d\n", search(root, 5)->key);
	delete_node(root, 3);
	display(root);
	tmp = search(root, 3);
	if (tmp != NULL) printf("탐색성공:%d\n", tmp->key);
}

