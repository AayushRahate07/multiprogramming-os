#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int p, r;
    cout << "Enter Number Of Processes : ";
    cin >> p;

    cout << "Enter Number Of Resources : ";
    cin >> r;

    int max[p][r], need[p][r], avail[r];
    vector<vector<int>> alloc(p, vector<int>(r));

    cout << "Allocated Resources : ";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> alloc[i][j];
        }
    }

    cout << "Maximum Resources : ";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> max[i][j];
        }
    }

    cout << "Needed Resources : ";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Available Resources : ";
    for (int i = 0; i < r; i++)
    {
        cin >> avail[i];
    }

    vector<bool> visited(p, false);
    vector<int> safeSequence(p);
    int count = 0;

    for (int k = 0; k < p; k++)
    {
        bool deadlock = true;

        for (int i = 0; i < p; i++)
        {
            bool flag = true;
            if (!visited[i])
            {
                for (int j = 0; j < r; j++)
                {
                    if (avail[j] < need[i][j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    cout << "\nAvailable Resources before execution : ";
                    for (int k = 0; k < r; k++)
                    {
                        cout << avail[k] << " ";
                    }
                    cout << endl;

                    cout << "Needed Resources by process : ";
                    for (int k = 0; k < r; k++)
                    {
                        cout << need[i][k] << " ";
                    }
                    cout << endl;

                    cout << "Process P" << i << " executing" << endl;

                    cout << "Available Resources after execution : ";
                    for (int k = 0; k < r; k++)
                    {
                        avail[k] += alloc[i][k];
                        cout << avail[k] << " ";
                    }
                    cout << endl;

                    visited[i] = true;
                    deadlock = false;
                    safeSequence[count] = i;
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
        cout << "\nSystem is in a Safe State.\nSafe Sequence: ";
        for (int i = 0; i < p; i++)
        {
            cout << "P" << safeSequence[i] << (i == p - 1 ? "" : " -> ");
        }
        cout << endl;
    }

    return 0;
}