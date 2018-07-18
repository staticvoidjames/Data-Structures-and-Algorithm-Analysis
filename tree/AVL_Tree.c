#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define LH 1  /*  左高 */
#define EH 0  /*  等高 */
#define RH -1 /*  右高 */

typedef char ElementType;
typedef int Boolean;

/*  本例子中的代码借鉴了《大话数据结构》中的平衡二叉树的代码,其解法可以说是体现了平衡二叉树的本质定义:
    在平衡二叉树中，任意一个节点的左右子树的高度差的绝对值<2,也就有3中可能,-1,0,1
    添加一个节点时，新添加的节点平衡因子为0，这时候只需要检查新添加的节点到根节点的路径上是否存在bf==2,-2的情况,
    在计算一个节点的bf值时，需要知道3点:
    1.之前保存的bf值。通过结构体内的bf值得到。
    2.插入元素位于当前元素的哪个子树上。通过之前插入一个元素时的路径可以得到。
    3.该子树在插入后有没有长高。这个在插入元素之后,往根节点的路径上,每碰到一个节点都需要进行一次判断,并计算其最新的bf值

    该例子中的所有旋转的命名都是参考中国大学MOOC《数据结构》课程中对于平衡二叉树的命名:LL旋转、LR旋转、RL旋转和RR旋转
    《大话数据结构》和网络上的一些博客可能对旋转有不同的命名和区分

    建议参考《大话数据结构》版本代码，其中将双旋转分解给两个单旋转的思路很值得学习

    "均衡,存乎万物之间"     ----暗影之拳  阿卡丽
*/

typedef struct BinNode
{
    ElementType data;
    int bf; /* balance factor:平衡因子*/
    struct BinNode *left, *right;
} BinNode, *AVLTree;

// LL旋转
void ll_rotate(AVLTree *tree)
{
    AVLTree l = (*tree)->left;
    // 调平衡因子
    (*tree)->bf = l->bf = EH;
    (*tree)->left = l->right; /*  l的右子树挂接为tree的左子树 */
    l->right = *tree;
    *tree = l; /*  tree指向新的根结点 */
}

// LR旋转
void lr_rotate(AVLTree *tree)
{
    AVLTree l = (*tree)->left;
    AVLTree lr = l->right;

    switch (lr->bf)
    {
    // 最后的LR旋转步骤其实是一致的,但是这里lr节点的bf值的不同会导致在旋转完成后,
    // 被旋转的节点的bf因子不同
    case LH:
        (*tree)->bf = RH;
        l->bf = EH;
        lr->bf = EH;
        break;

    case EH:
        (*tree)->bf = l->bf = lr->bf = EH;
        break;

    case RH:
        (*tree)->bf = EH;
        l->bf = LH;
        lr->bf = EH;
        break;
    }
    (*tree)->left = lr->right;
    l->right = lr->left;
    lr->left = l;
    lr->right = (*tree);
    *tree = lr;
}

void left_balance(AVLTree *tree)
{
    // 进入到这里就证明了(*tree)->bf = 2
    AVLTree l;
    // 接下来判断插入的位置是在左子树的哪边
    l = (*tree)->left;
    switch (l->bf)
    {
    case LH:
        // 插入在左子树的左子树上,做LL旋转
        ll_rotate(tree);
        break;

    case RH:
        // 插入在左子树的右子树上,做LR旋转
        lr_rotate(tree);
        break;
    }
}

void rr_rotate(AVLTree *tree)
{
    AVLTree r = (*tree)->right;
    // 调平衡因子
    (*tree)->bf = r->bf = EH;
    (*tree)->right = r->left;
    r->left = *tree;
    *tree = r;
}

// RL旋转
void rl_rotate(AVLTree *tree)
{
    AVLTree r = (*tree)->right;
    AVLTree rl = r->left;
    switch (rl->bf)
    {
    case LH:
        (*tree)->bf = EH;
        r->bf = RH;
        rl->bf = EH;
        break;

    case EH:
        (*tree)->bf = r->bf = rl->bf = EH;
        break;

    case RH:
        (*tree)->bf = LH;
        r->bf = EH;
        rl->bf = EH;
        break;
    }
    r->left = rl->right;
    (*tree)->right = rl->left;
    rl->left = (*tree);
    rl->right = r;
    *tree = rl;
}

void right_balance(AVLTree *tree)
{
    AVLTree r, rl;
    r = (*tree)->right;
    switch (r->bf)
    {
    case LH:
        rl_rotate(tree);
        break;

    case RH:
        rr_rotate(tree);
        break;
    }
}

