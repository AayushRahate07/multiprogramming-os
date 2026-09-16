#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cout << "Enter Number Of Processes : ";
    cin >> n;

    vector<int> at(n), bt(n), pr(n), rem(n);
    vector<int> ct(n), wt(n), tat(n);

    cout << "Enter Arrival Times : ";
    for (int i = 0; i < n; i++)
    {
        cin >> at[i];
    }

    cout << "Enter Burst Times : ";
    for (int i = 0; i < n; i++)
    {
        cin >> bt[i];
        rem[i] = bt[i];
    }

    cout << "Enter Priorities : ";
    for (int i = 0; i < n; i++)
    {
        cin >> pr[i];
    }

    int complete = 0;
    int time = 0;

    while (complete < n)
    {
        int idx = -1;
        int best = 9999;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rem[i] > 0)
            {
                if (pr[i] < best)
                {
                    best = pr[i];
                    idx = i;
                }
                else if (pr[i] == best)
                {
                    if (at[i] < at[idx])
                    {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        rem[idx]--;
        time++;

        if (rem[idx] == 0)
        {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            complete++;
        }
    }

    cout << "\nPID\tAT\tBT\tPR\tCT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}