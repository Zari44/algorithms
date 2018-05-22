#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    int no_nodes;
public:
    struct Edge;
    Graph(const int no_nodes, const int nodes_values[]);
    vector<vector<Edge> > *adj;
    vector<int> *adj_val;
    void addEdge(int node1, int node2);
    void print() const;
    int getNoNodes() const { return no_nodes; }
    int getNodeValue(int node) const { return adj_val->at(node); }
};

struct Graph::Edge
{
    Edge(int head_node, bool visited = false)
        : head_node(head_node), visited(visited) {}
    int head_node;
    bool visited;
};

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


bool has_all_edges_from_node_been_visited(const Graph& graph, int node)
{
    vector<Graph::Edge> edges = graph.adj->at(node);
    for (const auto& edge : edges)
        if (!edge.visited)
            return false;
    return true;
}

void find_optimal_offices_utils(Graph& graph, queue<Graph::Edge>& que, int start_node, int previous_node[], bool visited_edges[], int days_off[])
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
                int day_off = days_off[start_node] + graph.adj_val->at(edge->head_node);
                if (days_off[edge->head_node] < day_off)
                {
                    days_off[edge->head_node] = day_off;
                    previous_node[edge->head_node] = start_node;
                }
                cout << "Current node: " << edge->head_node << " \t";
                cout << "Previous node : " << start_node <<  " \t";
                cout << "Days off previous node: " << days_off[start_node] << " \t";
                cout << "Days off: " << day_off << endl;
            }
        }
    }
}

int find_optimal_offices(Graph& graph, int previous_node[], int start_node, int& best_last_office)
{
    queue<Graph::Edge> que;
    bool visited[graph.getNoNodes()];
    int days_off[graph.getNoNodes()];

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
        if (days_off[i] > max)
        {
            max = days_off[i];
            best_last_office = i;
        }

    return max;
}

void print_best_offices(int previous[], int best_last_office, int starting_office)
{
    int index = best_last_office;

    cout << "Best offices in reverse order: ";
    while (index != starting_office)
    {
        cout << index << " ";
        index = previous[index];
    }
    cout << starting_office << endl;

}

int main(int argc, char *argv[])
{
    const int number_of_nodes = 18;
    const int nodes_values[number_of_nodes] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1};
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

    cout << " --- graph --- " << endl;
    graph.print();

    cout << " --- " << endl;

    int previous_node[graph.getNoNodes()];
    int starting_node = 0;
    int best_last_office = 0;

    cout << "max = " << find_optimal_offices(graph, previous_node, starting_node, best_last_office) << endl;
    cout << "best last office = " << best_last_office << endl;
    print_best_offices(previous_node, best_last_office, starting_node);
    return 0;
}