int InsertAVL(AVLTree *tree, ElementType x, Boolean *taller)
{
    if (!*tree)
    {
        *tree = (AVLTree)malloc(sizeof(BinNode));
        (*tree)->data = x;
        (*tree)->left = (*tree)->right = NULL;
        (*tree)->bf = EH;
        *taller = TRUE;
        return OK;
    }
    else
    {
        // 已经存在了，就没有必要处理了
        if ((*tree)->data == x)
        {
            *taller = FALSE;
            return FALSE;
        }
        else if (x < (*tree)->data)
        {
            // 插入都失败了，也就是插入的元素原来就有了，也就没必要判断bf值等等了，树根本就没有变化
            if (!InsertAVL(&(*tree)->left, x, taller))
            {
                return FALSE;
            }
            // 在插入之后,对应的子树(这里是左子树)长高了，重新计算bf值
            if (*taller)
            {
                switch ((*tree)->bf)
                {
                case LH:
                    // 原来左边高，这里左子树还长高了，所以这里的bf值就是2了，需要做左平衡
                    left_balance(tree);
                    *taller = FALSE;
                    break;

                case EH:
                    // 原来左右高度相同,这里bf值就为1(LH)了
                    (*tree)->bf = LH;
                    // 对于当前节点的父节点来说，其当前子树长高
                    *taller = TRUE;
                    break;

                case RH:
                    // 原来右边高,现在左右高度一致了
                    (*tree)->bf = EH;
                    // 对于当前节点的父节点来说，其当前子树没有长高
                    *taller = FALSE;
                    break;
                }
            }
        }
        else
        {
            if (!InsertAVL(&(*tree)->right, x, taller))
            {
                return FALSE;
            }
            if (*taller)
            {
                switch ((*tree)->bf)
                {
                case LH:
                    (*tree)->bf = EH;
                    *taller = FALSE;
                    break;

                case EH:
                    (*tree)->bf = RH;
                    *taller = TRUE;
                    break;

                case RH:
                    right_balance(tree);
                    break;
                }
            }
        }
    }
    return OK;
}

void InOrderTraverse(AVLTree tree)
{
    if (tree)
    {
        InOrderTraverse(tree->left);
        putchar(tree->data);
        InOrderTraverse(tree->right);
    }
}

void PreOrderTraverse(AVLTree tree)
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

int main(int argc, char const *argv[])
{
    AVLTree tree = NULL;
    Boolean taller;
    // 通过中序遍历和前/后序遍历中的一个可以唯一地确定一颗二叉树
    InsertAVL(&tree, 'A', &taller);
    InsertAVL(&tree, 'B', &taller);
    InsertAVL(&tree, 'C', &taller);
    printf("按ABC(RR旋转)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    tree = NULL;
    InsertAVL(&tree, 'C', &taller);
    InsertAVL(&tree, 'B', &taller);
    InsertAVL(&tree, 'A', &taller);
    printf("按CBA(LL旋转)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    tree = NULL;
    InsertAVL(&tree, 'I', &taller);
    InsertAVL(&tree, 'C', &taller);
    InsertAVL(&tree, 'F', &taller);
    printf("按ICF(LR旋转时lr->bf = EH)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    tree = NULL;
    InsertAVL(&tree, 'I', &taller);
    InsertAVL(&tree, 'J', &taller);
    InsertAVL(&tree, 'C', &taller);
    InsertAVL(&tree, 'B', &taller);
    InsertAVL(&tree, 'F', &taller);
    InsertAVL(&tree, 'E', &taller);
    printf("按IJCBFE(LR旋转时lr->bf = LH)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    tree = NULL;
    InsertAVL(&tree, 'I', &taller);
    InsertAVL(&tree, 'J', &taller);
    InsertAVL(&tree, 'C', &taller);
    InsertAVL(&tree, 'B', &taller);
    InsertAVL(&tree, 'F', &taller);
    InsertAVL(&tree, 'H', &taller);
    printf("按IJCBFH(LR旋转时lr->bf = RH)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    tree = NULL;
    InsertAVL(&tree, 'E', &taller);
    InsertAVL(&tree, 'J', &taller);
    InsertAVL(&tree, 'H', &taller);
    printf("按EJH(RL旋转时rl->bf = EH)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    tree = NULL;
    InsertAVL(&tree, 'E', &taller);
    InsertAVL(&tree, 'D', &taller);
    InsertAVL(&tree, 'J', &taller);
    InsertAVL(&tree, 'H', &taller);
    InsertAVL(&tree, 'K', &taller);
    InsertAVL(&tree, 'G', &taller);
    printf("按EDJHKG(RL旋转时rl->bf = LH)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    tree = NULL;
    InsertAVL(&tree, 'E', &taller);
    InsertAVL(&tree, 'D', &taller);
    InsertAVL(&tree, 'J', &taller);
    InsertAVL(&tree, 'H', &taller);
    InsertAVL(&tree, 'K', &taller);
    InsertAVL(&tree, 'I', &taller);
    printf("按EDJHKI(RL旋转时rl->bf = RH)插入数据,前序遍历和中序遍历分别为:\n");
    PreOrderTraverse(tree);
    puts("");
    InOrderTraverse(tree);
    puts("");

    return 0;
}
