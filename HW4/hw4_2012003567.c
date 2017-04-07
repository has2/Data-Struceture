#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef int element;
typedef struct _TreeNode
{
	element data;
	struct _TreeNode * left;
	struct _TreeNode * right;
} TreeNode;

TreeNode * createTreeNode(void)
{
	TreeNode * node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = NULL;
	node->right = NULL;
	return node;
}

void setData(TreeNode * node, element data)
{
	node->data = data;
}

element getData(TreeNode * node)
{
	return node->data;
}

void makeLeftSubTree(TreeNode * main, TreeNode * sub)
{
	if (main->left == NULL) {
		main->left = sub;
		return;
	}
	exit(1);
}

void makeRightSubTree(TreeNode * main, TreeNode * sub)
{
	if (main->right == NULL) {
		main->right = sub;
		return;
	}
	exit(1);
}

TreeNode * getLeftSubTree(TreeNode * node)
{
	return node->left;
}

TreeNode * getRightSubTree(TreeNode * node)
{
	return node->right;
}

void printInorder(TreeNode *root) {
	if (root != NULL) {
		printInorder(root->left);    // 1. left child 방문
		printf("%d ", root->data);   // 2. root 방문
		printInorder(root->right);   // 3. right child 방문
	}
}
void printPreorder(TreeNode *root) {
	if (root != NULL) {
		printf("%d ", root->data);   // 1. root 방문
		printPreorder(root->left);   // 2. left child 방문
		printPreorder(root->right);  // 3. right child 방문
	}
}
void printPostorder(TreeNode *root) {
	if (root != NULL) {
		
		printPostorder(root->left);  // 1. left child 방문
		printPostorder(root->right); // 2. right child 방문
		printf("%d ", root->data);   // 3. root 방문

		
	}
}
int main(int argc, char *argv[]) {
	FILE *input;
	input = fopen("input.txt", "r");
	char command;

	//노드 만들기
	TreeNode * t1 = createTreeNode();
	setData(t1, 54);
	TreeNode * t2 = createTreeNode();
	setData(t2, 27);
	TreeNode * t3 = createTreeNode();
	setData(t3, 89);
	TreeNode * t4 = createTreeNode();
	setData(t4, 13);
	TreeNode * t5 = createTreeNode();
	setData(t5, 44);
	TreeNode * t6 = createTreeNode();
	setData(t6, 71);
	TreeNode * t7 = createTreeNode();
	setData(t7, 92);
	TreeNode * t8 = createTreeNode();
	setData(t8, 1);
	TreeNode * t9 = createTreeNode();
	setData(t9, 37);
	TreeNode * t10 = createTreeNode();
	setData(t10, 64);
	
	//노드를 붙혀서 트리 만들기
	makeLeftSubTree(t1, t2);
	makeLeftSubTree(t2, t4);
	makeLeftSubTree(t4, t8);
	makeRightSubTree(t2, t5);
	makeLeftSubTree(t5, t9);
	makeRightSubTree(t1, t3);
	makeLeftSubTree(t3, t6);
	makeLeftSubTree(t6, t10);
	makeRightSubTree(t3, t7);


	if (argc == 1)
		input = fopen("input.txt", "r");
	else
		input = fopen(argv[1], "r");


	while (1) {
		command = fgetc(input);
		if (feof(input)) break;

		switch (command) {
		case 'i': printf("Inorder:   "); printInorder(t1); printf("\n");
			break;
		case 'r': printf("Preorder:  "); printPreorder(t1); printf("\n");
			break;
		case 'o': printf("Postorder: "); printPostorder(t1); printf("\n");
			break;
		default:
			break;
		}
	}
	

	fclose(input);
	return 0;
}

