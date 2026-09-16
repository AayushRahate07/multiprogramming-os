#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int p, r;

    cout << "Enter Number Of Processes : ";
    cin >> p;

    cout << "Enter Number Of Resources : ";
    cin >> r;

    vector<vector<int>> alloc(p, vector<int>(r));
    vector<vector<int>> need(p, vector<int>(r));
    vector<int> avail(r);

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> alloc[i][j];
        }
    }

    cout << "Enter Need Matrix:\n";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> need[i][j];
        }
    }

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < r; i++)
    {
        cin >> avail[i];
    }

    vector<bool> visited(p, false);
    vector<int> safeSequence;
    int count = 0;

    for (int i = 0; i < p; i++)
    {
        bool hasAllocation = false;
        for (int j = 0; j < r; j++)
        {
            if (alloc[i][j] > 0)
            {
                hasAllocation = true;
                break;
            }
        }
        if (!hasAllocation)
        {
            visited[i] = true;
            count++;
        }
    }

    for (int k = 0; k < p; k++)
    {
        bool deadlock = true;

        for (int i = 0; i < p; i++)
        {
            if (!visited[i])
            {
                bool possible = true;

                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if (possible)
                {
                    for (int j = 0; j < r; j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    visited[i] = true;
                    safeSequence.push_back(i);

                    deadlock = false;
                    count++;
                }
            }
        }

        if (deadlock)
        {
            break;
        }
    }

    if (count == p)
    {
        cout << "\nNo Deadlock Detected\n";

        cout << "Safe Sequence : ";

        for (int i : safeSequence)
        {
            cout << "P" << i << " ";
        }
    }
    else
    {
        cout << "\nDeadlock Detected\n";

        cout << "Processes In Deadlock : ";

        for (int i = 0; i < p; i++)
        {
            if (!visited[i])
            {
                cout << "P" << i << " ";
            }
        }
    }

    return 0;
}