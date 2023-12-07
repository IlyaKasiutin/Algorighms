#include "igraph.hpp"
#include <utility>

class ArcGraph: public IGraph
{

public:
    ArcGraph(int vertex_num);
    ArcGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const  override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~ArcGraph() {}

private:
    std::vector<std::pair<int, int>> edgesList;
    int vertices_count;

};