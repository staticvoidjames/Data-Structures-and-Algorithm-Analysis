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
                printf("<V%d,V%d>\t", graph->vertex_nodes[i].vertex_content, graph->vertex_nodes[tmp->vertex_index].vertex_content);
                tmp = tmp->next;
            }
            puts("");
        }
    }
}

// 拓扑排序，若无回路，则输出拓扑排序序列并返回1，若有回路返回0
int topological_sort(Graph *graph)
{
    int queue[MAX_VERTEX] = {0};
    int i, front,rear, indegree;
    int tmp, count = 0;
    front = rear = 0;
    EdgeNode *node;
    for (i = 0; i < graph->vertex_num; i++)
    {
        indegree = graph->vertex_nodes[i].in_degree;
        if (!indegree)
        {
            queue[rear++] = i; // 将入度为0的顶点入栈
        }
    }
    while (front != rear)
    {
        tmp = queue[front++];
        printf("V%d -> ", graph->vertex_nodes[tmp].vertex_content);
        count ++;
        for (node = graph->vertex_nodes[tmp].first; node; node = node->next)
        {
            indegree = --graph->vertex_nodes[node->vertex_index].in_degree;
            if (!indegree)
            {
                queue[rear ++] = node->vertex_index;
            }
        }
    }
    if(count != graph->vertex_num)
    {
        puts("图有回路,不能进行拓扑排序");
        return 0;
    }
    return 1;
}

main(int argc, char const *argv[])
{
    // 本案例中使用的图如附件:拓扑排序图.jpg所示
    Graph graph;
    int i;
    vertex_type vertex[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    create_graph(&graph, vertex, 14);
    // 拓扑排序不需要权重,所有的weight都为0
    insert_arc(&graph, 0, 4, 0);
    insert_arc(&graph, 0, 5, 0);
    insert_arc(&graph, 0, 11, 0);

    insert_arc(&graph, 1, 2, 0);
    insert_arc(&graph, 1, 4, 0);
    insert_arc(&graph, 1, 8, 0);

    insert_arc(&graph, 2, 5, 0);
    insert_arc(&graph, 2, 6, 0);
    insert_arc(&graph, 2, 9, 0);

    insert_arc(&graph, 3, 2, 0);
    insert_arc(&graph, 3, 13, 0);

    insert_arc(&graph, 4, 7, 0);

    insert_arc(&graph, 5, 8, 0);
    insert_arc(&graph, 5, 12, 0);

    insert_arc(&graph, 6, 5, 0);

    insert_arc(&graph, 8, 7, 0);

    insert_arc(&graph, 9, 10, 0);
    insert_arc(&graph, 9, 11, 0);

    insert_arc(&graph, 10, 13, 0);

    insert_arc(&graph, 12, 9, 0);

    print_graph(&graph);
    
    topological_sort(&graph);

    return 0;
}
