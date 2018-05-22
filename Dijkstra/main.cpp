#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Graph
{
    int no_nodes;
public:
    Graph(const int no_nodes, const int nodes_values[]);
    vector<vector<int> > *adj;
    vector<int> *adj_val;
    void addEdge(int node1, int node2);
    void print() const;
    int getNoNodes() const { return no_nodes; }
};

Graph::Graph(const int no_nodes, const int nodes_values[])
    : no_nodes(no_nodes)
{
    adj = new vector<vector<int> >(no_nodes);
    adj_val = new vector<int>(no_nodes);
    for (int i = 0; i < no_nodes; ++i)
        adj_val->at(i) = nodes_values[i];
}

void Graph::addEdge(int node1, int node2)
{
    (adj->at(node1)).push_back(node2);
}

void Graph::print() const
{
    for (vector<vector<int> >::iterator it = adj->begin(); it != adj->end(); ++it)
    {
        for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
            cout << *it2 << " ";
        cout << endl;
    }

}

//// ------------------------------- //
//class WeightedEdgesGraph{
//public:
//    int no_nodes;
//public:
//    struct Edge;
//    WeightedEdgesGraph();
//    vector<vector<Edge> > *adj;
//    void convertFrom(const Graph& graph);
//    void print();
//    int getNoNodes() { return no_nodes; }
//};

//struct WeightedEdgesGraph::Edge{
//    Edge(int head, int cost) : head(head), cost(cost) {}
//    int head;
//    int cost;
//};

//WeightedEdgesGraph::WeightedEdgesGraph()
//{
//    adj = NULL;
//}

//void WeightedEdgesGraph::convertFrom(const Graph &graph)
//{
//    no_nodes = graph.getNoNodes();
//    adj = new vector<vector<Edge> >(no_nodes);

//    for (int i = 0; i < graph.getNoNodes(); ++i)
//    {
//        for (int j = 0; j < graph.adj->at(j).size(); ++j)
//        {
//            Edge edge()
//        }
//    }
//}

// ------------------------------- //

void BFS_utils(Graph& graph, queue<int>& que, int start_node, bool visited[])
{
    vector<int>::iterator it;
    while (!que.empty())
    {
        start_node = que.front();
        que.pop();
        cout << start_node << endl;
        for ( it = (graph.adj->at(start_node)).begin(); it != (graph.adj->at(start_node)).end(); ++it)
        {
            if (visited[*it] == false)
            {
                que.push(*it);
                visited[*it] = true;
            }
        }
    }
}

void BFS(Graph& graph, int start_node)
{
    queue<int> que;
    bool visited[graph.getNoNodes()];
    for (int i = 0; i < graph.getNoNodes(); ++i)
        visited[i] = false;

    que.push(start_node);
    visited[start_node] = true;
    BFS_utils(graph, que, start_node, visited);
}

void find_optimal_offices_utils(Graph& graph, queue<int>& que, int start_node, int previous_node, bool visited[], int days_off[])
{
    vector<int>::iterator it;
    while (!que.empty())
    {
        start_node = que.front();
        que.pop();
        for ( it = (graph.adj->at(start_node)).begin(); it != (graph.adj->at(start_node)).end(); ++it)
        {
            if (visited[*it] == false)
            {
                que.push(*it);
                visited[*it] = true;
                previous_node = start_node;
                int day_off = days_off[previous_node] + graph.adj_val->at(*it);
                cout << "Current node: " << *it << " \t";
                cout << "Previous node: " << previous_node << " \t";
                cout << "Days off previous node: " << days_off[previous_node] << " \t";
                cout << "Days off: " << day_off << endl;
                if (days_off[*it] < day_off)
                    days_off[*it] = day_off;
            }
        }
    }
}

int find_optimal_offices(Graph& graph, int start_node)
{
    queue<int> que;
    bool visited[graph.getNoNodes()];
    int days_off[graph.getNoNodes()];
    int previous_node = 0;
    for (int i = 0; i < graph.getNoNodes(); ++i)
    {
        visited[i] = false;
        days_off[i] = 0;
    }

    que.push(start_node);
    visited[start_node] = true;
    days_off[start_node] = graph.adj_val->at(start_node);
    find_optimal_offices_utils(graph, que, start_node, previous_node, visited, days_off);

    int max = 0;
    for (int i = 0; i < graph.getNoNodes(); ++i)
    {
        if (days_off[i] > max)
            max = days_off[i];
        cout << days_off[i] << endl;
    }
    return max;
}

int find_min_distance(int distances[], bool visited[], int no_nodes)
{
    int min = 1000000, min_index;

    for (int i = 0; i < no_nodes; ++i)
    {
        if (visited[i] == false && distances[i] <= min)
            min = distances[i], min_index = i;
    }

    return min_index;
}

int find_max_distance(int distances[], bool visited[], int no_nodes)
{
    int max = -1, max_index;

    for (int i = 0; i < no_nodes; ++i)
        if (visited[i] == false && distances[i] >= max)
            max = distances[i], max_index = i;

    return max_index;
}

void Dijkstra(const Graph& graph, int start_node, int distance[], int previous[])
{
    bool visited[graph.getNoNodes()];
    vector<int> unvisited;
    for (int i = 0; i < graph.getNoNodes(); ++i)
    {
        distance[i] = 0;
        previous[i] = -1;
        visited[i] = false;
        unvisited.push_back(i);
    }
    distance[start_node] = graph.adj_val->at(start_node);

    int u;
    vector<int>::iterator v;
    while (!unvisited.empty())
    {
        u = find_max_distance(distance, visited, graph.getNoNodes());
        cout << "Min index: " << u << endl;
        unvisited.erase( std::remove(unvisited.begin(), unvisited.end(), u) );
        visited[u] = true;
        for ( v = (graph.adj->at(u)).begin(); v != (graph.adj->at(u)).end(); ++v)
        {
            int new_distance = distance[u] + graph.adj_val->at(*v);
            if (new_distance < distance[*v])
            {
                distance[*v] = new_distance;
                previous[*v] = u;
            }
        }
    }
}

int main()
{
    const int number_of_nodes = 18;
//    const int nodes_values[number_of_nodes] = {2,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,5};
    const int nodes_values[number_of_nodes] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    Graph graph(number_of_nodes, nodes_values);

    graph.addEdge(0,1);
    graph.addEdge(0,7);
    graph.addEdge(1,2);
    graph.addEdge(1,14);
    graph.addEdge(2,3);
    graph.addEdge(2,9);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(4,17);
    graph.addEdge(6,7);
    graph.addEdge(7,8);
    graph.addEdge(8,9);
    graph.addEdge(9,10);
    graph.addEdge(9,4);
    graph.addEdge(10,11);
    graph.addEdge(12,13);
    graph.addEdge(13,14);
    graph.addEdge(14,9);
    graph.addEdge(15,16);
    graph.addEdge(16,17);

    graph.print();
    cout << " --- " << endl;

//    cout << find_optimal_offices(graph, 0) << endl;

    int previous[graph.getNoNodes()];
    int distance[graph.getNoNodes()];
    Dijkstra(graph, 0, distance, previous);

    for (int i = 0; i < graph.getNoNodes(); ++i)
        if (previous[i] != -1)
            cout << previous[i] << " ";

    cout << " --- " << endl;

    for (int i = 0; i < graph.getNoNodes(); ++i)
        if (distance[i] != -1)
            cout << distance[i] << " ";

    return 0;
}
