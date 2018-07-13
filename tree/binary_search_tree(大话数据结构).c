#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;

typedef  struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


/* 递归查找二叉排序树T中是否存在key, */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) 
{  
	if (!T)
	{
		*p = f;  
		return FALSE; 
	}
	else if (key==T->data)
	{
		*p = T;  
		return TRUE; 
	}
	else if (key<T->data) 
		return SearchBST(T->lchild, key, T, p);
	else  
		return SearchBST(T->rchild, key, T, p);
}

Status InsertBST(BiTree *T, int key)
{
	BiTree p,s;
	if (!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if(!p)
			*T = s;
		else if (key<p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else
		return FALSE;  /*  树中已有关键字相同的结点，不再插入 */
}

/* 	删除指定节点
	这里使用二级指针,使得程序简洁了不少,但是稍许难以理解 
*/
Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild==NULL)
	{
		q=*p; *p=(*p)->lchild; free(q);
	}
	else if((*p)->lchild==NULL)
	{
		q=*p; *p=(*p)->rchild; free(q);
	}
	else /* 左右子树均不空 */
	{
		q=*p; s=(*p)->lchild;
		while(s->rchild)
		{
			q=s;
			s=s->rchild;
		}
		(*p)->data=s->data;
		if(q!=*p)
			q->rchild=s->lchild;
		else
			q->lchild=s->lchild;
		free(s);
	}
	return TRUE;
}

/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点, */
Status DeleteBST(BiTree *T,int key)
{
	if(!*T) /* 不存在关键字等于key的数据元素 */ 
		return FALSE;
	else
	{
		if (key==(*T)->data) /* 找到关键字等于key的数据元素 */ 
			return Delete(T);
		else if (key<(*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else
			return DeleteBST(&(*T)->rchild,key);
	}
}

/* 中序遍历二叉树,结果将从小到大显示 */
void InOrderTraverse(BiTree tree)
{
	if (tree)
	{
		InOrderTraverse(tree->lchild);
		printf("%d\t",tree->data);
		InOrderTraverse(tree->rchild);
	}
}

int main(void)
{
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T=NULL;
	
	for(i=0;i<10;i++)
	{
		InsertBST(&T, a[i]);
	}

	puts("插入数据后,中序遍历树:");
	InOrderTraverse(T);
	puts("");

	DeleteBST(&T,93);
	puts("删除数据93后,中序遍历树:");
	InOrderTraverse(T);
	puts("");

	DeleteBST(&T,47);
	puts("删除数据47后,中序遍历树:");
	InOrderTraverse(T);
	puts("");

	return 0;
}
