#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

#define ClearTree InitTree /* 顺序结构中,这两个函数是同样的*/

typedef int boolean;
typedef char ElementType;
typedef ElementType BinTree[MAX_TREE_SIZE + 1];

ElementType Nil = 0;

int InitTree(BinTree tree)
{
	int i;
	for (i = 0; i <= MAX_TREE_SIZE; i ++)
	{
		tree[i] = Nil;
	}
	return OK;
}

/* 按层序次序输入二叉树中结点的值(字符型), 构造顺序存储的二叉树
   在实际情况下,这里如果创建失败,可能需要考虑将已经填入的数据清空
  */
int FillTree(BinTree tree, const ElementType *data)
{
	int i = 1;
	tree[0] = Nil;
	while (data[i - 1] != '\0')
	{
		if (data[i - 1] == '0')
		{
			tree[i] = Nil;
		} else
		{
			tree[i] = data[i - 1];
		}
		// 不是头结点 && 当前节点值不为空
		// 检查其必须有父节点
		// putchar(tree[i]);
		if (i != 1 && tree[i] != Nil)
		{
			if (tree[i / 2] == Nil)
			{
				return ERROR;
			}
		}
		i ++;
	}
	while (i <= MAX_TREE_SIZE)
	{
		tree[i] = Nil;
		i ++;
	}
	return OK;
}

int BinTreeEmpty(BinTree tree)
{
	return tree[1] == Nil;
}

int BiTreeDepth(BinTree tree)
{
	int last_index, depth = 0;
	for (last_index = MAX_TREE_SIZE; last_index > 0; last_index --)
	{
		if (tree[last_index] != Nil)
		{
			break;
		}
	}
	// 一个有k层的二叉树,其节点个数n与k的关系满足2^(k-1) - 1 < n <= 2^ k - 1,所以n个节点,层数k满足log2(n+1) + 1 > k >= log2(n+1)
	while (pow(2, depth) - 1 < last_index)
	{
		depth ++;
	}
	return depth;
}

int Root(BinTree tree, ElementType *e)
{
	if (BinTreeEmpty(tree))
	{
		return ERROR;
	}
	*e = tree[1];
	return OK;
}

int Value(BinTree tree, int index, ElementType *e)
{
	if (index < 1 || index > MAX_TREE_SIZE)
	{
		return ERROR;
	}
	*e = tree[index];
	return OK;
}

int Assign(BinTree tree, int index, ElementType value)
{
	if (index < 1 || index > MAX_TREE_SIZE || (index != 1 && tree[index / 2] == Nil))
	{
		return ERROR;
	}
	tree[index] = value;
	return OK;
}

int Parent(BinTree tree, int index, ElementType *result)
{
	int i;
	// 根节点不可能有父节点
	// tree[index] == Nil保证当前节点存在,如果当前节点存在,那么气父节点肯定存在
	if (index < 2 || index > MAX_TREE_SIZE || tree[index] == Nil)
	{
		return ERROR;
	}
	*result = tree[index / 2];
	return OK;
}

int LeftChild(BinTree tree, int index, ElementType *e)
{
	// 确定当前节点和其左孩子节点存在
	if (index < 1 || index > MAX_TREE_SIZE || tree[index] == Nil || tree[2 * index] == Nil)
	{
		return ERROR;
	}
	*e = tree[2 * index];
	return OK;
}

int RightChild(BinTree tree, int index, ElementType *e)
{
	// 确定当前节点和其右孩子节点存在
	if (index < 1 || index > MAX_TREE_SIZE || tree[index] == Nil || tree[2 * index + 1] == Nil)
	{
		return ERROR;
	}
	*e = tree[2 * index + 1];
	return OK;
}

int LeftSibling(BinTree tree, int index,ElementType *e)
{
	// 根节点不可能有左兄弟
	// 当前节点必须存在且必须为右节点
	if (index < 2 || index > MAX_TREE_SIZE || tree[index] == Nil || index % 2 == 1)
	{
		return ERROR;
	}
	*e = tree[index - 1];
	return OK;
}

int RightSibling(BinTree tree, int index,ElementType *e)
{
	// 当前节点必须存在且必须为左节点
	// 其右兄弟必须存在
	if (index < 1 || index > MAX_TREE_SIZE || tree[index] == Nil || index % 2 == 0 || tree[index + 1] == Nil)
	{
		return ERROR;
	}
	*e = tree[index + 1];
	return OK;
}

