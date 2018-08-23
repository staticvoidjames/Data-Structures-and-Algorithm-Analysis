/*
关于最短路径,请查看附件:什么是最短路径.png
                    最短路径问题的分类.png
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
dijstra算法:参考附件 dijstra算法.png

根据图中的结论可以简化为:每次从未收录的节点中找到路径最小的,将其标记为已收录,而因为其收录进来,与其相邻的顶点的最短路径权值可能发生改变,更新这些邻接点的最短路径和最短路径权值

本案例中:数组collected的值用来表示对应顶点是否已经被收录
        数组parent的值表示到该顶点的最短路径的上一个顶点下标
        数组dist的值表示当前已知的到该顶点的最短路径权值
*/
void dijstra(Graph *graph, int start)
{
    int parent[graph->vertex_num], dist[graph->vertex_num], collected[graph->vertex_num];
    int i, j, k, min;

    k = start;
    for (i = 0; i < graph->vertex_num; i++)
    {
        collected[i] = 0;               //开始时任何一个节点都没有收录
        parent[i] = -1;                 //路径还没有开始,所有顶点都是路径的开始
        dist[i] = INFINITY;//最开始到所有地方的路径都是无穷大
    }

    printf("单源最短路径,dijstra:\n收录顶点:V%c\n", graph->vertex[start]);

    collected[start] = 1; //把开始顶点收录
    // 添加第一个顶点,此时只有1个顶点,则最小距离也为0
    min = dist[start] = 0;

    // 计算新添加的节点对其未收录的邻接点的最短距离的影响并更新(这些邻接点会不会在路过这个新加入的顶点的情况下具有更小的路径权值),
    // 每次从未收录顶点中找到一个dist值最小的顶点,将其收录,直到没有顶点离start的距离<INFINITY,最多还需要添加 graph->vertex_num - 1次
    while(1)
    {
        // 新收录的顶点,可能导致其未收录的邻接点的最短路径权值更小,需要更新从start到这些顶点的最短路径权值
        for (j = 0; j < graph->vertex_num; j++)
        {
            if (!collected[j] && (min + graph->arc[k][j]) < dist[j])
            {
                dist[j] = min + graph->arc[k][j];
                parent[j] = k;
            }
        }
        
        min = INFINITY;
        // 找到一个未收录的最近的顶点
        for (j = 0; j < graph->vertex_num; j++)
        {
            if (!collected[j] && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        if (min == INFINITY)
        {
            // 没有相邻的顶点了,也就是存在顶点是无法从start到达的
            break;
        }
        printf("收录顶点:V%d\n", k);
        collected[k] = 1; // 收录该顶点,其最短路径已经确定了
    }

    printf("最短路径及长度如下:\n");
    struct
    {
        int *data;
        int top;
    } stack;

    puts("parent:");
    for (i = 0; i < graph->vertex_num; ++i)
    {
        printf("%d\t", parent[i]);
    }
    puts("");
    puts("dist:");
    for (i = 0; i < graph->vertex_num; ++i)
    {
        printf("%d\t", dist[i]);
    }
    puts("");
    for (i = 0; i < graph->vertex_num; ++i)
    {
        printf("V%c - V%c : %d \n", graph->vertex[start], graph->vertex[i], dist[i]);
        // 路径要逆序输出,这里使用栈方式实现
        stack.data = (int *)malloc(graph->vertex_num * sizeof(int));
        stack.top = -1;
        j = i;
        do
        {
            stack.data[++stack.top] = j;
            j = parent[j];
        } while (j != -1);
        while (stack.top != -1)
        {
            printf("V%c ", graph->vertex[stack.data[stack.top--]]);
        }
        puts("");
    }
    free(stack.data);
}

main(int argc, char const *argv[])
{
    // 本案例中使用的图如附件:shortest_path.jpg 所示
    Graph graph;
    int i, j;
    vertex_type vertex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    create_graph(&graph, vertex, 9);

    insert_arc(&graph, 0, 1, 1);
    insert_arc(&graph, 0, 2, 5);
    insert_arc(&graph, 1, 2, 3);
    insert_arc(&graph, 1, 3, 7);
    insert_arc(&graph, 1, 4, 5);
    insert_arc(&graph, 2, 4, 1);
    insert_arc(&graph, 2, 5, 7);
    insert_arc(&graph, 3, 4, 2);
    insert_arc(&graph, 3, 6, 3);
    insert_arc(&graph, 4, 5, 3);
    insert_arc(&graph, 4, 6, 6);
    insert_arc(&graph, 4, 7, 9);
    insert_arc(&graph, 5, 7, 5);
    insert_arc(&graph, 6, 7, 2);
    insert_arc(&graph, 6, 8, 7);
    insert_arc(&graph, 7, 8, 4);

    for (i = 0; i < graph.vertex_num; i++)
    {
        for (j = i; j < graph.vertex_num; j++)
        {
            graph.arc[j][i] = graph.arc[i][j];
        }
    }

    print_vertex(&graph);
    print_matrix(&graph);

    dijstra(&graph, 0);
    // MST_Kruskal(&graph);

    return 0;
}
