#include <iostream>
using namespace std;

void FCFS(int *arr, int n, int head)
{
    int seq_op = 0;
    cout << "\nDisk Movement details : ";

    for (int i = 0; i < n; i++)
    {
        cout << "\n"
             << head << " -----> " << arr[i];

        int dist = abs(arr[i] - head);
        seq_op += dist;
        head = arr[i];
    }

    cout << "\n\nTotal seek operations : " << seq_op;
    cout << "\nAvg Head Movement : " << float(seq_op) / n << "\n";
}

int search(int *arr, bool *done, int n, int head)
{
    int idx = -1, mn = INT16_MAX;
    for (int i = 0; i < n; i++)
    {
        if (!done[i] && arr[i] != head && abs(head - arr[i]) < mn)
        {
            mn = abs(head - arr[i]);
            idx = i;
        }
    }
    return idx;
}

void SSTF(int *arr, int n, int head)
{
    int seq_op = 0;
    bool done[n] = {false};
    cout << "\nDisk Movement details : ";

    for (int i = 0; i < n; i++)
    {
        int findIdx = search(arr, done, n, head);
        done[findIdx] = true;

        cout << "\n"
             << head << " -----> " << arr[findIdx];

        int dist = abs(arr[findIdx] - head);
        seq_op += dist;
        head = arr[findIdx];
    }

    cout << "\n\nTotal seek operations : " << seq_op;
    cout << "\nAvg Head Movement : " << float(seq_op) / n << "\n";
}

int main()
{
    cout << "\n\nName : Mohd Adil \nRoll No : 20BCS042\n";

    int n;
    cout << "\nEnter No of Sequences : ";
    cin >> n;
    int *arr = new int[n];
    cout << "Enter the Sequences : ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int head;
    cout << "Enter head position : ";
    cin >> head;

    cout << "\nPress 1 for FCFS disk Scheduling Algorithm";
    cout << "\nPress 2 for SSTF disk Scheduling Algorithm";
    cout << "\nPress 3 to exit";
    while (1)
    {
        cout << "\nEnter your choice : ";
        int ch;
        cin >> ch;

        switch (ch)
        {
        case 1:
            FCFS(arr, n, head);
            break;
        case 2:
            SSTF(arr, n, head);
            break;
        case 3:
            cout << "Exiting...";
            exit(0);
        default:
            cout << "\nEnter a correct choice please";
            break;
        }
    }

    return 0;
}

// sample input
// 8 176 79 34 60 92 11 41 114 50
