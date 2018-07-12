#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef char ElementType;

typedef struct BinNode
{
	ElementType data;
	struct BinNode *left, *right;
}*SearchTree;

void insert(SearchTree tree, ElementType x);

/* 构建一颗二叉搜索树   碰到0时认为输入结束*/
void CreateSearchTree(SearchTree *tree, const ElementType *data)
{
	SearchTree tmp, last;
	int i = 0, flag = 0;
	if (*tree == NULL && data[i] != '\0')
	{
		*tree = (SearchTree)malloc(sizeof(struct BinNode));
		(*tree)->left = (*tree)->right = NULL;
		(*tree)->data = data[i ++];
	}
	while (data[i] != '\0')
	{
		insert(*tree, data[i]);
		i ++;
	}
}

SearchTree findWithRecursive(SearchTree tree, ElementType x, int times)
{
	times ++;
	if (tree->data < x)
	{
		return findWithRecursive(tree -> right, x, times);
	}
	else if (tree->data > x)
	{
		return findWithRecursive(tree -> left, x, times);
	}
	else
	{
		printf("查找元素为%c的节点,判断次数:%d(递归方式)\n", x, times);
		return tree;
	}
	return NULL;
}

SearchTree find(SearchTree tree, ElementType x)
{
	int times = 0;
	while (tree)
	{
		times ++;
		if (tree->data < x)
		{
			tree = tree -> right;
		}
		else if (tree->data > x)
		{
			tree = tree -> left;
		}
		else
		{
			printf("查找元素为%c的节点,判断次数:%d\n", x, times);
			return tree;
		}
	}
	return NULL;
}

SearchTree insertWithRecursive(SearchTree tree, ElementType x)
{
	if (!tree)
	{
		tree = (SearchTree)malloc(sizeof(struct BinNode));
		tree->data = x;
		tree->left = tree->right = NULL;
		return tree;
	}
	else if (tree->data < x)
	{
		tree->right = insertWithRecursive(tree->right, x);
	}
	else if (tree->data > x)
	{
		tree->left = insertWithRecursive(tree->left, x);
	}
	return tree;
	/* else X已经存在，什么都不做 */
}

void insert(SearchTree tree, ElementType x)
{
	SearchTree tmp, last; // last:记录插入位置的父节点
	int flag = 0;// flag:为1时表示应该插入在左边,为2时表示应该插入到右边
	tmp = tree;
	while (tmp)
	{
		last = tmp;
		// 找到节点应该插入的位置并生成节点插入
		if (tmp->data > x)
		{
			tmp = last->left;
			flag = 1;
		}
		else if (tmp->data < x)
		{
			tmp = last->right;
			flag = 2;
		}
		else
		{
			// 相等时将flag置0,不处理即可
			flag = 0;
			tmp = NULL;
		}
	}
	if (flag)
	{
		tmp = (SearchTree)malloc(sizeof(struct BinNode));
		tmp->data = x;
		tmp->left = tmp->right = NULL;
		if (flag == 1)
		{
			last->left = tmp;
		}
		else if (flag == 2)
		{
			last->right = tmp;
		}
	}
}

ElementType findMinWithRecursive(SearchTree tree)
{
	if (!tree)
	{
		return ERROR;
	}
	else if (!tree->left)
	{
		return tree->data;
	}
	else
	{
		return findMinWithRecursive(tree->left);
	}
}

ElementType findMin(SearchTree tree)
{
	SearchTree tmp = tree;
	while (tree)
	{
		tmp = tree;
		tree = tree->left;
	}
	return tmp->data;
}

ElementType findMax(SearchTree tree)
{
	SearchTree tmp = tree;
	while (tree)
	{
		tmp = tree;
		tree = tree->right;
	}
	return tmp->data;
}

ElementType findMaxWithRecursive(SearchTree tree)
{
	if (!tree)
	{
		return ERROR;
	}
	else if (!tree->right)
	{
		return tree->data;
	}
	else
	{
		return findMaxWithRecursive(tree->right);
	}
}

SearchTree deleteWithRecursive(SearchTree tree, ElementType x)
{
	SearchTree tmp;
	if (!tree){}
	else if (x < tree->data)
	{
		tree->left = deleteWithRecursive(tree->left,x);
	}
	else if (x > tree->data)
	{
		tree->right = deleteWithRecursive(tree->right,x);
	}
	else
	{
		if (tree->left && tree->right)
		{
			tree->data = findMax(tree->left);
			tree->left = deleteWithRecursive(tree->left, tree->data);
		}
		else 
		{
			tmp = tree;
			if (tree->left)
			{
				tree = tree->left;
			}
			else
			{
				tree = tree->right;
			}
			free(tmp);
		}
		
	}
	return tree;
}

