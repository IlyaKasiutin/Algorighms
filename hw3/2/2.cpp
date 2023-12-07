#include <assert.h>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

struct IGraph {
    virtual ~IGraph() {}
        
        // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

};

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



void bfs_aux(const IGraph& graph, int start, int stop, std::vector<int>& d, std::vector<int>& k)
{
    std::queue<int> order;
    order.push(start);

    while(!order.empty())
    {
        int current_vertex = order.front();
        order.pop();

        for (auto next_vertex: graph.GetNextVertices(current_vertex))
        {
            if (k[next_vertex] == 0)
            {
                d[next_vertex] = d[current_vertex] + 1;
                k[next_vertex] = k[current_vertex];
                
                order.push(next_vertex);
            }

            else if (d[current_vertex] + 1 == d[next_vertex])
            {
                k[next_vertex] += k[current_vertex];
            }
        }
    }
}

int count_nearest_paths(const IGraph& graph, int start, int stop)
{
    std::vector<int> d(graph.VerticesCount(), INT8_MAX);
    d[start] = 0;
    std::vector<int> k(graph.VerticesCount(), 0);
    k[start] = 1;

    bfs_aux(graph, start, stop, d, k);

    return k[stop];
}

int main()
{
    int v = 0, n = 0;
    std::cin >> v >> n;

    ListGraph graph(v);

    for (int i = 0; i < n; ++i)
    {
        int first = 0, second = 0;
        std::cin >> first >> second;
        graph.AddEdge(first, second);
        graph.AddEdge(second, first);
    }

    int start = 0, stop = 0;
    std::cin >> start >> stop;
    std::cout << count_nearest_paths(graph, start, stop) << std::endl;

}