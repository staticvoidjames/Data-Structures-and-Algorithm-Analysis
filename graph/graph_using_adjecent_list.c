#include <stdio.h>
#include <stdlib.h>

#define INFINITY 0xffff
#define MAX_VERTEX 100

typedef char vertex_type;
typedef int weight_type;

typedef struct EdgeNode
{
    int vertex_index; // 边节点对应的下标
    weight_type weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct
{
    vertex_type vertex_content;
    EdgeNode *first;
} VertexNode;

typedef struct
{
    VertexNode vertex_nodes[MAX_VERTEX];
    int vertex_num, arc_num;
} Graph;

int visited[MAX_VERTEX];

typedef struct
{
    int vertex_index[MAX_VERTEX];
    int front, rear;
} Queue;

// 根据指定的顶点信息,创建一个没有边的表
void create_graph(Graph *graph, vertex_type *vertex, int vertex_num)
{
    int i, j;
    graph->arc_num = 0;
    graph->vertex_num = vertex_num;
    for (i = 0; i < vertex_num; i++)
    {
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
}

void DFS(const Graph *graph, int start_index)
{
    int i;
    EdgeNode *tmp = graph->vertex_nodes[start_index].first;
    visited[start_index]++;
    putchar(graph->vertex_nodes[start_index].vertex_content);

    while (tmp)
    {
        if (!visited[tmp->vertex_index])
        {
            DFS(graph, tmp->vertex_index);
        }
        tmp = tmp->next;
    }
}

void DFS_Traverse(const Graph *graph)
{
    int i;
    for (i = 0; i < graph->vertex_num; i++)
    {
        visited[i] = 0;
    }
    puts("DFS:");

    // 对每一个未被访问的顶点进行DFS
    for (i = 0; i < graph->vertex_num; i++)
    {
        if (!visited[i])
        {
            DFS(graph, i);
            puts("");
        }
    }
}

void BFS_Traverse(const Graph *graph)
{
    int i, j, vertex_index;
    Queue queue;
    EdgeNode *tmp;
    queue.front = queue.rear = 0;

    for (i = 0; i < graph->vertex_num; i++)
    {
        visited[i] = 0;
    }

    puts("BFS:");

    for (i = 0; i < graph->vertex_num; i++)
    {
        if (!visited[i])
        {
            // 开始:访问一个元素,并将它入列
            putchar(graph->vertex_nodes[i].vertex_content);
            visited[i] ++;
            queue.vertex_index[queue.rear++] = i;// 入列这个开始结点
            while (queue.rear - queue.front)
            {
                // 出列一个元素,访问其未被访问过的相邻元素并将这些相邻元素入列
                vertex_index =  queue.vertex_index[queue.front ++];// 取出一个节点
                tmp = graph->vertex_nodes[vertex_index].first;
                while (tmp)
                {
                    vertex_index = tmp->vertex_index;
                    if (!visited[vertex_index])
                    {
                        putchar(graph->vertex_nodes[vertex_index].vertex_content);
                        queue.vertex_index[queue.rear++] = vertex_index;// 入列这个结点
                        visited[vertex_index] ++;
                    }
                    tmp = tmp->next;
                }
            }
            puts("");
        }
    }
}

void print_graph(const Graph *graph)
{
    int i, j;
    EdgeNode *tmp;
    puts("顶点:");
    for (i = 0; i < graph->vertex_num; i++)
    {
        putchar(graph->vertex_nodes[i].vertex_content);
    }
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
                printf("<%c,%c>\t", graph->vertex_nodes[i].vertex_content, graph->vertex_nodes[tmp->vertex_index].vertex_content);
                tmp = tmp->next;
            }
            puts("");
        }
    }
}

main(int argc, char const *argv[])
{
    // 本案例中使用的图如附件:有向图.jpg所示
    Graph graph;
    int i;
    vertex_type vertex[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    create_graph(&graph, vertex, 9);

    insert_arc(&graph, 0, 1, 6); // A->B

    insert_arc(&graph, 1, 2, 3); // B->C
    insert_arc(&graph, 1, 4, 3); // B->E
    insert_arc(&graph, 1, 5, 6); // B->F

    insert_arc(&graph, 2, 4, 4); // C->E

    insert_arc(&graph, 3, 2, 6); // D->C

    insert_arc(&graph, 4, 1, 6); // E->B
    insert_arc(&graph, 4, 3, 6); // E->D

    insert_arc(&graph, 6, 5, 3); // G->F

    insert_arc(&graph, 7, 8, 3);

    print_graph(&graph);

    DFS_Traverse(&graph);
    BFS_Traverse(&graph);

    return 0;
}
