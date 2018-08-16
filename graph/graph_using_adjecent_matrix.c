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

void print_graph(const Graph *graph)
{
    int i, j, current_printed_arc_num;
    puts("顶点:");
    for (i = 0; i < graph->vertex_num; i++)
    {
        putchar(graph->vertex[i]);
    }
    if (!graph->arc_num)
    {
        puts("\n该图没有边");
    }
    else
    {
        current_printed_arc_num = 0;
        puts("\n边的邻接矩阵:");
        for (i = 0; i < graph->vertex_num; i++)
        {
            for (j = 0; j < graph->vertex_num; j++)
            {
                printf("%d\t", graph->arc[i][j]);
                if (graph->arc[i][j] != INFINITY)
                {
                    current_printed_arc_num++;
                }
            }
            puts("");
            // 已经打印完了就不要打印了
            if (current_printed_arc_num == graph->arc_num)
            {
                break;
            }
        }
    }
}

main(int argc, char const *argv[])
{
    Graph graph;
    // 4个顶点
    vertex_type vertex[] = {'A', 'B', 'C', 'D'};
    create_graph(&graph, vertex, 4);
    insert_arc(&graph, 0, 1, 6); // A->B
    insert_arc(&graph, 1, 2, 2); // B->C
    insert_arc(&graph, 2, 3, 3); // C->D
    insert_arc(&graph, 3, 0, 1); // D->A
    print_graph(&graph);

    return 0;
}