int delete(SearchTree tree, ElementType x)
{
	SearchTree tmp = tree, last;
	// 找到值为x的节点和其父节点
	while (tmp)
	{
		if (tmp->data < x)
		{
			last = tmp;
			tmp = tmp -> right;
		}
		else if (tmp->data > x)
		{
			last = tmp;
			tmp = tmp -> left;
		}
		else
		{
			// 找到了，退出当前循环
			break;
		}
	}
	// 没找到
	if (!tmp)
	{
		return ERROR;
	}
	else if (!tmp->left && !tmp->right)
	{
		// 要删除的节点没有子节点,直接删除自己,并将父节点指向自己的指针改为NULL
		putchar(last->data);
		last->left = tmp == last->left ? NULL : last->left;
		last->right = tmp == last->right ? NULL : last->right;
		free(tmp);
		tmp = NULL;
	}
	else if (tmp->left && tmp->right)
	{
		// 要删除的节点有左右两个子节点
		// 把当前节点的值改为左子树中的最大值,或右子树中的最小值,并把原有的最大/最小值节点删除
		tmp->data = findMin(tmp->right);
		delete(tmp->right, tmp->data);
	}
	else if (tmp->left)
	{
		// 只有左节点,将其父节点指向当前节点的左指针,释放当前节点
		last->left = tmp == last->left ? tmp->left : last->left;
		last->right = tmp == last->right ? tmp->left : last->right;
		free(tmp);
		tmp = NULL;
	}
	else
	{
		// 只有右节点
		last->left = tmp == last->left ? tmp->right : last->left;
		last->right = tmp == last->right ? tmp->right : last->right;
		free(tmp);
		tmp = NULL;
	}
	return OK;
}

void PreOrderTraverse(SearchTree tree)
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

int modify(SearchTree tree,ElementType origin,ElementType target)
{
	if(delete(tree,origin))
	{
		insert(tree,target);
	}
}

int main(int argc, char const *argv[])
{
	char *input = "CABDDE";
	SearchTree tree = NULL;
	// CABDE
	//     C
	// A       D
	//   B       E
	CreateSearchTree(&tree, input);
	puts("前序遍历树:");
	PreOrderTraverse(tree);
	puts("");

	find(tree, 'C');
	find(tree, 'A');
	find(tree, 'D');
	find(tree, 'B');

	findWithRecursive(tree, 'C', 0);
	findWithRecursive(tree, 'A', 0);
	findWithRecursive(tree, 'D', 0);
	findWithRecursive(tree, 'B', 0);

	input = "IBEFOLU";
	//     I
	// B          O
	//  E      L     U
	//   F
	tree = NULL;
	CreateSearchTree(&tree, input);
	puts("构建新树后,前序遍历树:");
	PreOrderTraverse(tree);
	puts("");

	//     I
	// B          O
	//  E      L     U
	//   F   M  N  S  W
	insert(tree, 'M');
	insert(tree, 'N');

	insertWithRecursive(tree, 'S');
	insertWithRecursive(tree, 'W');

	puts("插入元素MNSW后,前序遍历如下:");
	PreOrderTraverse(tree);
	puts("");

	printf("树中的最小元素为%c\n", findMin(tree));
	printf("树中的最小元素为%c(递归方式)\n", findMinWithRecursive(tree));

	printf("树中的最大元素为%c\n", findMax(tree));
	printf("树中的最大元素为%c(递归方式)\n", findMaxWithRecursive(tree));

	delete(tree, 'F');
	puts("删除节点F后:");
	PreOrderTraverse(tree);
	puts("");

	delete(tree, 'B');
	puts("删除节点B后:");
	PreOrderTraverse(tree);
	puts("");

	delete(tree, 'O');
	puts("删除节点O后:");
	PreOrderTraverse(tree);
	puts("");

	deleteWithRecursive(tree, 'N');
	puts("删除节点N后:");
	PreOrderTraverse(tree);
	puts("");

	deleteWithRecursive(tree, 'L');
	puts("删除节点L后:");
	PreOrderTraverse(tree);
	puts("");

	deleteWithRecursive(tree, 'S');
	puts("删除节点S后:");
	PreOrderTraverse(tree);
	puts("");

	modify(tree,'M','F');
	puts("将M改为F后:");
	PreOrderTraverse(tree);
	puts("");

	return 0;
}
