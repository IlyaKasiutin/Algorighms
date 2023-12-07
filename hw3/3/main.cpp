/*
Требуется отыскать самый короткий маршрут между городами. 
Из города может выходить дорога, которая возвращается в этот же город.
Требуемое время работы O((N + M)log N), где N – количество городов, 
M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.
*/

#include <iostream>
#include <vector>
#include <assert.h>
#include <set>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, std::pair<int, int> to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

};

class ListGraph: public IGraph
{

public:
    ListGraph(int vertex_num);
    ListGraph(const IGraph& graph);

    virtual void AddEdge(int from, std::pair<int, int> to) override;
    virtual int VerticesCount() const  override;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~ListGraph() {}

private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;

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

void ListGraph::AddEdge(int from, std::pair<int, int> to)
{
    assert(0 <= from && from < VerticesCount());
    assert(0 <= to.second && to.second < VerticesCount());

    adjacencyList[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
    return adjacencyList.size();
}

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const
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
            if (next_v.second == vertex)
            {
                prev_vertivces.push_back(v);
                break;
            }
        }
    }
    return prev_vertivces;
}

bool Relax(int u, int v, int time, std::vector<int>& d)
{
    if (d[v] > d[u] + time)
    {
        return true;
    }
    return false;
}

int Dijkstra(const IGraph& graph, int begin, int end)
{
    std::vector<int> d(graph.VerticesCount(), INT32_MAX);
    d[begin] = 0;
    auto cmp = [](std::pair<int, int> left, std::pair<int, int> right)
    {
        if (left.first < right.first)
            return true;
        else if (left.first == right.first)
        {
            if (left.second < right.second)
                return true;
        }
        return false;
    };
    std::set<std::pair<int, int>, decltype(cmp)> q(cmp);

    q.insert({0, begin});
    while (!q.empty())
    {
        auto current_vertex = (*q.begin()).second;
        q.erase(q.begin());
        for (auto next_vertex: graph.GetNextVertices(current_vertex))
        {
            if (d[next_vertex.second] == INT32_MAX)
            {
                d[next_vertex.second] = d[current_vertex] + next_vertex.first;
                q.insert(next_vertex);
            }
            else if (Relax(current_vertex, next_vertex.second, next_vertex.first, d))
            {
                int new_shortest_path = d[current_vertex] + next_vertex.first;
                auto prev_shortest_path = q.find({d[next_vertex.second], next_vertex.second});
                d[next_vertex.second] = new_shortest_path;
                if (prev_shortest_path != q.end())
                    q.erase(prev_shortest_path);
                q.insert({d[next_vertex.second], next_vertex.second});
            }
        }
    }
    return d[end];
}

int main()
{
    int n = 0, m = 0;
    std::cin >> n;
    std::cin >> m;

    ListGraph graph(n);
    for (int i = 0; i < m; ++i)
    {
        int begin = 0, end = 0, time = 0;
        std::cin >> begin >> end >> time;
        graph.AddEdge(begin, {time, end});
        graph.AddEdge(end, {time, begin});

    }

    int start = 0, stop = 0;
    std::cin >> start >> stop;
    std::cout << Dijkstra(graph, start, stop) << std::endl;
    return 0;
}