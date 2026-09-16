#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int pageSize, n, LA;

    cout << "Enter Page Size : ";
    cin >> pageSize;

    cout << "Enter Number Of Pages : ";
    cin >> n;

    vector<int> pageTable(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter Frame for Page " << i << " : ";
        cin >> pageTable[i];
    }

    cout << "Enter LA : ";
    cin >> LA;

    int page = LA / pageSize;
    int offset = LA % pageSize;

    if (page < 0 || page >= n)
    {
        cout << "INVALID LA" << endl;
    }
    else
    {
        int frame = pageTable[page];
        int PA = (frame * pageSize) + offset;
        cout << "Physical Addr : " << PA << endl;
    }

    return 0;
}