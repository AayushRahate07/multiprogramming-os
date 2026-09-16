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

    int frame[f], page[p], future[f];

    cout << "Enter Page Reference String : ";
    for (int i = 0; i < p; i++)
    {
        cin >> page[i];
    }

    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
    }

    int pageFault = 0;

    cout << "\n" << left << setw(10) << "PAGE" << setw(15) << "FRAMES" << "RESULT" << endl;
    cout << "---------------------------------------" << endl;

    for (int i = 0; i < p; i++)
    {
        bool found = 0;

        for (int j = 0; j < f; j++)
        {
            if (frame[j] == page[i])
            {
                found = 1;
                break;
            }
        }

        string result = "HIT";

        if (found == 0)
        {
            result = "MISS";
            bool placed = 0;
            for (int j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = page[i];
                    pageFault++;
                    placed = 1;
                    break;
                }
            }

            if (placed == 0)
            {
                for (int j = 0; j < f; j++)
                {
                    future[j] = 999; 
                    for (int m = i + 1; m < p; m++)
                    {
                        if (frame[j] == page[m])
                        {
                            future[j] = m;
                            break;
                        }
                    }
                }

                int victim = 0;
                for (int k = 1; k < f; k++)
                {
                    if (future[k] > future[victim])
                    {
                        victim = k;
                    }
                }

                frame[victim] = page[i];
                pageFault++;
            }
        }

        cout << left << setw(10) << page[i];
        
        string frameStr = "";
        for (int j = 0; j < f; j++)
        {
            if (frame[j] == -1)
                frameStr += "- ";
            else
                frameStr += to_string(frame[j]) + " ";
        }
        cout << left << setw(15) << frameStr << result << endl;
    }

    cout << "---------------------------------------" << endl;
    cout << "Total Page Faults : " << pageFault << endl;
    return 0;
}