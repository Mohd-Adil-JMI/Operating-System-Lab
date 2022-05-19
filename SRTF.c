#include <stdio.h>

int min(int k[500][500], int n, int p)
{

    int i, r;
    int mn = 100;
    r = -1;

    for (i = 0; i < n; i++)
    {
        if (k[1][i] != 0)
            if (mn > k[1][i] && p >= k[0][i])
            {
                mn = k[1][i];
                r = i;
            }
    }
    // printf("mn =%d",mn);
    return r;
}
int remainingb(int k[], int n)
{
    int i, flag = 0;
    for (i = 0; i < n; i++)
        if (k[i] > 0)
        {
            flag = 1;
            return flag;
        }
    return flag;
}

int main()
{
    printf("20BCS042 | Mohd Adil\n");
    int a[500][500], i, n, m, j, k, l, schedule[1000];

    printf("Enter no. of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for process %d :", i + 1);
        scanf("%d%d", &a[0][i], &a[1][i]);
        a[5][i] = a[1][i];
    }

    int start;

    int rem = remainingb(a[1], n);

    int sc = 0;

    while (rem)
    {
        start = min(a, n, sc);
        if (start != -1)
        {
            schedule[sc++] = start;
            a[1][start] = a[1][start] - 1;
            rem = remainingb(a[1], n);
        }
        else
        {
            schedule[sc++] = 1000;
        }
    }

    for (i = n - 1; i >= 0; i--)
    {
        for (j = sc - 1; j >= 0; j--)
        {
            if (schedule[j] == i)
            {
                a[2][i] = j + 1;
                break;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < sc; j++)
        {
            if (schedule[j] == i)
            {
                a[6][i] = j;
                break;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        a[3][i] = a[2][i] - a[0][i];
        a[4][i] = a[3][i] - a[5][i];
    }

    for (i = 0; i < n; i++)
    {
        printf("For process %d Arrival Time = %d and Burst Time = %d Completion Time = %d TAT = %d Waiting time = %d Response Time = %d\n", i + 1, a[0][i], a[5][i], a[2][i], a[3][i], a[4][i], a[6][i]);
    }

    float atat = 0, awt = 0, art = 0;
    for (i = 0; i < n; i++)
    {
        atat = atat + a[3][i];
        awt = awt + a[4][i];
        art = art + a[6][i];
    }

    printf("\n\nAverage TAT = %f\nAverage Waiting Time = %f\nAverage Response Time = %f", atat / n, awt / n, art / n);
    return 0;
}
