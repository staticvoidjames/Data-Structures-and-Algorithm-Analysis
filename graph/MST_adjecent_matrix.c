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
lowcost数组:数组中每一个值表示对应顶点与现有的树的最近距离,如果该值为0,表示该顶点已经在树中
adjvex:用于存储对应节点的父节点的位置
*/
int MST_Prim(Graph *graph)
{
    int adjvex[graph->vertex_num], lowcost[graph->vertex_num];
    int i, j, k, min, total_weight;
    for (i = 0; i < graph->vertex_num; i++)
    {
        lowcost[i] = INFINITY; // 在生成树开始生成之前,所有的节点离已生成的树的距离均为INFINITY
    }
    lowcost[0] = 0; //将第0个节点收录进来生成树
    total_weight = 0;
    adjvex[0] = -1; //第0个节点的父节点为-1,表示其为根节点
    printf("初始化生成树\n加入节点:V%c\n", graph->vertex[k]);

    for (i = 1; i < graph->vertex_num; i++)
    {
        lowcost[i] = graph->arc[0][i]; //当前只有1个节点,其邻接点与当前树的距离就是与当前节点的距离
        adjvex[i] = 0;                 //将所有的邻接点的父节点都置为0,也就是初始化树时候的节点
    }
    // 最多还有graph->vertex_num - 1 个顶点需要添加
    for (j = 1; j < graph->vertex_num; j++)
    {
        k = 0;
        min = INFINITY;
        for (i = 1; i < graph->vertex_num; i++)
        {
            if (lowcost[i] && lowcost[i] < min)
            {
                min = lowcost[i]; //找到离当前树最近的节点
                k = i;            //记住这个最小节点的位置
            }
        }
        // 的确找到了新的节点
        if (min != INFINITY)
        {
            total_weight += lowcost[k];
            lowcost[k] = 0; //将当前节点收录进生成树中
            printf("加入节点:V%c\n", graph->vertex[k]);
            // 对新加入的点,要统计其邻接点与该节点的距离,如果有  邻接点与新加入节点的距离 < 该邻接点与生成树的最小距离,更新该邻接点与树的距离
            for (i = 1; i < graph->vertex_num; i++)
            {
                if (lowcost[i] && graph->arc[k][i] < lowcost[i])
                {
                    lowcost[i] = graph->arc[k][i];
                    adjvex[i] = k; //后续如果第i个节点添加进来,那么其父节点肯定是第k个节点
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
        printf("节点V%c的父节点:V%c\n", graph->vertex[i], graph->vertex[adjvex[i]]);
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

    
    return 0;
}
