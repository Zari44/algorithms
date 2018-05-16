#include "graph.h"
#include <iostream>

using namespace std;

int main()
{
    Graph graph;
    if (!graph.readFromFile("../longest_holidays_with_restrictions/offices.txt"))
        return 0;
    graph.print();
    return 0;
}
