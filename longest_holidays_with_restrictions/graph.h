#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
    struct Vertex{
        Vertex(int value, int number, std::vector<Vertex>* adj)
            : value(value), number(number), adj(adj) {}
        int value;
        int number;
        std::vector<Vertex>* adj;
    };
    void addEdge(int u, int v);
public:
    Graph();
    Graph(const Graph& graph);
    ~Graph();
    std::vector<Vertex>* adj;
    bool readFromFile(const char* file_path);
    void print();
};

#endif // GRAPH_H
