#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef char ElementType;

typedef enum
{
	Link,
	Thread
} PointerTag;

typedef struct BinNode
{
	ElementType data;
	PointerTag ltag, rtag;
	struct BinNode *left, *right;
} *BinTree;

BinTree pre = NULL;
int i = 0;

/*
  按前序输入二叉树中结点的值（一个字符）
  0表示空树，构造二叉链表表示二叉树T。
  */
void FillTree(BinTree *tree, const ElementType *data)
{
	if (data[i] == '0')
	{
		*tree = NULL;
		i++;
	}
	else
	{
		*tree = (BinTree)malloc(sizeof(struct BinNode));
		(*tree)->data = data[i];
		i++;
		FillTree(&(*tree)->left, data);
		if ((*tree)->left)
		{
			(*tree)->ltag = Link;
		}
		FillTree(&(*tree)->right, data);
		if ((*tree)->right)
		{
			(*tree)->rtag = Link;
		}
	}
}

void in_threading(BinTree tree)
{
	if(tree)
	{
		in_threading(tree->left);
		if(!tree->left)
		{
			tree->ltag = Thread;
			tree->left = pre;
		}
		if(!pre->right)
		{
			pre->rtag = Thread;
			pre->right = tree;
		}
		pre = tree;

		in_threading(tree->right);
	}
}

// 中序遍历二叉树,并将其中序线索化,head指向线索化的头结点
// 其最后结果可以参考附件:中序遍历线索化.png
void in_order_threading(BinTree *head, BinTree tree)
{
	// 生成头结点
	*head = (BinTree)malloc(sizeof(struct BinNode));
	(*head)->ltag = Link;
	(*head)->rtag = Thread;
	(*head)->right = *head;

	if(!tree)  // 树为空
	{
		(*head)->left = *head;
	}
	else
	{
		// 头结点的left指向树的根节点
		(*head)->left = tree;
		// 中序遍历的第一个节点的left指向头结点
		pre = *head;

		in_threading(tree);

		// 中序遍历的最后一个节点的right指向头结点
		pre->right = *head;
		pre->rtag = Thread;
		// 头结点的right指向中序遍历的最后一个节点
		(*head)->right = pre;
	}
}

// 线索二叉树的遍历相关
// my heart has broken
void in_order_traverse(BinTree head)
{
	BinTree p;
	p = head->left;

	while(p != head)
	{
		while(p->ltag == Link)
		{
			p = p->left;
		}
		putchar(p->data);
		while(p->rtag == Thread && p->right != head)
		{
			p = p->right;
			putchar(p->data);
		}
		p = p->right;
	}
	puts("");
}

int main(int argc, char **argv)
{
	struct BinNode node;

	int status;
	BinTree tree,head;
	// 这里缺失的节点必须要用0表示,不然无法通过单独的一个前序或后续遍历来确定一个二叉树
	// 可以通过中序遍历和前/后遍历(其中一个)来唯一确定一颗二叉树
	// 				 A
	// 		 B				C
	// 	  D		  E		F		G
	// H	I  J
	ElementType *data = "ABDH00I00EJ000CF00G00";

	FillTree(&tree, data);
	
	in_order_threading(&head, tree);

	printf("中序遍历(输出)二叉线索树:\n");

	in_order_traverse(head);
	return 0;
}
