#include "listgraph.hpp"
#include <assert.h>

ListGraph::ListGraph(int vertex_num): adjacencyList(vertex_num)
{

}

ListGraph::ListGraph(const IGraph& graph): adjacencyList(graph.VerticesCount())
{
    for (int i = 0; i < VerticesCount(); i++)
    {
        adjacencyList[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < VerticesCount());
    assert(0 <= to && to < VerticesCount());

    adjacencyList[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
    return adjacencyList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    return adjacencyList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> prev_vertivces;

    for (int v = 0; v < VerticesCount(); v++)
    {
        for (auto next_v: adjacencyList[v])
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