#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), ct(n), wt(n), tat(n), completed(n, 0);

    cout << "Enter arrival times: ";
    for (int i = 0; i < n; i++)
        cin >> at[i];

    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++)
        cin >> bt[i];

    int time = 0, count = 0;
    int totalWT = 0, totalTAT = 0;

    cout << "\nExecution Sequence :\n"
         << time;

    while (count < n)
    {
        int idx = -1;
        int min_bt = 99999;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && !completed[i])
            {
                if (bt[i] < min_bt)
                {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            totalWT += wt[idx];
            totalTAT += tat[idx];
            completed[idx] = 1;
            count++;

            cout << " | P" << idx << " | " << time;
        }
        else
        {
            time++;
        }
    }

    cout << "\n\nPID\tAT\tBT\tCT\tWT\tTAT\n";
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

/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int id;
    int bt;
    int ct;
    int wt;
    int tat;
};

bool compareBT(const Process& a, const Process& b) {
    return a.bt < b.bt;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        cin >> p[i].bt;
    }

    sort(p.begin(), p.end(), compareBT);

    int time = 0;
    int totalWT = 0, totalTAT = 0;

    cout << "\nExecution Sequence :\n" << time;

    for (int i = 0; i < n; i++)
    {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct; // Since AT = 0
        p[i].wt = p[i].tat - p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;

        cout << " | P" << p[i].id << " | " << time;
    }

    cout << "\n\nPID\tAT\tBT\tCT\tWT\tTAT\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "\t0\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].wt << "\t" << p[i].tat << "\n";
    }

    cout << "------------------------------------\n";
    cout << "Average Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;

    return 0;
}*/