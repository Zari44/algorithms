#include "graph.h"
#include <iostream>

using namespace std;

void find_optimal_offices(const Graph& graph)
{
    int number_of_free_days = 0;
    for (const auto& free_days : graph.adj)
    {
        int most_free_days_during_month = 0;
        int best_office_during_month = 0;
        for (int office = 0; office < free_days.size(); ++office)
        {
            if (free_days.at(office) > most_free_days_during_month)
            {
                most_free_days_during_month = free_days.at(office);
                best_office_during_month = office;
            }
        }
        number_of_free_days += most_free_days_during_month;
        cout << best_office_during_month << " ";
    }
    cout << endl << "Number of free days during the year: " << number_of_free_days << endl;
}

int main()
{
    Graph graph;
    if (!graph.readFromFile("../longest_holidays/offices.txt"))
    {
        return 0;
    }
    graph.print();
    find_optimal_offices(graph);
    return 0;
}
