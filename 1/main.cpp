#include "listgraph.hpp"
#include "matrixgraph.hpp"
#include "setgraph.hpp"
#include "arcgraph.hpp"
#include <assert.h>
#include <cassert>
#include <iostream>
#include <algorithm>
int main()
{
    ListGraph graph(8);
    assert(graph.VerticesCount() == 8);
    graph.AddEdge(1, 2);
    assert(graph.GetNextVertices(1) == std::vector<int> {2});
    graph.AddEdge(1, 3);
    assert((graph.GetNextVertices(1) == std::vector<int>{2, 3}));

    MatrixGraph mgraph(graph);
    assert(mgraph.VerticesCount() == 8);
    assert((mgraph.GetNextVertices(1) == std::vector<int>{2, 3}));

    SetGraph sgraph(mgraph);
    assert(sgraph.VerticesCount() == 8);
    std::vector<int> sorted_next_vertices = sgraph.GetNextVertices(1);
    std::sort(sorted_next_vertices.begin(), sorted_next_vertices.end());
    assert((sorted_next_vertices == std::vector<int>{2, 3}));

    ArcGraph agraph(sgraph);
    assert(agraph.VerticesCount() == 8);
    std::vector<int> sorted_next_vertices_2 = agraph.GetNextVertices(1);
    std::sort(sorted_next_vertices_2.begin(), sorted_next_vertices_2.end());
    assert((sorted_next_vertices_2 == std::vector<int>{2, 3}));

    std::cout << "ok" << std::endl;
    return 0;
}