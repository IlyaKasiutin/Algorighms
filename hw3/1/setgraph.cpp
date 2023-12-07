#include "setgraph.hpp"
#include <assert.h>

SetGraph::SetGraph(int vertex_num): adjacencySet(vertex_num)
{

}

SetGraph::SetGraph(const IGraph& graph): adjacencySet(graph.VerticesCount())
{
    for (int i = 0; i < VerticesCount(); i++)
    {
        for (auto vertice: graph.GetNextVertices(i))
            adjacencySet[i].insert(vertice);
    }
}

void SetGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < VerticesCount());
    assert(0 <= to && to < VerticesCount());

    adjacencySet[from].insert(to);
}

int SetGraph::VerticesCount() const
{
    return adjacencySet.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    return std::vector<int>(adjacencySet[vertex].begin(), adjacencySet[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> prev_vertivces;

    for (int v = 0; v < VerticesCount(); v++)
    {
        for (auto next_v: adjacencySet[v])
        {
            if (next_v == vertex)
            {
                prev_vertivces.push_back(v);
                break;
            }
        }
    }
    return prev_vertivces;
}