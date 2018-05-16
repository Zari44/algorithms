#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
    int _number_of_vertices;
    void addEdge(int u, int v, int destination_value);
public:
    struct Vertex{
        Vertex(int value = 0, int number = 0) : value(value), number(number) {}
        Vertex(const Vertex& vertex) { value = vertex.value; number = vertex.number; }
        int value;
        int number;
    };
    Graph();
    Graph(const Graph& graph);
    ~Graph();
    std::vector<std::vector<Vertex>>* adj;
    bool readFromFile(const char* file_path);
    void print();
    int getNumberOfVertices() { return _number_of_vertices; }
};

#endif // GRAPH_H
