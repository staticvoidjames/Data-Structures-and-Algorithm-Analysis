#include <stdio.h>
#include <stdlib.h>

#define INFINITY 0xffff
#define MAX_VERTEX 100

typedef int vertex_type;
typedef int weight_type;

typedef struct EdgeNode
{
    int vertex_index; // 边节点对应的下标
    weight_type weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct
{
    int in_degree; // 入度
    vertex_type vertex_content;
    EdgeNode *first;
} VertexNode;

typedef struct
{
    VertexNode vertex_nodes[MAX_VERTEX];
    int vertex_num, arc_num;
} Graph;

int *stack; // 用于存储拓扑序列的栈
int top;    // 用于stack2的指针

// 根据指定的顶点信息,创建一个没有边的表
void create_graph(Graph *graph, vertex_type *vertex, int vertex_num)
{
    int i, j;
    graph->arc_num = 0;
    graph->vertex_num = vertex_num;
    for (i = 0; i < vertex_num; i++)
    {
        graph->vertex_nodes[i].in_degree = 0;
        graph->vertex_nodes[i].vertex_content = vertex[i];
        graph->vertex_nodes[i].first = NULL;
    }
}

// 这里没有做该线条是否已经存在的搜索,这里不考虑这个问题
void insert_arc(Graph *graph, int arc_head, int arc_tail, weight_type weight)
{
    EdgeNode *tmp = (EdgeNode *)malloc(sizeof(EdgeNode));
    tmp->next = graph->vertex_nodes[arc_head].first;
    tmp->weight = weight;
    tmp->vertex_index = arc_tail;
    graph->vertex_nodes[arc_head].first = tmp;
    graph->arc_num++;

    graph->vertex_nodes[arc_tail].in_degree++;
}

void print_graph(const Graph *graph)
{
    int i, j;
    EdgeNode *tmp;
    puts("顶点:入度");
    for (i = 0; i < graph->vertex_num; i++)
    {
        printf("V%d:%d\n", graph->vertex_nodes[i].vertex_content, graph->vertex_nodes[i].in_degree);
    }
    puts("");
    if (!graph->arc_num)
    {
        puts("\n该图没有边");
    }
    else
    {
        puts("\n边的邻接表:");
        for (i = 0; i < graph->vertex_num; i++)
        {
            tmp = graph->vertex_nodes[i].first;
            while (tmp)
            {
                printf("<V%d,V%d,%d>\t", graph->vertex_nodes[i].vertex_content, graph->vertex_nodes[tmp->vertex_index].vertex_content, tmp->weight);
                tmp = tmp->next;
            }
            puts("");
        }
    }
}

// 拓扑排序，若无回路，则输出拓扑排序序列并返回1，若有回路返回0
int topological_sort(Graph *graph, int **etv_p)
{
    int queue[MAX_VERTEX] = {0};
    int i, front, rear, indegree;
    int tmp, count = 0;
    front = rear = 0;
    EdgeNode *node;
    int *etv;

    top = 0;
    stack = (int *)malloc(graph->vertex_num * sizeof(int)); // 初始化拓扑序列栈

    *etv_p = (int *)malloc(graph->vertex_num * sizeof(int));
    etv = *etv_p;
    for (i = 0; i < graph->vertex_num; i++)
    {
        indegree = graph->vertex_nodes[i].in_degree;
        if (!indegree)
        {
            count++;
            queue[rear++] = i; // 将入度为0的顶点入栈
        }
        etv[i] = 0;
    }
    // 在求关键路径时,在开始时不可能存在0个或多个入度为0的点
    if (count != 1)
    {
        puts("初始图中存在0个或多个入度为0的点,不能用于关键路径计算");
        return 0;
    }
    count = 0;
    while (front != rear)
    {
        tmp = queue[front++];
        printf("V%d -> ", graph->vertex_nodes[tmp].vertex_content);
        count++;
        stack[++top] = tmp; // 将弹出的顶点序号压入拓扑序列的栈
        for (node = graph->vertex_nodes[tmp].first; node; node = node->next)
        {
            indegree = --graph->vertex_nodes[node->vertex_index].in_degree;
            if (!indegree)
            {
                queue[rear++] = node->vertex_index;
            }
            if (etv[tmp] + node->weight > etv[node->vertex_index])
            {
                etv[node->vertex_index] = etv[tmp] + node->weight;
            }
        }
    }
    if (count != graph->vertex_num)
    {
        puts("图有回路,不能进行拓扑排序");
        return 0;
    }
    return 1;
}

int critical_path(Graph *graph)
{
    int *etv, *ltv; // earliest/latest time of vertex事件最早开始时间和最迟开始时间数组
    int ete, lte;   // earliest/latest time of edge声明活动最早开始时间和最迟开始时间变量
    int i, tmp, get_top;
    EdgeNode *node;
    if (!topological_sort(graph, &etv))
    {
        return 0;
    }
    // init ltv
    ltv = (int *)malloc(graph->vertex_num * sizeof(int));
    for (i = 0; i < graph->vertex_num; i++)
        ltv[i] = etv[graph->vertex_num - 1];

    printf("\netv:\n");
    for (i = 0; i < graph->vertex_num; i++)
        printf("%d -> ", etv[i]);
    printf("\n");

    while (top)
    {
        get_top = stack[top--];
        // 求各顶点事件的最迟发生时间ltv值
        for (node = graph->vertex_nodes[get_top].first; node; node = node->next)
        {
            tmp = node->vertex_index;
            if (ltv[tmp] - node->weight < ltv[get_top])
            {
                ltv[get_top] = ltv[tmp] - node->weight;
            }
        }
    }

    printf("\nltv:\n");
    for (i = 0; i < graph->vertex_num; i++)
        printf("%d -> ", ltv[i]);
    printf("\n");

    puts("关键路径:\n");
    for (i = 0; i < graph->vertex_num; i++) /* 求ete,lte和关键活动 */
    {
        for (node = graph->vertex_nodes[i].first; node; node = node->next)
        {
            tmp = node->vertex_index;
            ete = etv[i];
            lte = ltv[tmp] - node->weight;
            //在关键路径上
            if (ete == lte)
                printf("<v%d - v%d> length: %d \n", graph->vertex_nodes[i].vertex_content, graph->vertex_nodes[tmp].vertex_content, node->weight);
        }
    }
}

main(int argc, char const *argv[])
{
    // 本案例中使用的图如附件:关键路径图.png所示
    Graph graph;
    int i;
    vertex_type vertex[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    create_graph(&graph, vertex, 10);

    insert_arc(&graph, 0, 1, 3);
    insert_arc(&graph, 0, 2, 4);

    insert_arc(&graph, 1, 3, 5);
    insert_arc(&graph, 1, 4, 6);

    insert_arc(&graph, 2, 3, 8);
    insert_arc(&graph, 2, 5, 7);

    insert_arc(&graph, 3, 4, 3);

    insert_arc(&graph, 4, 6, 9);
    insert_arc(&graph, 4, 7, 4);

    insert_arc(&graph, 5, 7, 6);

    insert_arc(&graph, 6, 9, 2);

    insert_arc(&graph, 7, 8, 5);

    insert_arc(&graph, 8, 9, 3);

    print_graph(&graph);

    critical_path(&graph);

    return 0;
}
