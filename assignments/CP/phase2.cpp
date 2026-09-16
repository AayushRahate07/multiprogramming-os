#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>

using namespace std;

char M[300][4];
char R[4], IR[4];
int IC;
bool C;
int SI, PI, TI;

struct PCB
{
    int jobId, TTL, TLL, TTC, LLC, PTR;
} pcb;

ifstream fin;
ofstream fout;

vector<int> usedFrames;
int currentPage = 0;
bool terminated = false;

void init()
{
    for (int i = 0; i < 300; i++)
        for (int j = 0; j < 4; j++)
            M[i][j] = ' ';

    for (int i = 0; i < 4; i++)
    {
        IR[i] = ' ';
        R[i] = ' ';
    }

    IC = 0;
    C = false;
    SI = PI = TI = 0;
    pcb.TTC = pcb.LLC = pcb.PTR = 0;
    currentPage = 0;
    terminated = false;
    usedFrames.clear();
}

void dumpMemory()
{
    cout << "\n=== MEMORY DUMP (JOB " << pcb.jobId << ") ===\n";
    for (int i = 0; i < 300; i++)
    {
        cout << "M[" << i << "]: ";
        for (int j = 0; j < 4; j++)
        {
            char c = M[i][j];
            cout << (c == ' ' ? '_' : c);
        }
        cout << "\n";
    }
    cout << "=========================\n\n";
}

int allocateFrame()
{
    if ((int)usedFrames.size() >= 30)
        return -1;

    while (true)
    {
        int frame = rand() % 30;
        bool used = false;
        for (int f : usedFrames)
        {
            if (f == frame)
            {
                used = true;
                break;
            }
        }
        if (!used)
        {
            usedFrames.push_back(frame);
            return frame;
        }
    }
}

int addressMap(int VA)
{
    if (VA < 0 || VA > 99)
    {
        PI = 2;
        return -1;
    }
    int page = VA / 10;
    int offset = VA % 10;
    int PTE = pcb.PTR + page;

    if (M[PTE][0] == '*')
    {
        PI = 3;
        return -1;
    }

    int frame = (M[PTE][2] - '0') * 10 + (M[PTE][3] - '0');
    return frame * 10 + offset;
}

void terminate(int EM)
{
    switch (EM)
    {
    case 0:
        fout << "NO ERROR";
        break;
    case 1:
        fout << "OUT OF DATA";
        break;
    case 2:
        fout << "LINE LIMIT EXCEEDED";
        break;
    case 3:
        fout << "TIME LIMIT EXCEEDED";
        break;
    case 4:
        fout << "OPCODE ERROR";
        break;
    case 5:
        fout << "OPERAND ERROR";
        break;
    case 6:
        fout << "INVALID PAGE FAULT";
        break;
    }
    fout << "\n-------------------------------------------\n";
    fout << "JOB ID           : " << pcb.jobId << "\n";
    fout << "IC               : " << IC << "\n";
    fout << "IR               : " << IR[0] << IR[1] << IR[2] << IR[3] << "\n";
    fout << "TIME USED  (TTC) : " << pcb.TTC << "\n";
    fout << "LINES USED (LLC) : " << pcb.LLC << "\n";
    fout << "-------------------------------------------\n\n\n";

    dumpMemory();
    terminated = true;
}

bool handlePageFault(int VA)
{
    int page = VA / 10;
    int frame = allocateFrame();
    if (frame == -1)
        return false;

    int pte = pcb.PTR + page;
    M[pte][0] = ' ';
    M[pte][1] = ' ';
    M[pte][2] = (frame / 10) + '0';
    M[pte][3] = (frame % 10) + '0';

    PI = 0;
    return true;
}

