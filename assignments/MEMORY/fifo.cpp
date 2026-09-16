#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int p, f;

    cout << "Number Of Pages : ";
    cin >> p;

    cout << "Number Of Frame Size : ";
    cin >> f;

    int frame[f], page[p];

    cout << "Enter Page Reference String : ";
    for (int i = 0; i < p; i++)
    {
        cin >> page[i];
    }

    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
    }

    int victim = 0;
    int pageFault = 0;

    cout << "\n"
         << setw(10) << left << "PAGE" << setw(15) << left << "FRAMES" << setw(10) << left << "RESULT" << endl;
    cout << "---------------------------------------" << endl;

    for (int i = 0; i < p; i++)
    {
        bool found = 0;
        string result = "HIT";

        for (int j = 0; j < f; j++)
        {
            if (frame[j] == page[i])
            {
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            result = "MISS";
            frame[victim] = page[i];
            victim = (victim + 1) % f;
            pageFault++;
        }

        cout << setw(10) << left << page[i];

        string st = "";
        for (int m = 0; m < f; m++)
        {
            if (frame[m] == -1)
                st += "- ";
            else
                st += to_string(frame[m]) + " ";
        }

        cout << setw(15) << left << st << setw(10) << left << result << endl;
    }

    cout << "---------------------------------------" << endl;
    cout << "Total Page Faults : " << pageFault << endl;
    return 0;
}