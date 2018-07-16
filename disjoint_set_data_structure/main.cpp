// A union-find algorithm to detect cycle in a graph
#include <iostream>
#include <vector>

using namespace std;

// a structure to represent an edge in the graph
struct Edge
{
    int src, dest, cost;
};

// a structure to represent a graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V;

    // graph is represented as an array of edges
    vector<Edge> edges;
    int getNumberOfEdges() {return edges.size();}
    void addEdge(int src, int dst, int cost = 0)
    {
        Edge edge;
        edge.src = src;
        edge.dest = dst;
        edge.cost = cost;
        edges.push_back(edge);
    }
};

// Creates a graph with V vertices
Graph* createGraph(int V)
{
    Graph* graph = new Graph;
    graph->V = V;

    return graph;
}

// A utility function to find the subset of an element i
int find(vector<int>& parent, int i)
{
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// A utility function to do union of two subsets
void Union(vector<int>& parent, int x, int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// The main function to check whether a given graph contains
// cycle or not
bool isCycle( Graph* graph )
{
    // Allocate memory for creating V subsets
    vector<int> parent(graph->V, -1);

    // Iterate through all edges of graph, find subset of both
    // vertices of every edge, if both subsets are same, then
    // there is cycle in graph.
    for(int i = 0; i < graph->getNumberOfEdges(); ++i)
    {
        int src_subset = find(parent, graph->edges[i].src);
        int dst_subset = find(parent, graph->edges[i].dest);

        if (src_subset == dst_subset)
            return true;

        Union(parent, src_subset, dst_subset);
    }
    return false;
}

// Driver program to test above functions
int main()
{
    /* Let us create the following graph
         0
        |  \
        |    \
        1-----2 */
    int V = 3;
    Graph* graph = createGraph(V);

    graph->addEdge(0,1);
    graph->addEdge(1,2);
    graph->addEdge(0,2);

    if (isCycle(graph))
        cout << "graph contains cycle" << endl;
    else
        cout << "graph doesn't contain cycle" << endl;

    return 0;
}
