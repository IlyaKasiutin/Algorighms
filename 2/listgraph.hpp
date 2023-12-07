#include "igraph.hpp"

class ListGraph: public IGraph
{

public:
    ListGraph(int vertex_num);
    ListGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const  override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~ListGraph() {}

private:
    std::vector<std::vector<int>> adjacencyList;

};