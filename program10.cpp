#include <iostream>
#include <vector>
using namespace std;

struct Process
{
    char Pname[3];
    int memory;
    bool allocated = false;
};
struct Block
{
    int size;
    bool used = false;
    int rem;
    struct Process processAllocated;
};

int main()
{
    cout << "No. of block : ";
    int n;
    cin >> n;
    vector<Block> blocks;
    cout << "Enter Size of the " << n << " Blocks: ";
    for (int i = 0; i < n; i++)
    {
        Block tempBlock;
        cin >> tempBlock.size;
        tempBlock.rem = tempBlock.size;
        blocks.push_back(tempBlock);
    }
    cout << "No. of Process : ";
    int m;
    cin >> m;
    vector<Process> Processes;
    cout << "Enter Name and size of the Processes: ";
    for (int i = 0; i < m; i++)
    {
        Process tempProcess;
        cin >> tempProcess.Pname;
        cin >> tempProcess.memory;
        Processes.push_back(tempProcess);
    }
    // memory allocation
    int j = 0;
    for (int i = 0; i < m; i++)
    {
        int prv = j;
        do
        {
            if (Processes[i].memory <= blocks[j].rem && blocks[j].used == false)
            {
                Processes[i].allocated = true;
                blocks[j].used = true;
                blocks[j].rem = blocks[j].size - Processes[i].memory;
                blocks[j].processAllocated = Processes[i];
                break;
            }
            else
            {
                j = (j + 1) % n;
            }
        } while (j != prv);
    }
    //display
    cout << "\tBlock Number\tSize\tProcess Allocated\tInternal Fragmentation" << endl;
    for (int i = 0; i < n; i++)
    {
        if (blocks[i].used == true)
        {
            cout << "\t\t" << i + 1 << "\t" << blocks[i].size << "\t\t" << blocks[i].processAllocated.Pname << "\t\t\t" << blocks[i].rem << endl;
        }
        else
        {
            cout << "\t\t" << i + 1 << "\t" << blocks[i].size << "\t\t"
                 << "---"
                 << "\t\t\t"
                 << "---" << endl;
        }
    }
    //for external fragmentation
    bool flag = true;
    for (int i = 0; i < m; i++)
    {
        if (Processes[i].allocated == false)
        {
            flag = false;
            break;
        }
        else
        {
            continue;
        }
    }
    //calculating IF and EF
    int IF = 0, EF = 0;
    for (int i = 0; i < n; i++)
    {
        if (blocks[i].used == true)
        {
            IF += blocks[i].rem;
        }
        else
        {
            if (flag == false)
            {
                EF += blocks[i].rem;
            }
        }
    }
    cout << "Total Internal Fragmentation = " << IF << endl;
    cout << "Total External Fragmentation = " << EF << endl;
    return 0;
}