void MOS()
{
    if (PI != 0)
    {
        if (PI == 1)
        {
            terminate(4);
        }
        else if (PI == 2)
        {
            terminate(5);
        }
        else if (PI == 3)
        {
            string op = "";
            op += IR[0];
            op += IR[1];

            if (op == "GD" || op == "SR")
            {
                int VA = (IR[2] - '0') * 10 + (IR[3] - '0');
                if (!handlePageFault(VA))
                    terminate(6);
            }
            else
            {
                terminate(6);
            }
        }
        return;
    }

    if (TI == 2)
    {
        if (SI == 2)
        {
            int VA = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (++pcb.LLC <= pcb.TLL)
            {
                int RA = addressMap(VA);
                if (PI == 0 && RA != -1)
                {
                    for (int i = RA; i < RA + 10; ++i)
                        for (int j = 0; j < 4; ++j)
                            fout << M[i][j];
                    fout << "\n";
                }
                PI = 0;
            }
            SI = 0;
        }
        terminate(3);
        return;
    }

    if (SI != 0)
    {
        int VA = (IR[2] - '0') * 10 + (IR[3] - '0');

        if (SI == 1)
        {
            string line;
            if (!getline(fin, line) || (line.size() >= 4 && line.substr(0, 4) == "$END"))
            {
                terminate(1);
            }
            else
            {
                int RA = addressMap(VA);

                if (PI == 3)
                {
                    handlePageFault(VA);
                    RA = addressMap(VA);
                }

                if (!terminated && PI == 0 && RA != -1)
                {
                    int k = 0;
                    for (int i = RA; i < RA + 10; ++i)
                        for (int j = 0; j < 4; ++j)
                            M[i][j] = (k < (int)line.size()) ? line[k++] : ' ';
                }
            }
        }
        else if (SI == 2)
        {
            if (++pcb.LLC > pcb.TLL)
            {
                terminate(2);
            }
            else
            {
                int RA = addressMap(VA);

                if (PI == 3)
                {
                    terminate(6);
                    return;
                }

                if (!terminated && PI == 0 && RA != -1)
                {
                    for (int i = RA; i < RA + 10; ++i)
                        for (int j = 0; j < 4; ++j)
                            fout << M[i][j];
                    fout << "\n";
                }
            }
        }
        else if (SI == 3)
        {
            terminate(0);
        }

        SI = 0;
    }
}

void executeJob()
{
    while (!terminated)
    {
        int RA = addressMap(IC);

        if (PI == 3)
        {
            handlePageFault(IC);
            continue;
        }
        if (PI != 0)
        {
            MOS();
            continue;
        }

        memcpy(IR, M[RA], 4);

        if (IR[0] == 'H')
        {
            pcb.TTC += 1;

            if (pcb.TTC > pcb.TTL)
                TI = 2;

            SI = 3;
            MOS();
            break;
        }

        if (!isdigit(IR[2]) || !isdigit(IR[3]))
        {
            PI = 2;
            MOS();

            if (!terminated)
                IC++;

            continue;
        }

        string op = "";
        op += IR[0];
        op += IR[1];

        if (op == "GD" || op == "SR")
            pcb.TTC += 2;
        else
            pcb.TTC += 1;

        if (pcb.TTC > pcb.TTL)
            TI = 2;

        int VA = (IR[2] - '0') * 10 + (IR[3] - '0');
        bool branchTaken = false;

        if (op == "GD")
        {
            SI = 1;
        }
        else if (op == "PD")
        {
            SI = 2;
        }
        else if (op == "LR" || op == "SR" || op == "CR")
        {
            int loc = addressMap(VA);

            if (PI == 3)
            {
                if (op == "SR")
                {
                    handlePageFault(VA);
                    if (!terminated)
                    {
                        pcb.TTC -= 2;
                        continue;
                    }
                }
                else
                {
                    terminate(6);
                    break;
                }
            }

            if (PI != 0)
            {
                MOS();
                if (!terminated)
                    IC++;
                continue;
            }

            if (op == "LR")
                memcpy(R, M[loc], 4);
            else if (op == "SR")
                memcpy(M[loc], R, 4);
            else
                C = (memcmp(R, M[loc], 4) == 0);
        }

        else if (op == "BT")
        {
            if (C)
            {
                IC = VA;
                branchTaken = true;
            }
        }
        else
        {
            PI = 1;
        }

        if (SI != 0 || PI != 0 || TI != 0)
            MOS();

        if (!branchTaken && !terminated && PI == 0)
            IC++;
    }
}

void load()
{
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        if (line.substr(0, 4) == "$AMJ")
        {
            init();
            pcb.jobId = stoi(line.substr(4, 4));
            pcb.TTL = stoi(line.substr(8, 4));
            pcb.TLL = stoi(line.substr(12, 4));
            pcb.PTR = allocateFrame() * 10;

            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 4; j++)
                    M[pcb.PTR + i][j] = '*';

            currentPage = 0;
        }

        else if (line.substr(0, 4) == "$DTA")
        {
            executeJob();
        }
        else if (line.substr(0, 4) == "$END")
        {
            continue;
        }

        else
        {
            int frame = allocateFrame();
            int page = currentPage++;
            int pte = pcb.PTR + page;

            M[pte][0] = ' ';
            M[pte][1] = ' ';
            M[pte][2] = (frame / 10) + '0';
            M[pte][3] = (frame % 10) + '0';

            int k = 0;
            for (int i = frame * 10; i < frame * 10 + 10; i++)
                for (int j = 0; j < 4; j++)
                    M[i][j] = (k < (int)line.size()) ? line[k++] : ' ';
        }
    }
}

int main()
{
    srand(time(0));
    fin.open("input2.txt");
    fout.open("output2.txt");
    if (!fin.is_open())
    {
        cout << "Error opening input2.txt\n";
        return 1;
    }
    load();
    fin.close();
    fout.close();
    cout << "MOS Execution Completed!\n";
    return 0;
}