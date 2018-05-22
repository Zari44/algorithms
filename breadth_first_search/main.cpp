#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Graph
{
    int no_nodes;
public:
    struct Edge;
    Graph(const int no_nodes, const int nodes_values[]);
    Graph();
    vector<vector<Edge> > *adj;
    vector<int> *adj_val;
    void addEdge(int node1, int node2);
    void print() const;
    int getNoNodes() const { return no_nodes; }
    int getNodeValue(int node) const { return adj_val->at(node); }
    void copyToInverse(Graph& inverseGraph);
};

struct Graph::Edge
{
    Edge(int head_node, bool visited = false)
        : head_node(head_node), visited(visited) {}
    int head_node;
    bool visited;
};

Graph::Graph() :
    no_nodes(0), adj(NULL), adj_val(NULL)
{
}

Graph::Graph(const int no_nodes, const int nodes_values[])
    : no_nodes(no_nodes)
{
    adj = new vector<vector<Edge> >(no_nodes);
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
    for (vector<vector<Edge> >::iterator adj_list = adj->begin(); adj_list != adj->end(); ++adj_list)
    {
        for (vector<Edge>::iterator edge = adj_list->begin(); edge != adj_list->end(); ++edge)
            cout << edge->head_node << " ";
        cout << endl;
    }
}

void Graph::copyToInverse(Graph &inverseGraph)
{
    inverseGraph.no_nodes = no_nodes;
    inverseGraph.adj = new vector<vector<Edge> >(inverseGraph.no_nodes);
    inverseGraph.adj_val = new vector<int>(inverseGraph.no_nodes);

    for (int i =0; i < inverseGraph.no_nodes; ++i)
    {
        inverseGraph.adj_val->at(i) = (*adj_val).at(i);
    }

    for (int u = 0; u < adj->size(); ++u)
    {
        vector<Edge> heads = adj->at(u);
        for (int v = 0; v < heads.size(); ++v)
        {
            int node = heads[v].head_node;
            Edge edge_u(u);
            (inverseGraph.adj->at(node)).push_back(edge_u);
        }
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

//void BFS_utils(Graph& graph, queue<int>& que, int start_node, bool visited[])
//{
//    vector<int>::iterator it;
//    while (!que.empty())
//    {
//        start_node = que.front();
//        que.pop();
//        cout << start_node << endl;
//        for ( it = (graph.adj->at(start_node)).begin(); it != (graph.adj->at(start_node)).end(); ++it)
//        {
//            if (visited[*it] == false)
//            {
//                que.push(*it);
//                visited[*it] = true;
//            }
//        }
//    }
//}

//void BFS(Graph& graph, int start_node)
//{
//    queue<int> que;
//    bool visited[graph.getNoNodes()];
//    for (int i = 0; i < graph.getNoNodes(); ++i)
//        visited[i] = false;

//    que.push(start_node);
//    visited[start_node] = true;
//    BFS_utils(graph, que, start_node, visited);
//}

bool has_all_edges_from_node_been_visited(const Graph& graph, int node)
{
    vector<Graph::Edge> edges = graph.adj->at(node);
    for (const auto& edge : edges)
        if (!edge.visited)
            return false;
    return true;
}

void find_optimal_offices_utils(Graph& graph, queue<Graph::Edge>& que, int start_node, int previous_node, bool visited_edges[], int days_off[])
{
    vector<Graph::Edge>::iterator edge;
    while (!que.empty())
    {
        start_node = que.front().head_node;
        que.pop();
        for ( edge = (graph.adj->at(start_node)).begin(); edge != (graph.adj->at(start_node)).end(); ++edge)
        {
            if (visited_edges[edge->head_node] == false)
            {
                que.push(*edge);
                if (has_all_edges_from_node_been_visited(graph, edge->head_node))
                    visited_edges[edge->head_node] = true;
                previous_node = start_node;
                int day_off = days_off[previous_node] + graph.adj_val->at(edge->head_node);
                cout << "Current node: " << edge->head_node << " \t";
                cout << "Previous node: " << previous_node << " \t";
                cout << "Days off previous node: " << days_off[previous_node] << " \t";
                cout << "Days off: " << day_off << endl;
                if (days_off[edge->head_node] < day_off)
                    days_off[edge->head_node] = day_off;
            }
        }
    }
}

int find_optimal_offices(Graph& graph, int start_node)
{
    queue<Graph::Edge> que;
    bool visited[graph.getNoNodes()];
    int days_off[graph.getNoNodes()];
    int previous_node = 0;
    int start_edge = 0;

    for (int i = 0; i < graph.getNoNodes(); ++i)
    {
        visited[i] = false;
        days_off[i] = 0;
    }

    que.push(start_node);
    graph.adj->at(start_node).at(start_edge).visited = true;
    if (has_all_edges_from_node_been_visited(graph, start_node))
        visited[start_node] = true;
    days_off[start_node] = graph.getNodeValue(start_node);
    find_optimal_offices_utils(graph, que, start_node, previous_node, visited, days_off);

    int max = 0;
    for (int i = 0; i < graph.getNoNodes(); ++i)
    {
        if (days_off[i] > max)
            max = days_off[i];
        cout << days_off[i] << " ";
    }
    cout << endl;
    return max;
}

int main(int argc, char *argv[])
{
    const int number_of_nodes = 18;
    const int nodes_values[number_of_nodes] = {2,2,1,1,3,1,1,1,2,2,2,1,1,1,3,1,1,4};
//    const int nodes_values[number_of_nodes] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1};
    Graph graph(number_of_nodes, nodes_values);
    Graph inversed_graph;

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

    graph.copyToInverse(inversed_graph);

    cout << " --- graph --- " << endl;
    graph.print();
    cout << " --- inversed graph --- " << endl;
    inversed_graph.print();

    cout << " --- " << endl;

    cout << "max = " << find_optimal_offices(graph, 0) << endl;

    return 0;
}
