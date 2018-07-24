# Data Structures and Algorithm Analysis

#### 项目介绍
数据结构与算法学习代码及笔记  
每个算法的代码:C语言代码肯定存在,Java代码可能存在  
暂时学习内容范围为:  
中国大学mooc---数据结构,陈越教授、何钦铭教授，国家精品课程  
《大话数据结构》---程杰，清华大学出版社  
《数据结构与算法分析》---[美] Mark Allen Weiss,冯舜玺 译  

编码:UTF-8, I hate GBK  
运行环境:建议使用gcc编译,c99模式运行  

#### 目录
为了避免因英文命名导致难以找到对应源代码的问题,这里给出目录  

因为算法实在是不知道怎么分类,直接放在一级目录下  
此外,每一个文件夹下表示一种数据结构相关

具体命名对应如下:  

#### 数据结构相关(目录):  
> 本目录所有目录文件均只提供C语言版目录,相关的Java实现有无均不确定，除此之外，如果个人觉得写得可能有点复杂或需要补充理解，可能提供其他摘录版本，摘录版本会有相应带括号的文件名后缀，如linked_list(大话数据结构).c,但是这些文件不记录至目录中

##### list	线性表
|文件名|文件内容|  
|:--|:--|  
|array.c|可变数组|
|arraylist.c|顺序存储方式，数组实现|
|linkedlist.c|链表实现方式|
|```stack_using_array.c```|栈,顺序存储方式实现|
|double_stack.c|栈,两栈共享空间|
|```stack_using_linked_list.c```|栈,链表方式实现|
|```queue_using_arry.c```|队列,顺序存储方式实现|
|```queue_using_linked_list.c```|队列,链表方式实现|

#### string 串
|文件名|文件内容|  
|:--|:--|  
|string.c|字符串的一种实现方式|
| KMP_Algorithm.c |子串查找的多种方式,包括KMP查找及改进|

#### tree 树
|文件名|文件内容|  
|:--|:--|  
|```binary_tree_using_array.c```|二叉树,顺序存储方式实现|  
|```binary_tree_using_pointer.c```|二叉树,指针方式实现|  
|```binary_search_tree.c```|BST:二叉搜索(查找)树|  
|AVL_Tree.c|平衡二叉树|  
|heap.c|堆|  
|Huffman_tree.c|哈夫曼树(最优二叉树,含哈夫曼编码)|  
|threaded_binary_tree.c|线索二叉树|  

#### 算法相关(一级目录下的文件):
|文件名|文件内容|  
|:--|:--|  
|sequential_search.c|顺序查找(含使用哨兵方式)|  
|binary_search.c|二分法查找(含插值查找&斐波那契查找)|  
|fibonacci.c|斐波那契数列(含为递归方式)|  
|max_subsequence.c|最大子列和问题的n种求解方式|  
|gcd.c|求最大公约数的若干种方法(含辗转相除法、更相减损法及其改进)|  
|hash_table.c|散列查找(哈希表)|  