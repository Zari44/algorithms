#include <iostream>

using namespace std;

int fibb(int n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return 1;
    else
        return fibb(n-1) + fibb(n-2);
}

int main(int argc, char *argv[])
{
    for (int n = 0; n < 10; ++n)
        cout << "Fibb (" << n << ") = " << fibb(n) << endl;

    return 0;
}
