#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 这个写得有点乱,将就着看吧 */
typedef char ElementType;

typedef struct TreeNode
{
	ElementType data;
	int weight;// 当前节点的权值,如果不是叶节点,那么该值就是两个子节点权值之和(哈夫曼树只有叶节点和度为2的节点)
	struct TreeNode *left, *right; // 哈夫曼树中的每一个节点的左右节点都是一颗哈夫曼树
}*HuffmanTree;

typedef struct word_code_entry
{
	ElementType word;// 被编码的字符
	char *code;// 一个字符串,表示当前字符的编码
} word_code_entry;

typedef struct HeapNode
{
	HuffmanTree *data;// 最小堆的数据,以数组形式表示的完全二叉树
	int size;// 当前节点数量
	int capacity;// 可容纳节点数量
}*MinHeap;

// 字符及对应的编码键值对
word_code_entry code_map[127] = {{0, 0}};

/* 将以h->data[p]为根节点的完全二叉树调成一个堆 */
void PercDown(MinHeap h, int p)
{
	int target_position, child;
	HuffmanTree current_item;

	current_item = h->data[p];
	target_position = p;

	for (target_position = p; target_position << 1 <= h->size; target_position = child)
	{
		child = target_position << 1;
		if (child != h->size && h->data[child + 1]->weight < h->data[child]->weight)
		{
			child ++;
		}
		if (current_item->weight < h->data[child]->weight)
		{
			break;
		}
		h->data[target_position] = h->data[child];
	}
	h->data[target_position] = current_item;
}

void build_heap(MinHeap h)
{
	for (int i = h->size >> 1; i > 0; i --)
	{
		PercDown(h, i);
	}
}

void print_heap(MinHeap h)
{
	int i;
	for (i = 1; i <= h->size; i ++)
	{
		printf("%c\t%d\n", h->data[i]->data, h->data[i]->weight);
	}
	puts("");
}

MinHeap get_MinHeap_from_string(const ElementType *str)
{
	int length = strlen(str);
	MinHeap h;
	HuffmanTree *nodes = (HuffmanTree *)malloc((length + 1) * sizeof(HuffmanTree));
	ElementType tmp;
	int size = 0;
	nodes[0] = (HuffmanTree)malloc(sizeof(struct TreeNode));
	nodes[0]->data = 0;// 最小值
	nodes[0]->weight = 0;
	nodes[0]->left = nodes[0]->right = NULL;

	for (int i = 1; i <= length; ++i)
	{
		nodes[i] = (HuffmanTree)malloc(sizeof(struct TreeNode));
		nodes[i]->data = 0;// 最小值
		nodes[i]->weight = 0;
		nodes[i]->left = nodes[i]->right = NULL;
	}

	for (int i = 1; i <= length; ++i)
	{
		tmp = str[i - 1];
		for (int j = 1; j <= length; ++j)
		{
			if (tmp == nodes[j]->data)
			{
				nodes[j]->weight ++;
				break;
			}
			else if (!nodes[j]->data)
			{
				nodes[j]->data = tmp;
				nodes[j]->weight = 1;
				break;
			}
		}
	}

	for (int i = 1; i <= length; ++i)
	{
		if (!nodes[i]->data)
		{
			break;
		}
		printf("%c\t%d\n", nodes[i]->data, nodes[i]->weight);
		size ++;
	}

	h = (MinHeap)malloc(sizeof(struct HeapNode));
	h->data = nodes;
	h->capacity = 100;
	h->size = size;

	// 构建一个最小堆
	build_heap(h);
	puts("建成最小堆后");
	print_heap(h);

	return h;
}

/* 从堆上取出堆顶的数据 */
HuffmanTree delete_min(MinHeap h)
{
	int target_position, child;
	HuffmanTree max_item, last_item;

	max_item = h->data[1];
	last_item = h->data[h->size --];

	target_position = 1;
	child = target_position << 1;

	while (child <= h->size)
	{
		// 在当前父节点中找到更大的那个子节点,用它的值替换掉当前的节点值(如果这个子节点的值>last_item的值)
		child = target_position << 1;
		if (child != h->size
		        && h->data[child + 1]->weight < h->data[child]->weight)
		{
			child ++;
		}
		// last_item找到了位置,直接跳出这个循环即可
		if (last_item->weight < h->data[child]->weight)
		{
			break;
		}
		h->data[target_position] = h->data[child];
		target_position = child;
		child = target_position << 1;
	}
	h->data[target_position] = last_item;
	return max_item;
}

