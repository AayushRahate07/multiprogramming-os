#include <iostream>
#include <vector>
using namespace std;

struct Segment
{
    int base;
    int limit;
};

int main()
{
    int segmentCount;
    cout << "Enter Number of Segments: ";
    cin >> segmentCount;

    vector<Segment> segmentTable(segmentCount);

    for (int i = 0; i < segmentCount; i++)
    {
        cout << "Enter Base and Limit for Segment " << i << " : ";
        cin >> segmentTable[i].base >> segmentTable[i].limit;
    }

    int segmentNum, offset;
    cout << "\nEnter Logical Address (Segment No and Offset): ";
    cin >> segmentNum >> offset;

    if (segmentNum < 0 || segmentNum >= segmentCount)
    {
        cout << "INVALID SEGMENT NUMBER" << endl;
    }
    else if (offset < 0 || offset >= segmentTable[segmentNum].limit)
    {
        cout << "SEGMENTATION FAULT" << endl;
    }
    else
    {
        int PA = segmentTable[segmentNum].base + offset;
        cout << "Physical Address: " << PA << endl;
    }

    return 0;
}