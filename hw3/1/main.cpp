#include "listgraph.hpp"
#include "matrixgraph.hpp"
#include "setgraph.hpp"
#include "arcgraph.hpp"
#include <assert.h>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>
#include <queue>

void bfs_aux(const IGraph& graph, std::vector<bool>& visited, int vertex, std::function<void(int)> func)
{
    std::queue<int> order;
    order.push(vertex);
    visited[vertex] = true;

    while(!order.empty())
    {
        int current_vertex = order.front();
        order.pop();

        func(current_vertex);

        for (auto next_vertex: graph.GetNextVertices(current_vertex))
        {
            if (!visited[next_vertex])
            {
                order.push(next_vertex);
                visited[next_vertex] = true;
            }
        }
    }
}

void bfs(const IGraph& graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
        {
            bfs_aux(graph, visited, i, func);
        }
    }
}

int main()
{
    auto print_func = [](int vertex){ std::cout << vertex << " "; };

    ListGraph graph(6);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(2, 5);
    graph.AddEdge(4, 5);
    graph.AddEdge(1, 3);
    graph.AddEdge(4, 2);
    std::cout << "ListGraph: ";
    bfs(graph, print_func);

    MatrixGraph mgraph(graph);
    std::cout << std::endl << "MatrixGraph: ";
    bfs(mgraph, print_func);

    SetGraph sgraph(mgraph);
    std::cout << std::endl << "SetGraph: ";
    bfs(sgraph, print_func);

    ArcGraph agraph(sgraph);
    std::cout << std::endl << "ArcGraph: ";
    bfs(agraph, print_func);

    return 0;
}