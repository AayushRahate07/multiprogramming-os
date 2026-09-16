#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
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

    int seek = 0, tot = 0;

    cout << "\n" << std::left << setw(15) << "Track Visited" << std::left << setw(15) << "Seek Time" << endl;
    cout << "------------------------------" << endl;

    for (int i = 0; i < n; i++)
    {
        seek = abs(head - req[i]);
        cout << std::left << setw(15) << req[i] << std::left << setw(15) << seek << endl;
        tot += seek;
        head = req[i];
    }

    cout << "------------------------------" << endl;
    cout << "Total Seek Time: " << tot << endl;
    return 0;
}