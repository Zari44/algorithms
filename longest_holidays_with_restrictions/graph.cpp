#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const int NO_OF_MONTHS = 6;
using namespace std;

Graph::Graph() : _number_of_vertices(0)
{

}

void Graph::addEdge(int u, int v, int destination_value)
{
//    Vertex vertex(u,v,adj->at(u));
//    adj->at(u).append(vertex);
}

bool Graph::readFromFile(const char *file_path)
{
    adj = new vector<vector<Vertex>>;
    ifstream graph_file;
    graph_file.open(file_path);
    if (graph_file.is_open())
    {
        string line;
//        int no_offices;
//        if (getline(graph_file, line))
//            no_offices = atoi( line.c_str() );
        adj = new vector<vector<Vertex>>;
        while (getline(graph_file, line))
        {
            vector<Vertex> vertices;
            Vertex vertex;
            int pos1;
            string delimiter1 = " ";
            while ((pos1 = line.find(delimiter1)) != std::string::npos)
            {
                string vertex_info = line.substr(0, pos1).c_str();
                line.erase(0, pos1 + delimiter1.length());
                int pos2;
                string delimiter2 = ",";
                if ((pos2 = vertex_info.find(delimiter2)) != std::string::npos)
                {
                    vertex.value = atoi(vertex_info.substr(0, pos2).c_str());
                    vertex_info.erase(0, pos2 + delimiter2.length());
                    vertex.number = atoi(vertex_info.c_str());
                    vertices.push_back(vertex);
                }
            }
            _number_of_vertices++;
            adj->push_back(vertices);
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

Graph::Graph(const Graph& graph)
{
    _number_of_vertices = graph._number_of_vertices;
    adj = new vector<vector<Vertex>>;
    for (const auto& adj_list : (*graph.adj))
    {
        std::vector<Vertex> temp_list;
        for (const auto& vertex : adj_list)
        {
            temp_list.push_back(vertex);
        }
        adj->push_back(temp_list);
    }
}

Graph::~Graph()
{
    delete adj;
}


void Graph::print()
{
    for (const auto& edges_vector : (*adj))
    {
        static int indx = 0;
        cout << indx << " : ";
        indx++;
        for (const auto& vertex : (edges_vector))
            cout << vertex.number << "," << vertex.value << " ";
        cout << endl;
    }
    cout << "Number of vertices : " << getNumberOfVertices() << endl;
}
