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



void find_optimal_path(Graph& graph, Graph::Vertex& start_node, bool visited[], vector<int>& path, int& path_score, vector<int>& best_path, int& best_path_score)
{
    visited[start_node.number] = true;
    path.push_back(start_node.number);
    path_score += start_node.value;

    if (graph.adj->at(start_node.number).empty())
    {
        if (best_path.empty() || path_score > best_path_score)
        {
            best_path = path;
            best_path_score = path_score;
        }
    }
    else
    {
        vector<Graph::Vertex>::iterator it;
        for (it = graph.adj->at(start_node.number).begin(); it != graph.adj->at(start_node.number).end(); ++it)
            if (!visited[it->number])
                find_optimal_path(graph, *it, visited, path, path_score, best_path, best_path_score);
    }
    path.pop_back();
    visited[start_node.number] = false;
}

void get_best_path(Graph& graph, Graph::Vertex& start_node)
{
    Graph copy_graph(graph);
    bool *visited;
    int no_vert = copy_graph.getNumberOfVertices();
    visited = new bool[no_vert];
    for (int i = 0; i < no_vert; ++i)
        visited[i] = false;
    vector<int> path;
    vector<int> best_path;
    int path_score = 0;
    int best_path_score = 0;

    find_optimal_path(copy_graph, start_node, visited, path, path_score, best_path, best_path_score);

    for (const auto& vertex : best_path)
        cout << vertex<< " ";
    cout << endl << "Path score is: " << best_path_score << endl;
}



int main()
{
    Graph graph;
    if (!graph.readFromFile("../longest_holidays_with_restrictions/offices.txt"))
        return 0;
    graph.print();
    cout << " --- " << endl;
    find_optimal_offices(graph);
    cout << "\n --- " << endl;
    Graph::Vertex first_node((graph.adj->at(0)).at(0));
    get_best_path(graph, first_node);
    return 0;
}
