#include "matrixgraph.hpp"
#include <assert.h>

MatrixGraph::MatrixGraph(int vertex_num)
{
    adjacencyMatrix.assign(vertex_num, std::vector<int>(vertex_num));
}

MatrixGraph::MatrixGraph(const IGraph& graph)
{
    adjacencyMatrix.assign(graph.VerticesCount(), std::vector<int>(graph.VerticesCount()));

    for (int i = 0; i < VerticesCount(); i++)
    {
        std::vector<int> next_vertices = graph.GetNextVertices(i);
        for (auto elem: next_vertices)
        {
            adjacencyMatrix[i][elem] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < VerticesCount());
    assert(0 <= to && to < VerticesCount());

    adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const
{
    return adjacencyMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    std::vector<int> next_vertices;
    for (int i = 0; i < VerticesCount(); i++)
    {
        if (adjacencyMatrix[vertex][i] == 1)
        {
            next_vertices.push_back(i);
        }
    }
    return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> prev_vertivces;

    for (int v = 0; v < VerticesCount(); v++)
    {
        if (adjacencyMatrix[v][vertex] == 1)
        {
            prev_vertivces.push_back(v);
        }
    }
    return prev_vertivces;
}