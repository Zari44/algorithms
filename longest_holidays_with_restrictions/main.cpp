#include "graph.h"
#include <iostream>

using namespace std;

void DFS(Graph& graph, bool visited[], int start_node)
{
    cout << start_node << " ";
    visited[start_node] = true;

    vector<Graph::Vertex>::iterator it;
    for (it = (graph.adj->at(start_node)).begin(); it != (graph.adj->at(start_node)).end(); ++it)
        if (!visited[it->number])
            DFS(graph, visited, it->number);
}

void find_optimal_offices(const Graph& graph)
{
    Graph copy_graph(graph);

    bool *visited;
    int no_vert = copy_graph.getNumberOfVertices();
    visited = new bool[no_vert];
    for (int i = 0; i < no_vert; ++i)
        visited[i] = false;

    DFS(copy_graph, visited, 0);
    delete []visited;
}

int main()
{
    Graph graph;
    if (!graph.readFromFile("../longest_holidays_with_restrictions/offices.txt"))
        return 0;
    graph.print();
    cout << " --- " << endl;
    find_optimal_offices(graph);
    return 0;
}
