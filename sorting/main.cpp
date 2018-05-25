#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool is_element_present(int matrix[][4], int element, int N, int M)
{

    return true;
}

int main()
{
    const int N = 3;
    const int M = 4;
    int matrix[N][M] = {{2,4,5,8},
                        {3,6,7,10},
                        {9,11,12,13}};
    int element = 7;

    cout << is_element_present(matrix, element, N, M) << endl;

    return 0;
}
