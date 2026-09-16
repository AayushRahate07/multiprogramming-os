#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, quant;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> burst(n), remaining(n), waiting(n, 0), turnaround(n), completion(n);

    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++)
    {
        cin >> burst[i];
        remaining[i] = burst[i];
    }

    cout << "Enter time quantum: ";
    cin >> quant;

    int time = 0;

    cout << endl << "Execution Sequence :" << endl;

    int completed = 0;

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                cout << "[T" << time << "]\tProcess P" << i << " runs. ";

                if (remaining[i] > quant)
                {
                    time += quant;
                    remaining[i] -= quant;
                    cout << "Remaining: " << remaining[i] << endl;
                }
                else
                {
                    time += remaining[i];
                    completion[i] = time; 
                    cout << "Remaining: 0 (Finished at " << time << ")" << endl;

                    remaining[i] = 0;
                    completed++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        turnaround[i] = completion[i] - 0;
        waiting[i] = turnaround[i] - burst[i];
    }

    int totalWT = 0, totalTAT = 0;

    cout << endl << "PID\tBT\tCT\tWT\tTAT" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t" << burst[i] << "\t"
             << completion[i] << "\t" << waiting[i]
             << "\t" << turnaround[i] << endl;

        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    cout << endl;
    cout << "Average Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;

    return 0;
}