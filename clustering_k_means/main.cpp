// A union-find algorithm to detect cycle in a graph
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// a structure to represent an edge in the graph
struct Edge
{
    int src, dst, cost;
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
        edge.dst = dst;
        edge.cost = cost;
        edges.push_back(edge);
    }
    void sortEdgesIncreasingCost()
    {
        std::sort(edges.begin(), edges.end(), sort_edges_const_increasing_order);
    }

    void print()
    {
        for (int i = 0; i < edges.size(); ++i)
            cout << edges[i].src << " --> " << edges[i].dst << ", " << edges[i].cost << endl;
    }

private:
    static bool sort_edges_const_increasing_order(const Edge& edge1, const Edge& edge2)
    {
        return edge1.cost < edge2.cost;
    }
};

// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};

// Creates a graph with V vertices
Graph* createGraph(int V)
{
    Graph* graph = new Graph;
    graph->V = V;

    return graph;
}


//// A utility function to find set of an element i
//// (uses path compression technique)
int find(vector<subset>& subsets, int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}



// A utility function to do union of two subsets
void Union(vector<subset>& subsets, int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].parent = yroot;
        subsets[yroot].rank += subsets[xroot].rank;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank += subsets[yroot].rank;
    }
    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank += subsets[yroot].rank;
    }
}

int k_clustering_max_spacing(Graph* graph, int k)
{
    graph->sortEdgesIncreasingCost();
//    cout << "sorted: " << endl;
//    graph->print();
    vector<subset> subsets(graph->V);

    int no_clusters = graph->V;

    // Create V subsets with single elements
    for (int v = 0; v < graph->V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    cout << "--------------------" << endl;
    int i = 0;
    while ( no_clusters > k-1 )
    {
        Edge next_edge = graph->edges[i++];

        int src_subset = find(subsets, next_edge.src);
        int dst_subset = find(subsets, next_edge.dst);

        if (src_subset != dst_subset)
        {
            cout << "Added " << i << "-th edge: " << next_edge.src << " --> " << next_edge.dst << ", " << next_edge.cost << endl;
            Union(subsets, src_subset, dst_subset);
            no_clusters--;
        }

    }

    return graph->edges[++i].cost;
}

Graph* read_input_file(char* input_file_path)
{
    Graph* graph = new Graph;
    ifstream data_file;
    data_file.open(input_file_path);
    if (data_file.is_open())
    {
//      [number_of_nodes]
//      [edge 1 node 1] [edge 1 node 2] [edge 1 cost]
//      [edge 2 node 1] [edge 2 node 2] [edge 2 cost]
        data_file >> graph->V;
        int src, dst, cost;
        while (data_file >> src >> dst >> cost)
        {
            graph->addEdge(src-1, dst-1, cost);
//            graph->addEdge(dst, src, cost);
        }
    }
    return graph;
}

// Driver program to test above functions
int main()
{
    char* input_data_path = "./clustering1.txt";
    Graph* graph = read_input_file(input_data_path);
//    graph->print();
    cout << "Max spacing: " << k_clustering_max_spacing(graph, 4) << endl;

//    int V = 9;
//    Graph* graph = createGraph(V);

//    graph->addEdge(1 ,2 ,4);
//    graph->addEdge(2 ,3 ,8);
//    graph->addEdge(3 ,4 ,7);
//    graph->addEdge(4 ,5 ,9);
//    graph->addEdge(5 ,6 ,10);
//    graph->addEdge(6 ,3 ,4);
//    graph->addEdge(6,7, 2);
//    graph->addEdge(7,8 ,1);
//    graph->addEdge(8 ,1, 8);
//    graph->addEdge(8 ,2 ,11);
//    graph->addEdge(8 ,0 ,7);
//    graph->addEdge(0 ,3 ,2);
//    graph->addEdge(0, 7 ,6);

//    graph->print();

//    cout << "Max spacing: " << k_clustering_max_spacing(graph, 4) << endl;

    return 0;
}
