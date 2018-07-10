#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef char ElementType;

typedef struct BinNode
{
	ElementType data;
	struct BinNode *left, *right;
}*BinTree;

int i = 0;

int InitTree(BinTree *tree)
{
	*tree = NULL;
	return OK;
}

/*
  按前序输入二叉树中结点的值（一个字符）
  0表示空树，构造二叉链表表示二叉树T。
  */
void FillTree(BinTree *tree, const ElementType *data)
{
	if (data[i] == '0')
	{
		*tree = NULL;
		i ++;
	}
	else
	{
		*tree = (BinTree)malloc(sizeof(struct BinNode));
		(*tree)->data = data[i];
		i ++;
		FillTree(&(*tree)->left, data);
		FillTree(&(*tree)->right, data);
	}
}

void ClearTree(BinTree *tree)
{ 
	if (!*tree)
	{
		return;
	}
	ClearTree(&(*tree)->left);
	ClearTree(&(*tree)->right);
	free(*tree);
	*tree = NULL;//这一步必须要
}

int BinTreeEmpty(BinTree tree)
{
	return tree == NULL;
}

int BiTreeDepth(BinTree tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	int leftDepth = BiTreeDepth(tree->left);
	int rightDepth = BiTreeDepth(tree->right);
	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;//加1表示当前层
}


int Assign(BinTree tree,ElementType value)
{
	if(!tree)
	{
		return ERROR;
	}
	tree->data = value;
	return OK;
}

void PreOrderTraverse(BinTree tree)
{
	// 这里的!=NULL可以去掉
	if (tree != NULL)
	{
		// 先打印
		putchar(tree->data);
		// 遍历左子树
		PreOrderTraverse(tree->left);
		// 遍历右子树
		PreOrderTraverse(tree->right);
	}
}

void InOrderTraverse(BinTree tree)
{
	if (tree)
	{
		InOrderTraverse(tree->left);
		putchar(tree->data);
		InOrderTraverse(tree->right);
	}
}

void PostOrderTraverse(BinTree tree)
{
	if (tree)
	{
		PostOrderTraverse(tree->left);
		PostOrderTraverse(tree->right);
		putchar(tree->data);
	}
}

/* 层序遍历二叉树 
   使用队列实现
*/
void LevelOrderTraverse(BinTree tree)
{
	struct
	{
		BinTree *data[100];
		int front;
		int rear;
	} queue;
	queue.front = queue.rear = 0;
	while (tree != NULL)
	{
		if (tree != NULL)
		{
			putchar(tree->data);
		}
		if (tree->left != NULL)
		{
			queue.data[queue.rear++] = tree->left;
		}
		if (tree->right != NULL)
		{
			queue.data[queue.rear++] = tree->right;
		}
		tree = queue.data[queue.front ++];
	}
}

int main(int argc, char **argv)
{
	struct BinNode node;

	int status;
	BinTree tree;
	ElementType *data;

	puts("init tree");
	InitTree(&tree);
	printf("is binary tree empty?\n%d\n", BinTreeEmpty(tree));

	// 这里缺失的节点必须要用0表示,不然无法通过单独的一个前序或后续遍历来确定一个二叉树
	// 可以通过中序遍历和前/后遍历(其中一个)来唯一确定一颗二叉树
	data = "ABDH0K000E00CFI000G0J00";
	// 				A
	// 		 B				C
	// 	  D		E		F		G
	// H			  I			  J
	// 	 K
	FillTree(&tree, data);
	printf("using data:\t%s\tto fill tree\n", data);

	printf("建立二叉树后,树空否？%d 树的深度=%d\n", BinTreeEmpty(tree), BiTreeDepth(tree));

	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(tree);
	puts("");

	printf("前序遍历二叉树:\n");
	PreOrderTraverse(tree);
	puts("");

	printf("中序遍历二叉树:\n");
	InOrderTraverse(tree);
	puts("");

	printf("后序遍历二叉树:\n");
	PostOrderTraverse(tree);
	puts("");

	ClearTree(&tree);
	printf("清除二叉树后 is binary tree empty?\n%d\n", BinTreeEmpty(tree));

	return 0;
}