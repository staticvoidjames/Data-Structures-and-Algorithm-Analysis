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
        putchar(graph->vertex[i]);
    }
}

void print_matrix_in_weight(const Graph *graph)
{
    int i, j, current_printed_arc_num;
    if (!graph->arc_num)
    {
        puts("\n该图没有边");
    }
    else
    {
        current_printed_arc_num = 0;
        puts("\n边的邻接矩阵(权值形式):");
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

void print_matrix_in_arc(const Graph *graph)
{
    int i, j, current_printed_arc_num;
    if (!graph->arc_num)
    {
        puts("\n该图没有边");
    }
    else
    {
        current_printed_arc_num = 0;
        puts("\n边的邻接矩阵(边形式):");
        for (i = 0; i < graph->vertex_num; i++)
        {
            for (j = 0; j < graph->vertex_num; j++)
            {
                if (graph->arc[i][j] != INFINITY)
                {
                    printf("<%c,%c>\t", graph->vertex[i], graph->vertex[j]);
                    current_printed_arc_num++;
                }
                else
                {
                    printf("%d\t", graph->arc[i][j]);
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

// DFS:Depth First Search,深度优先遍历(无向图遍历方式)
void DFS_Traverse_undirectional_graph_way(const Graph *graph,int vertex_index)
{
    int i;
    visited[vertex_index]++;
    putchar(graph->vertex[vertex_index]);
    for (i = 0; i < graph->vertex_num; i++)
    {
        if (graph->arc[vertex_index][i] != INFINITY)
        {
            if (!visited[i])
            {
                DFS_Traverse_undirectional_graph_way(graph, i);
            }
        }
    }
}

main(int argc, char const *argv[])
{
    // 本案例中使用的图如附件:深度优先搜索.png所示,图中左图为生成的图,右图为搜索过程图示
    // 其中本案例中为有向图,但是存在如下规律:
    // 若存在弧<Vi,Vj>,肯定存在<Vj,Vi>(说白了就是用有向边组成了一个无向图)
    // 此图来自《大话数据结构》关于图的深度优先搜索部分
    Graph graph;
    int i;
    // 4个顶点
    vertex_type vertex[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    create_graph(&graph, vertex, 9);
    insert_arc(&graph, 0, 1, 6); // A->B
    insert_arc(&graph, 1, 0, 6); // B->A

    insert_arc(&graph, 1, 2, 3); // B->C
    insert_arc(&graph, 2, 1, 3);

    insert_arc(&graph, 2, 3, 4); // C->D
    insert_arc(&graph, 3, 2, 4);

    insert_arc(&graph, 3, 4, 6); // D->E
    insert_arc(&graph, 4, 3, 6);

    insert_arc(&graph, 4, 5, 6); // E->F
    insert_arc(&graph, 5, 4, 6);

    insert_arc(&graph, 5, 0, 6); // F->A
    insert_arc(&graph, 0, 5, 6);

    insert_arc(&graph, 1, 6, 6); // B->G
    insert_arc(&graph, 6, 1, 6);

    insert_arc(&graph, 3, 6, 6); // D->G
    insert_arc(&graph, 6, 3, 6);

    insert_arc(&graph, 5, 6, 6); // F->G
    insert_arc(&graph, 6, 5, 6);

    insert_arc(&graph, 1, 8, 6); // B->I
    insert_arc(&graph, 8, 1, 6);

    insert_arc(&graph, 2, 8, 6); // C->I
    insert_arc(&graph, 8, 2, 6);

    insert_arc(&graph, 3, 8, 6); // D->I
    insert_arc(&graph, 8, 3, 6);

    insert_arc(&graph, 3, 7, 6); // D->H
    insert_arc(&graph, 7, 3, 6);

    insert_arc(&graph, 4, 7, 6); // E->H
    insert_arc(&graph, 7, 4, 6);

    insert_arc(&graph, 6, 7, 6); // G->H
    insert_arc(&graph, 7, 6, 6);

    print_vertex(&graph);
    print_matrix_in_weight(&graph);
    print_matrix_in_arc(&graph);

	puts("DFS(无向图方式):");
    for(i = 0 ;i < graph.vertex_num;i ++)
    {
        visited[i] = 0;
    }

    DFS_Traverse_undirectional_graph_way(&graph,0);

    return 0;
}
