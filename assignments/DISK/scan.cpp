#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    int n, head, diskSize;

    cout << "Enter Initial Head Position: ";
    cin >> head;

    cout << "Enter Total Disk Size: ";
    cin >> diskSize;

    cout << "Enter Number Of Requests: ";
    cin >> n;

    vector<int> left, right;

    cout << "Enter Requests:\n";
    for (int i = 0; i < n; i++)
    {
        int r;
        cin >> r;
        if (r >= head)
            right.push_back(r);
        else
            left.push_back(r);
    }

    sort(right.begin(), right.end());
    sort(left.begin(), left.end());

    int tot = 0, seek = 0;

    cout << "\n"
         << std::left << setw(15) << "Track Visited" << std::left << setw(15) << "Seek Time" << endl;
    cout << "------------------------------" << endl;

    for (int i = 0; i < right.size(); i++)
    {
        seek = abs(right[i] - head);
        cout << std::left << setw(15) << right[i] << std::left << setw(15) << seek << endl;
        tot += seek;
        head = right[i];
    }

    if (!left.empty())
    {
        seek = abs((diskSize - 1) - head);
        tot += seek;
        cout << std::left << setw(15) << (diskSize - 1) << std::left << setw(15) << seek << endl;

        head = diskSize - 1;
    }

    for (int i = left.size() - 1; i >= 0; i--)
    {
        seek = abs(left[i] - head);
        cout << std::left << setw(15) << left[i] << std::left << setw(15) << seek << endl;
        tot += seek;
        head = left[i];
    }

    cout << "------------------------------" << endl;
    cout << "Total Seek Time: " << tot << endl;
    return 0;
}