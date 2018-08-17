#include <stdio.h>
#include <stdlib.h>

#define INFINITY 0xffff
#define MAX_VERTEX 100

typedef char vertex_type;
typedef int weight_type;

typedef struct
{
    int vertex_index[MAX_VERTEX];
    int front, rear;
} Queue;

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

// DFS:Depth First Search,深度优先搜索
// 注意:这里指的是搜索,而不是遍历,这里使用这种搜索方式进行遍历(在一个图中搜索,搜索的目标是什么呢,顶点?边?搜索这些东西没必要使用DFS/BFS这些方式),进行举例
// 其实,最简单的顶点遍历方式就是直接遍历顶点集合即可,其时间复杂度为O(v),其中v为顶点数
// Do not fall into the trap of thinking:不要掉进思维里的陷阱
void DFS(const Graph *graph, int start_index)
{
    int i;
    visited[start_index]++;
    putchar(graph->vertex[start_index]);
    for (i = 0; i < graph->vertex_num; i++)
    {
        if (graph->arc[start_index][i] != INFINITY)
        {
            if (!visited[i])
            {
                DFS(graph, i);
            }
        }
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
            visited[i]++;
            putchar(graph->vertex[i]);
            queue.vertex_index[queue.rear++] = i; // 入列这个开始结点

            while (queue.rear - queue.front)
            {
                // 出列一个元素,访问其未被访问过的相邻元素并将这些相邻元素入列
                vertex_index = queue.vertex_index[queue.front++];
                for (j = 0; j < graph->vertex_num; j++)
                {
                    if (graph->arc[vertex_index][j] != INFINITY && !visited[j])
                    {
                        putchar(graph->vertex[j]);
                        queue.vertex_index[queue.rear++] = j;
                        visited[j]++;
                    }
                }
            }
        }
        puts("");
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

    print_vertex(&graph);
    print_matrix_in_weight(&graph);
    print_matrix_in_arc(&graph);

    DFS_Traverse(&graph);
    BFS_Traverse(&graph);
    
    return 0;
}
