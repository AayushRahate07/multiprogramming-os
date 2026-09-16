#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int n, head;

    cout << "Enter Initial Head Position : ";
    cin >> head;

    cout << "Enter Number Of Requests : ";
    cin >> n;

    vector<int> req(n);
    cout << "Enter Requests : ";
    for (int i = 0; i < n; i++)
    {
        cin >> req[i];
    }

    vector<bool> visited(n, false);
    int tot = 0;
    int count = 0;

    cout << endl
         << std::left << setw(15) << "Track Visited" << std::left << setw(15) << "Seek Time" << endl;
    cout << "------------------------------" << endl;

    while (count < n)
    {
        int min_seek = 9999;
        int idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                int current_seek = abs(head - req[i]);
                if (current_seek < min_seek)
                {
                    min_seek = current_seek;
                    idx = i;
                }
            }
        }

        visited[idx] = true;
        tot += min_seek;

        cout << std::left << setw(15) << req[idx] << std::left << setw(15) << min_seek << endl;

        head = req[idx];
        count++;
    }

    cout << "------------------------------" << endl;
    cout << "Total Seek Time: " << tot << endl;
    return 0;
}