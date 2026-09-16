#include <iostream>
#include <vector>
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

    int ptr = 0;
    int count = 0;

    int p;
    cout << "Enter Size Of Process : ";
    cin >> p;

    bool allocated = false;

    while (count < b)
    {
        if (blocks[ptr] >= p)
        {
            cout << "\nProcess allocated to Block " << ptr << endl;
            cout << "Block size changed from " << blocks[ptr] << " to " << blocks[ptr] - p << endl;
            
            blocks[ptr] = blocks[ptr] - p;
            allocated = true;
            break;
        }
        else
        {
            ptr = (ptr + 1) % b;
            count++;
        }
    }

    if (!allocated)
    {
        cout << "\nProcess could not be allocated: Insufficient memory blocks." << endl;
    }

    return 0;
}

/*
#include <iostream>
#include <vector>
#include <iomanip>
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

    int pSize;
    cout << "Enter Number Of Processes : ";
    cin >> pSize;

    vector<int> processes(pSize);
    cout << "Enter Processes : ";
    for (int i = 0; i < pSize; i++)
    {
        cin >> processes[i];
    }

    int ptr = 0;

    cout << "\n" << setw(15) << left << "PROCESS SIZE" << setw(15) << left << "ALLOCATED BLOCK" << endl;
    cout << "---------------------------------------" << endl;

    for (int i = 0; i < pSize; i++)
    {
        int count = 0;
        bool allocated = false;

        while (count < b)
        {
            if (blocks[ptr] >= processes[i])
            {
                cout << setw(15) << left << processes[i] << "Block " << ptr << " (" << blocks[ptr] << " -> " << blocks[ptr] - processes[i] << ")" << endl;
                blocks[ptr] -= processes[i];
                allocated = true;
                break;
            }
            
            ptr = (ptr + 1) % b;
            count++;
        }

        if (!allocated)
        {
            cout << setw(15) << left << processes[i] << "Not Allocated" << endl;
        }
    }

    return 0;
}

*/