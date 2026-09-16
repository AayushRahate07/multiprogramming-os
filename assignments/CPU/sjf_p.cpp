#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), rem_bt(n), ct(n), wt(n), tat(n);

    cout << "Enter arrival times: ";
    for (int i = 0; i < n; i++)
        cin >> at[i];

    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++)
    {
        cin >> bt[i];
        rem_bt[i] = bt[i];
    }

    int time = 0, count = 0;
    int totalWT = 0, totalTAT = 0;
    int prev = -1;

    cout << "\nGantt Chart (Time-steps) :\n"
         << time;

    while (count < n)
    {
        int idx = -1;
        int min_rem = 99999;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rem_bt[i] > 0)
            {
                if (rem_bt[i] < min_rem)
                {
                    min_rem = rem_bt[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            if (prev != idx)
            {
                cout << " | P" << idx << " | " << time;
                prev = idx;
            }

            rem_bt[idx]--;
            time++;

            if (rem_bt[idx] == 0)
            {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                totalWT += wt[idx];
                totalTAT += tat[idx];
                count++;
            }
        }
        else
        {
            time++;
            cout << " | IDLE | " << time;
            prev = -1;
        }
    }
    cout << " | " << time << "\n";

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << wt[i] << "\t" << tat[i] << "\n";
    }

    cout << "------------------------------------\n";
    cout << "Average Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;

    return 0;
}