/* 这里插入一个元素x,不考虑堆中已经存在这个元素的情况 */
void insert(MinHeap h, HuffmanTree x)
{
	int i;
	h->size ++;
	i = h->size;
	for (i = h->size; x->weight < h->data[i >> 1]->weight; i >>= 1)
	{
		h->data[i] = h->data[i >> 1];
	}
	h->data[i] = x;
}

/* 用指定数据创建一颗哈夫曼树 */
HuffmanTree create_Huffman_tree(const ElementType *data)
{
	MinHeap h = get_MinHeap_from_string(data);
	HuffmanTree new_tree;
	while (h->size != 1)
	{
		new_tree = (HuffmanTree)malloc(sizeof(struct TreeNode));
		new_tree->left = delete_min(h);
		new_tree->right = delete_min(h);
		new_tree->weight = new_tree->left->weight + new_tree->right->weight;
		new_tree->data = '0';
		insert(h, new_tree);
	}
	new_tree = delete_min(h);
	return new_tree;
}

void PreOrderTraverse(HuffmanTree tree)
{
	if (tree)
	{
		printf("%c\t%d\t\n", tree->data, tree->weight);
		PreOrderTraverse(tree->left);
		PreOrderTraverse(tree->right);
	}
}

void InOrderTraverse(HuffmanTree tree)
{
	if (tree)
	{
		InOrderTraverse(tree->left);
		printf("%c\t%d\n", tree->data, tree->weight);
		InOrderTraverse(tree->right);
	}
}

// 使用指定的哈夫曼树,生成哈夫曼编码的映射,每个entry在map中的位置(可以认为是hash值)为字符的值
void make_word_code_map(HuffmanTree tree, char *code, int n)
{
	if (!tree)
	{
		return;
	}
	if (!tree->left && !tree->right)
	{
		code[n] = 0;
		word_code_entry entry;
		entry.word = tree->data;
		entry.code = (char *)malloc(n * sizeof(char));
		strcpy(entry.code, code);
		code_map[entry.word] = entry;
	}
	else
	{
		code[n] = '0';
		make_word_code_map(tree->left, code, n + 1);
		code[n] = '1';
		make_word_code_map(tree->right, code, n + 1);
	}
}

// 将指定字符串进行哈夫曼编码并打印
void encode(HuffmanTree tree, const ElementType *data)
{
	int length = strlen(data);
	ElementType tmp;
	printf("%s的哈夫曼编码为:\n", data);
	for (int i = 0; i < length; ++i)
	{
		tmp = data[i];
		printf("%s\t", code_map[tmp].code);
	}
	puts("");
}

// // 将指定的哈夫曼编码字符串，根据指定的哈弗曼编码书,解码成原有字符串,这个就不写了,
// char *decode(HuffmanTree tree,const char *encoded_string)
// {

// }

int main(int argc, char const *argv[])
{
	// 该字符串符合附件图片:哈夫曼编码.png   中的字符格式(' '表示sp,'n'表示nl)
	char *str = "aeists n s e a i a eiei eaiei taetie ietaie ieai eiae eaea";
	HuffmanTree tree =  create_Huffman_tree(str);
	char *code = (char *)malloc(sizeof(char) * 20);// 暂时编码的最大长度为20,也就是最大高度为21

	puts("先序遍历生成的哈弗曼树：");
	PreOrderTraverse(tree);
	puts("中序遍历生成的哈弗曼树：");
	InOrderTraverse(tree);

	make_word_code_map(tree, code, 0);
	puts("每个字符的编码为:");
	for (int i = 0; i < 127; i ++)
	{
		if (code_map[i].code)
		{
			printf("%c\t%s\n", code_map[i].word, code_map[i].code);
		}
	}
	encode(tree,str);

	return 0;
}
