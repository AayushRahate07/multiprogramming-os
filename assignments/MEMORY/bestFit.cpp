#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int b;
    cout << "Enter Number Of Blocks : ";
    cin >> b;

    vector<int> blocks(b);
    cout << "Enter Blocks : ";
    for (int i = 0; i < b; i++)
    {
        cin >> blocks[i];
    }

    int p;
    cout << "Enter Size Of Process : ";
    cin >> p;

    vector<int> smaller;
    for (int i = 0; i < b; i++)
    {
        if (blocks[i] >= p)
        {
            smaller.push_back(blocks[i]);
        }
    }
    sort(smaller.begin(), smaller.end());

    if (smaller.empty())
    {
        cout << "Cannot Allocate";
        return 0;
    }

    for (int j = 0; j < b; j++)
    {
        if (blocks[j] == smaller[0])
        {
            blocks[j] = blocks[j] - p;
            break;
        }
    }

    for (int i = 0; i < b; i++)
    {
        cout << blocks[i] << " ";
    }
}
