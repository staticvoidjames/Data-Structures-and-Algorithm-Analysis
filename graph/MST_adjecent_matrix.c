/*
MST: Minimum Spanning Tree.最小生成树
关于生成树的介绍,请查看附件:    什么是最小生成树.png
*/
#include <stdio.h>
#include <stdlib.h>

#define INFINITY 0xffff
#define MAX_VERTEX 100

typedef char vertex_type;
typedef int weight_type;

typedef struct
{
    vertex_type vertex[MAX_VERTEX]; //记录顶点信息
    // 记录边信息(边的两个顶点在顶点集合中的位置及对应的权重等)的邻接矩阵
    // 这里也可以用一个单独的指针就行,使用时将邻接矩阵传入,通过顶点个数可以算出每个边的权重的位置偏移量
    weight_type arc[MAX_VERTEX][MAX_VERTEX];
    int vertex_num, arc_num;
} Graph;

int visited[MAX_VERTEX];

// 根据指定的顶点信息,创建一个没有边的表
void create_graph(Graph *graph, vertex_type *vertex, int vertex_num)
{
    int i, j;
    graph->arc_num = 0;
    graph->vertex_num = vertex_num;
    for (i = 0; i < vertex_num; i++)
    {
        graph->vertex[i] = vertex[i];
        for (j = 0; j < vertex_num; j++)
        {
            graph->arc[i][j] = INFINITY;
        }
    }
}

void insert_arc(Graph *graph, int arc_head, int arc_tail, weight_type weight)
{
    graph->arc[arc_head][arc_tail] = weight;
    graph->arc_num++;
}

void print_vertex(const Graph *graph)
{
    int i;
    puts("顶点:");
    for (i = 0; i < graph->vertex_num; i++)
    {
        putchar('V');
        putchar(graph->vertex[i]);
        putchar('\t');
    }
}

void print_matrix(const Graph *graph)
{
    int i, j, current_printed_arc_num;
    if (!graph->arc_num)
    {
        puts("\n该图没有边");
    }
    else
    {
        current_printed_arc_num = 0;
        puts("\n拥有边及权重:");
        for (i = 0; i < graph->vertex_num; i++)
        {
            for (j = 0; j < graph->vertex_num; j++)
            {
                if (graph->arc[i][j] != INFINITY)
                {
                    printf("<V%c,V%c>\t%d\n", graph->vertex[i], graph->vertex[j], graph->arc[i][j]);
                    current_printed_arc_num++;
                }
            }
            // 已经打印完了就不要打印了
            if (current_printed_arc_num == graph->arc_num)
            {
                break;
            }
        }
    }
}

/*
prim算法：每次找到未被访问的离现有生成树最近的节点，并将其并入树中，直到所有节点都被并入树中，即得到最小生成树
dist:数组中每一个值表示对应顶点与现有的树的最近距离,如果该值为0,表示该顶点已经在树中
parent:用于存储对应节点的父节点的位置
*/
int MST_Prim(Graph *graph)
{
    int parent[graph->vertex_num], dist[graph->vertex_num];
    int i, j, k, min, total_weight;
    for (i = 0; i < graph->vertex_num; i++)
    {
        dist[i] = INFINITY; // 在生成树开始生成之前,所有的节点离已生成的树的距离均为INFINITY
    }
    dist[0] = 0; //将第0个节点收录进来生成树
    total_weight = 0;
    parent[0] = -1; //第0个节点的父节点为-1,表示其为根节点
    printf("初始化生成树\n加入节点:V%c\n", graph->vertex[k]);
    puts("最小生成树(Prim算法)");
    printf("初始化生成树\n加入节点:V%c\n", graph->vertex[k]);

    for (i = 1; i < graph->vertex_num; i++)
    {
        dist[i] = graph->arc[0][i]; //当前只有1个节点,其邻接点与当前树的距离就是与当前节点的距离
        parent[i] = 0;              //将所有的邻接点的父节点都置为0,也就是初始化树时候的节点
    }
    // 最多还有graph->vertex_num - 1 个顶点需要添加
    for (j = 1; j < graph->vertex_num; j++)
    {
        k = 0;
        min = INFINITY;
        for (i = 1; i < graph->vertex_num; i++)
        {
            if (dist[i] && dist[i] < min)
            {
                min = dist[i]; //找到离当前树最近的节点
                k = i;         //记住这个最小节点的位置
            }
        }
        // 的确找到了新的节点
        if (min != INFINITY)
        {
            total_weight += dist[k];
            dist[k] = 0; //将当前节点收录进生成树中
            printf("加入节点:V%c\n", graph->vertex[k]);
            // 对新加入的点,要统计其邻接点与该节点的距离,如果有  邻接点与新加入节点的距离 < 该邻接点与生成树的最小距离,更新该邻接点与树的距离
            for (i = 1; i < graph->vertex_num; i++)
            {
                if (dist[i] && graph->arc[k][i] < dist[i])
                {
                    dist[i] = graph->arc[k][i];
                    parent[i] = k; //后续如果第i个节点添加进来,那么其父节点肯定是第k个节点
                }
            }
        }
        else
        {
            // 找不到节点了,但是现在添加进入的节点数还没有graph->vertex_num个,证明无法生成最小生成树,传入的图不是连通图
            puts("生成树不存在!!!"); //这里不是连通图,那么就没有生成树,也就更加没有最小生成树了
            return -1;
        }
    }
    printf("根节点:V%c\n", graph->vertex[0]);
    for (i = 1; i < graph->vertex_num; i++)
    {
        printf("节点V%c的父节点:V%c\n", graph->vertex[i], graph->vertex[parent[i]]);
    }
    printf("最小生成树的总权重%d\n", total_weight);
    return total_weight;
}