/* 先序遍历 index:树的根节点序号(可以遍历子树,遍历整个树传index = 1) */
void PreOrderTraverse(BinTree tree, int index)
{
	if (tree[index] == Nil)
	{
		return;
	}
	// 先打印
	putchar(tree[index]);
	// 遍历左子树
	PreOrderTraverse(tree, 2 * index);
	// 遍历右子树
	PreOrderTraverse(tree, 2 * index + 1);
}

/* 中序遍历 index:树的根节点序号(可以遍历子树,遍历整个树传index = 1) */
void InOrderTraverse(BinTree tree, int index)
{
	if (tree[index] == Nil)
	{
		return;
	}
	InOrderTraverse(tree, 2 * index);
	putchar(tree[index]);
	InOrderTraverse(tree, 2 * index + 1);
}
/* 后序遍历 index:树的根节点序号(可以遍历子树,遍历整个树传index = 1) */
void PostOrderTraverse(BinTree tree, int index)
{
	if (tree[index] == Nil)
	{
		return;
	}
	PostOrderTraverse(tree, 2 * index);
	PostOrderTraverse(tree, 2 * index + 1);
	putchar(tree[index]);
}

/* 层序遍历二叉树 */
void LevelOrderTraverse(BinTree tree)
{
	int i;
	if (BinTreeEmpty(tree))
	{
		return;
	}
	for (i = 1; i <= MAX_TREE_SIZE; i ++)
	{
		if (tree[i] != Nil)
		{
			putchar(tree[i]);
		}
	}
}

int main(int argc, char **argv)
{
	int status;
	ElementType e, e1;
	BinTree tree;
	puts("init tree");
	InitTree(tree);
	printf("is binary tree empty?\n%d", BinTreeEmpty(tree));

	// 这里必须使用字符指针，不能使用字符数组，不然后续不能使用字符串常量赋值给字符数组
	// (data = "ABC0DE000FGHI";编译失败,data作为字符数组名时为一个指针，但是其实际为字符数组类型，存在逻辑上的不自恰)，
	// 自恰:self consistent
	ElementType *data = "AB0CDEFG";
	printf("using char array :\t  %s \tto fill tree,succeed?\n%d\n", data, FillTree(tree, data));

	puts("init tree");
	InitTree(tree);
	data = "ABC0DE000FGHI";
	// 			A
	// 	   B			  C
	//  0	  D		  E  	 0
	// 0 0  F   G   H   I

	printf("using char array :\t  %s \tto fill tree,succeed?\n %d\n", data, FillTree(tree, data));

	printf("建立二叉树后,树空否？%d 树的深度=%d\n", BinTreeEmpty(tree), BiTreeDepth(tree));

	status = Root(tree, &e);
	if (status)
		printf("二叉树的根为：%c\n", e);
	else
		printf("树空，无根\n");
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(tree);
	puts("");

	printf("前序遍历二叉树:\n");
	PreOrderTraverse(tree, 1);
	puts("");

	printf("中序遍历二叉树:\n");
	InOrderTraverse(tree, 1);
	puts("");

	printf("后序遍历二叉树:\n");
	PostOrderTraverse(tree, 1);
	puts("");

	Value(tree, 3, &e);
	printf("第3个节点的值:%c\n", e);

	e = '?';
	Assign(tree, 7, e);
	Value(tree, 7, &e);
	printf("修改后第7个节点的值:%c\n", e);

	printf("前序遍历二叉树:\n");
	PreOrderTraverse(tree, 1);
	puts("");

	Parent(tree, 6, &e);
	Value(tree, 6, &e1);
	printf("结点%c的parent为%c,左右孩子分别为", e1, e);

	LeftChild(tree, 6, &e);
	RightChild(tree, 6, &e1);
	printf("%c,%c,左右兄弟分别为", e, e1);

	LeftSibling(tree, 13,&e);
	RightSibling(tree,12, &e1);
	printf("%c,%c\n", e, e1);

	ClearTree(tree);
	printf("清除二叉树后,树空否？%d 树的深度=%d\n", BinTreeEmpty(tree), BiTreeDepth(tree));
	status = Root(tree, &e);
	if (status)
		printf("二叉树的根为：%d\n", e);
	else
		printf("树空，无根\n");

	return 0;
}