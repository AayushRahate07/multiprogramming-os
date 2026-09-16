#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    int id, bt, priority, ct, wt, tat;
};

bool comparePriority(const Process &a, const Process &b)
{
    return a.priority < b.priority;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++)
    {
        p[i].id = i;
        cin >> p[i].bt;
    }

    cout << "Enter priorities: ";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].priority;
    }

    sort(p.begin(), p.end(), comparePriority);

    int time = 0;
    int totalWT = 0, totalTAT = 0;

    cout << "\nExecution Sequence : " << time;

    for (int i = 0; i < n; i++)
    {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;

        cout << " | P" << p[i].id << " | " << time;
    }

    cout << "\n\nPID\tPrio\tBT\tCT\tWT\tTAT\n-------------------------------------\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "\t" << p[i].priority << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].wt << "\t" << p[i].tat << "\n";
    }

    cout << "-------------------------------------\n";
    cout << "Average Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;

    return 0;
}