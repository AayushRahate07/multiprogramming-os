#include <iostream>
using namespace std;

int main()
{
    int m, p;
    cout << "Enter Memory Size : ";
    cin >> m;

    cout << "Enter Process Size : ";
    cin >> p;

    int block = 1;
    while (block < p)
    {
        block = block * 2;
    }

    if (block > m)
    {
        cout << "BULLSHIT" << endl;
    }
    else
    {
        cout << "Memory : " << m - block << endl;
        cout << "Blocks : " << block << endl;
    }

    return 0;
}