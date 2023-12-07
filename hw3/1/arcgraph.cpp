#include "arcgraph.hpp"
#include <assert.h>

ArcGraph::ArcGraph(int vertex_num): edgesList(0), vertices_count(vertex_num)
{

}

ArcGraph::ArcGraph(const IGraph& graph): edgesList(0), vertices_count(graph.VerticesCount())
{
    for (int i = 0; i < VerticesCount(); i++)
    {
        for(auto next_vertex: graph.GetNextVertices(i))
        {
            edgesList.push_back(std::pair<int, int>(i, next_vertex));
        }
    }
}

void ArcGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < VerticesCount());
    assert(0 <= to && to < VerticesCount());

    edgesList.push_back(std::pair<int, int>(from, to));
}

int ArcGraph::VerticesCount() const
{
    return vertices_count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
    std::vector<int> next_vertices;
    for (auto pair: edgesList)
    {
        if (pair.first == vertex)
            next_vertices.push_back(pair.second);
    }
    return next_vertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> prev_vertivces;

    for (auto pair: edgesList)
    {
        if (pair.second == vertex)
            prev_vertivces.push_back(pair.first);
    }
    return prev_vertivces;
}