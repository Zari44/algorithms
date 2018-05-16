#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
    struct Vertex{
        Vertex(int value = 0, int number = 0) : value(value), number(number) {}
        int value;
        int number;
    };
    void addEdge(int u, int v, int destination_value);
public:
    Graph();
    Graph(const Graph& graph);
    ~Graph();
    std::vector<std::vector<Vertex>>* adj;
    bool readFromFile(const char* file_path);
    void print();
};

#endif // GRAPH_H
