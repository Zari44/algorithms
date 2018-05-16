#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
public:
    Graph();
    Graph(const Graph& graph);
    std::vector<std::vector<int> > adj;
    bool readFromFile(const char* file_path);
    void addEdge(int u, int v);
    void print();
};

#endif // GRAPH_H