typedef struct
{
    int head;
    int tail;
    int weight;
} Edge;

void build_edge(Edge *edge, Graph *graph)
{
    int i, j, k, sorted;
    Edge tmp;
    k = 0;
    //因为是无向图,只需对矩阵的一半部分进行扫描,添加边即可
    for (i = 0; i < graph->vertex_num - 1; i++)
    {
        for (j = i + 1; j < graph->vertex_num; j++)
        {
            if (graph->arc[i][j] != INFINITY)
            {
                edge[k].head = i;
                edge[k].tail = j;
                edge[k].weight = graph->arc[i][j];
                k++;
            }
        }
    }
    // 正常情况下,这里用堆排序,这里为了方便,直接用冒泡排序
    for (i = 0; i < graph->arc_num - 1; i++)
    {
        sorted = 1;
        for (j = 0; j < graph->arc_num - i - 1; j++)
        {
            if (edge[j].weight > edge[j + 1].weight)
            {
                tmp = edge[j];
                edge[j] = edge[j + 1];
                edge[j + 1] = tmp;
                sorted = 0;
            }
        }
        if (sorted)
        {
            break;
        }
    }
    printf("权排序之后的边为:\n");
    for (i = 0; i < graph->arc_num; i++)
    {
        printf("(%d, %d) %d\n", edge[i].head, edge[i].tail, edge[i].weight);
    }
}

// 找到第vertex_index个节点所在树的根节点
int find_root(int *parent, int vertex_index)
{
    // 这个节点不是根节点,追溯根节点
    while (parent[vertex_index] != -1)
    {
        vertex_index = parent[vertex_index];
    }
    return vertex_index;
}
/*
Kruskal算法:
每次找到图中剩余权值最小的边,使其独自成树
switch(如果这条边的2个顶点)
    case:在已知的同一个树里面,说明这条边在如果加入树中,会构成回路,不处理;

    case:分别位于两颗已知树中,添加这条边,合并这两颗树(将一颗树的根节点的父节点指向另一颗树);
    case:其中1个顶点位于一颗树中,另一颗不位于任何一颗树中,直接将这条边添加进这可树即可;
    case:两颗都不位于任何一颗树中,自身成为一颗树,其中一个顶点做根节点,另一个顶点做子节点。

    后面3种情况说起来这么复杂，其实在代码中就一行代码，说白了就是为每一个加入的顶点找一个根节点而已,为新添加的边找到一颗树来依靠。

在本案例中,使用数组parent表示树，数组中可能存在多棵树，当数组中存的值为负数时，
表示其为树的根节点，如果2个顶点的根节点为同一个，那么也就是位于同一颗树中。
在生成最小生成树之前,需要对边按权值进行从小到大排序,一般这里推荐使用最小堆排序,其可以将算法复杂度控制为O(n)
这里就不管了,直接冒泡排序就得了
*/
int MST_Kruskal(Graph *graph)
{
    int parent[graph->vertex_num];
    Edge edge[graph->arc_num];
    int i, j, k, total_edge, total_weight;
    int head_root, tail_root;

    total_weight = total_edge = 0;

    build_edge(edge, graph);

    for (i = 0; i < graph->vertex_num; i++)
    {
        parent[i] = -1; // 在生成树开始生成之前,每一顶点都是独立的根节点
    }
    // 对这些边进行遍历,有合适的边就放入到树中
    for (i = 0; i < graph->arc_num; i++)
    {
        head_root = find_root(parent, edge[i].head); // 找到头结点所在树的根节点
        tail_root = find_root(parent, edge[i].tail); // 找到尾节点所在树的根节点
        // 根节点不是同一个,也就是不在同一颗树中,
        if (head_root != tail_root)
        {
            printf("加入边:(%d, %d) %d\n", edge[i].head, edge[i].tail, edge[i].weight);
            total_weight += edge[i].weight;
            parent[tail_root] = head_root;//这行语句实现了上面注释中的3种情况的处理(为新添加的边找到一颗树来依靠)
            total_edge++;
        }
    }

    if (total_edge != graph->vertex_num - 1)
    {
        puts("生成树不存在!!!"); //这里不是连通图,那么就没有生成树,也就更加没有最小生成树了
        return -1;
    }
    printf("最小生成树的总权重%d\n", total_weight);
    return total_weight;
}

main(int argc, char const *argv[])
{
    // 本案例中使用的图如附件:MST.png 所示
    Graph graph;
    int i, j;
    vertex_type vertex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    create_graph(&graph, vertex, 9);

    insert_arc(&graph, 0, 1, 10);
    insert_arc(&graph, 0, 5, 11);
    insert_arc(&graph, 1, 2, 18);
    insert_arc(&graph, 1, 8, 12);
    insert_arc(&graph, 1, 6, 16);

    insert_arc(&graph, 2, 8, 8);
    insert_arc(&graph, 2, 3, 22);
    insert_arc(&graph, 3, 8, 21);
    insert_arc(&graph, 3, 6, 24);
    insert_arc(&graph, 5, 6, 17);

    insert_arc(&graph, 3, 7, 16);
    insert_arc(&graph, 3, 4, 20);
    insert_arc(&graph, 4, 7, 7);
    insert_arc(&graph, 4, 5, 26);
    insert_arc(&graph, 6, 7, 19);

    for (i = 0; i < graph.vertex_num; i++)
    {
        for (j = i; j < graph.vertex_num; j++)
        {
            graph.arc[j][i] = graph.arc[i][j];
        }
    }

    print_vertex(&graph);
    print_matrix(&graph);
    MST_Prim(&graph);
    MST_Kruskal(&graph);

    return 0;
}
