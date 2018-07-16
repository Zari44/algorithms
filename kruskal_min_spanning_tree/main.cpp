//// C++ program for Kruskal's algorithm to find Minimum Spanning Tree
//// of a given connected, undirected and weighted graph
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>




//// A function that does union of two sets of x and y
//// (uses union by rank)
//void Union(struct subset subsets[], int x, int y)
//{
//    int xroot = find(subsets, x);
//    int yroot = find(subsets, y);

//    // Attach smaller rank tree under root of high
//    // rank tree (Union by Rank)
//    if (subsets[xroot].rank < subsets[yroot].rank)
//        subsets[xroot].parent = yroot;
//    else if (subsets[xroot].rank > subsets[yroot].rank)
//        subsets[yroot].parent = xroot;

//    // If ranks are same, then make one as root and
//    // increment its rank by one
//    else
//    {
//        subsets[yroot].parent = xroot;
//        subsets[xroot].rank++;
//    }
//}

//// Compare two edges according to their weights.
//// Used in qsort() for sorting an array of edges
//int myComp(const void* a, const void* b)
//{
//    struct Edge* a1 = (struct Edge*)a;
//    struct Edge* b1 = (struct Edge*)b;
//    return a1->weight > b1->weight;
//}

//// The main function to construct MST using Kruskal's algorithm
//void KruskalMST(struct Graph* graph)
//{
//    int V = graph->V;
//    struct Edge result[V];  // Tnis will store the resultant MST
//    int e = 0;  // An index variable, used for result[]
//    int i = 0;  // An index variable, used for sorted edges

//    // Step 1:  Sort all the edges in non-decreasing
//    // order of their weight. If we are not allowed to
//    // change the given graph, we can create a copy of
//    // array of edges
//    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

//    // Allocate memory for creating V ssubsets
//    struct subset *subsets =
//        (struct subset*) malloc( V * sizeof(struct subset) );

//    // Create V subsets with single elements
//    for (int v = 0; v < V; ++v)
//    {
//        subsets[v].parent = v;
//        subsets[v].rank = 0;
//    }

//    // Number of edges to be taken is equal to V-1
//    while (e < V - 1)
//    {
//        // Step 2: Pick the smallest edge. And increment
//        // the index for next iteration
//        struct Edge next_edge = graph->edge[i++];

//        int x = find(subsets, next_edge.src);
//        int y = find(subsets, next_edge.dest);

//        // If including this edge does't cause cycle,
//        // include it in result and increment the index
//        // of result for next edge
//        if (x != y)
//        {
//            result[e++] = next_edge;
//            Union(subsets, x, y);
//        }
//        // Else discard the next_edge
//    }

//    // print the contents of result[] to display the
//    // built MST
//    printf("Following are the edges in the constructed MST\n");
//    for (i = 0; i < e; ++i)
//        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
//                                                 result[i].weight);
//    return;
//}

//// Driver program to test above functions
//int main()
//{
//    /* Let us create following weighted graph
//             10
//        0--------1
//        |  \     |
//       6|   5\   |15
//        |      \ |
//        2--------3
//            4       */
//    int V = 4;  // Number of vertices in graph
//    int E = 5;  // Number of edges in graph
//    struct Graph* graph = createGraph(V, E);


//    // add edge 0-1
//    graph->edge[0].src = 0;
//    graph->edge[0].dest = 1;
//    graph->edge[0].weight = 10;

//    // add edge 0-2
//    graph->edge[1].src = 0;
//    graph->edge[1].dest = 2;
//    graph->edge[1].weight = 6;

//    // add edge 0-3
//    graph->edge[2].src = 0;
//    graph->edge[2].dest = 3;
//    graph->edge[2].weight = 5;

//    // add edge 1-3
//    graph->edge[3].src = 1;
//    graph->edge[3].dest = 3;
//    graph->edge[3].weight = 15;

//    // add edge 2-3
//    graph->edge[4].src = 2;
//    graph->edge[4].dest = 3;
//    graph->edge[4].weight = 4;

//    KruskalMST(graph);

//    return 0;
//}

// A union-find algorithm to detect cycle in a graph
#include <iostream>
#include <vector>
#include <algorithm>

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
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void kruskalMST(Graph* graph)
{
    Graph* MST = createGraph(graph->V);
    // Step 1:  Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    graph->sortEdgesIncreasingCost();
    vector<subset> subsets(graph->V);

    // Create V subsets with single elements
    for (int v = 0; v < graph->V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

//    MST->addEdge(graph->edges[0].src, graph->edges[0].dst, graph->edges[0].cost);

    for (int i = 0; i < graph->getNumberOfEdges(); ++i)
    {
        Edge next_edge = graph->edges[i];

        int src_subset = find(subsets, next_edge.src);
        int dst_subset = find(subsets, next_edge.dst);

//        cout << "src subset " << src_subset << ", dst subset " << dst_subset << endl;
        if (src_subset != dst_subset)
        {
            MST->addEdge(graph->edges[i].src, graph->edges[i].dst, graph->edges[i].cost);
            Union(subsets, src_subset, dst_subset);
        }
    }

    MST->print();
}

// Driver program to test above functions
int main()
{
    /*
     *  Let us create the following graph
         0
        |  \
        |    \
        1-----2
    *
    */

    int V = 3;
    Graph* graph = createGraph(V);

    graph->addEdge(0,1,1);
    graph->addEdge(1,2,1);
    graph->addEdge(0,2,2);

//    if (isCycle(graph))
//        cout << "graph contains cycle" << endl;
//    else
//        cout << "graph doesn't contain cycle" << endl;

    kruskalMST(graph);

    return 0;
}



