#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> arrival(n), burst(n), waiting(n), turnaround(n), completion(n);

    cout << "Enter arrival times: ";
    for (int i = 0; i < n; i++)
        cin >> arrival[i];

    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++)
        cin >> burst[i];

    int time = 0;
    cout << "\nExecution Sequence :\n" << time;

    for (int i = 0; i < n; i++)
    {
        if (time < arrival[i])
        {
            time = arrival[i];
            cout << " | IDLE | " << time;
        }

        waiting[i] = time - arrival[i];
        time += burst[i];
        completion[i] = time;
        turnaround[i] = completion[i] - arrival[i];

        cout << " | P" << i << " | " << time;
    }

    int totalWT = 0, totalTAT = 0;

    cout << "\n\n" << setw(6) << left << "PID" 
         << setw(6) << left << "AT" 
         << setw(6) << left << "BT" 
         << setw(6) << left << "CT" 
         << setw(6) << left << "WT" 
         << setw(6) << left << "TAT" << endl;
    cout << "------------------------------------" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t" 
             << arrival[i] << "\t" 
             << burst[i] << "\t"
             << completion[i] << "\t" 
             << waiting[i] << "\t" 
             << turnaround[i] << endl;

        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    cout << "------------------------------------" << endl;
    cout << "Average Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;

    return 0;
}