#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Graph
{
    int no_nodes;
public:
    Graph(const int no_nodes, const int nodes_values[]);
    vector<vector<int> > *adj;
    vector<int> *adj_val;
    void addEdge(int node1, int node2);
    void print();
    int getNoNodes() { return no_nodes; }
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

void Graph::print()
{
    for (vector<vector<int> >::iterator it = adj->begin(); it != adj->end(); ++it)
    {
        for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
            cout << *it2 << " ";
        cout << endl;
    }

}

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
//        if (days_off[i] > max)
//            max = days_off[i];
        cout << days_off[i] << endl;
    }
    return max;
}

int main(int argc, char *argv[])
{
    const int number_of_nodes = 18;
    const int nodes_values[number_of_nodes] = {2,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,5};
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

    cout << find_optimal_offices(graph, 0) << endl;

    return 0;
}
