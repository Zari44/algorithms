#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Graph::Graph()
{

}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(v);
}

bool Graph::readFromFile(const char *file_path)
{
    ifstream graph_file;
    graph_file.open(file_path);
    if (graph_file.is_open())
    {
        string line;
//        int no_vertices;
//        if (getline(graph_file, line))
//            no_vertices = atoi( line.c_str() );
        while (getline(graph_file, line))
        {
            vector<int> temp;
            int vertex_i;
            int pos;
            string delimiter = " ";
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                vertex_i = atoi(line.substr(0, pos).c_str());
                temp.push_back(vertex_i);
                line.erase(0, pos + delimiter.length());
            }
            adj.push_back(temp);
        }
        graph_file.close();
        return true;
    }
    else
    {
        cout << "Unable to open file" << endl;
        return false;
    }
}

void Graph::print()
{
    for (const auto& edges_vector : adj)
    {
        for (const auto& vertex : edges_vector)
            cout << vertex << " ";
        cout << endl;
    }
    cout << "Number of offices: " << adj.size() << endl;
}
