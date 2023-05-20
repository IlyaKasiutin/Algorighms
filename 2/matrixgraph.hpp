#include "igraph.hpp"

class MatrixGraph: public IGraph
{

public:
    MatrixGraph(int vertex_num);
    MatrixGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const  override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

    ~MatrixGraph() {}

private:
    std::vector<std::vector<int>> adjacencyMatrix;

};