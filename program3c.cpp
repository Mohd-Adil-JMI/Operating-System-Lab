#include <iostream>
#include <vector>
using namespace std;

struct Process
{
    char Pname[3];
    int arvlTime;
    int brstTime;
    int cmplTime;
    int wtngTime;
    int tartTime;
    int respTime;
};

struct priorityQ
{
    Process pr;
    priorityQ *next;
};

priorityQ *push(priorityQ *front, Process process, char c)
{
    priorityQ *node = new priorityQ;
    node->pr = process;
    node->next = NULL;

    // push according to burst Time
    if (c == 'b')
    {
        if (front == NULL)
        {
            front = node;
        }
        else if (front->pr.brstTime > process.brstTime)
        {
            node->next = front;
            front = node;
        }
        else
        {
            priorityQ *tmp = front;
            while (tmp->next != NULL && tmp->next->pr.brstTime < process.brstTime)
            {
                tmp = tmp->next;
            }

            node->next = tmp->next;
            tmp->next = node;
        }
    }

    // otherwise push accoring to arrival time
    else
    {
        if (front == NULL)
        {
            front = node;
        }
        else if (front->pr.arvlTime > process.arvlTime)
        {
            node->next = front;
            front = node;
        }
        else
        {
            priorityQ *tmp = front;
            while (tmp->next != NULL && tmp->next->pr.arvlTime < process.arvlTime)
            {
                tmp = tmp->next;
            }

            node->next = tmp->next;
            tmp->next = node;
        }
    }

    return front;
}

priorityQ *pop(priorityQ *front)
{
    front = front->next;
    return front;
}

// Process front(priorityQ *front)
// {
//     return front->pr;
// }

bool empty(priorityQ *front)
{
    return (front == NULL);
}

// ans vector
priorityQ *pqfront = new priorityQ;
// vector<Process> v;
int n;
float avgc, avgw, avgt;

void SJF(priorityQ *pq1)
{
    int cmpt=pq1->pr.brstTime;
    pqfront->pr = pq1->pr;
    pqfront->next = NULL;
    // v.push_back(front(pq1));
    pq1 = pop(pq1);

    priorityQ *pq2 = NULL;

    while (!empty(pq1))
    {
        while (!empty(pq1) && pq1->pr.arvlTime < cmpt)
        {
            pq2 = push(pq2, pq1->pr, 'b');
            pq1 = pop(pq1);
        }

        cmpt += pq2->pr.brstTime;
        priorityQ *temp = pqfront;
        while (temp!= NULL)
        {
            temp = temp->next;
        }
        temp->pr = pq2->pr;
        temp->next = NULL;
        // v.push_back(front(pq2));
        pq2 = pop(pq2);
    }

    while (!empty(pq2))
    {
        priorityQ *temp = pqfront;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = pq2;
        temp=temp->next;
        temp->next = NULL;
        // v.push_back(front(pq2));
        pq2 = pop(pq2);
    }
}

void calculateTimes()
{
    pqfront->pr.wtngTime=0;
    pqfront->pr.cmplTime=pqfront->pr.brstTime;
    // v.front().wtngTime=0;
    // v.front().cmplTime = v.front().brstTime;
    float sumc = 0, sumw = 0, sumt = 0;

    // calculating completion time
    int prv = pqfront->pr.cmplTime;
    // int prv = v.front().cmplTime;
    sumc += prv;
    priorityQ *temp = pqfront->next;
    while (temp != NULL)
    {
        temp->pr.cmplTime = prv + temp->pr.brstTime;
        prv = temp->pr.cmplTime;
        sumc += prv;
        temp = temp->next;
    }

    // for(int i=1; i<n; i++){
    //     v[i].cmplTime = prv + v[i].brstTime;
    //     prv = v[i].cmplTime;
    //     sumc += v[i].cmplTime;
    // }

    // calculating waiting time
    prv = pqfront->pr.cmplTime;
    temp = pqfront->next;
    while (temp != NULL)
    {
        temp->pr.wtngTime = prv - temp->pr.arvlTime;
        prv = temp->pr.cmplTime;
        sumw += temp->pr.wtngTime;
        temp = temp->next;
    }

    // prv = v.front().cmplTime;
    // for(int i=1; i<n; i++){
    //     v[i].wtngTime = prv - v[i].arvlTime;
    //     prv = v[i].cmplTime;
    //     sumw += v[i].wtngTime;
    // }

    // calculating turn around time
    temp = pqfront;
    while (temp != NULL)
    {
        temp->pr.tartTime = temp->pr.cmplTime - temp->pr.arvlTime;
        sumt += temp->pr.tartTime;
        temp = temp->next;
    }

    // for(int i=0; i<n; i++){
    //     v[i].tartTime = v[i].brstTime + v[i].wtngTime;
    //     sumt += v[i].tartTime;
    // }

    // calculating avg(s) time
    avgc = sumc / n;
    avgw = sumw / n;
    avgt = sumt / n;
}

void display()
{
    cout << "\n\nDisplaying the table :- ";

    cout << "\n\n+--------------+------------+--------------+-----------------+--------------+-----------------+---------------+";
    cout << "\n| Process name | Burst Time | Arrival Time | Completion Time | Waiting Time | TurnAround Time | Response Time |";
    cout << "\n+--------------+------------+--------------+-----------------+--------------+-----------------+---------------+";
    priorityQ *temp = pqfront->next;
    while (temp != NULL)
    {
        printf("\n|      %s      |    %2d      |      %2d      |        %2d       |      %2d      |      %2d         |      %2d       |", temp->pr.Pname, temp->pr.brstTime, temp->pr.arvlTime, temp->pr.cmplTime, temp->pr.wtngTime, temp->pr.tartTime, temp->pr.wtngTime);
        cout << "\n+--------------+------------+--------------+-----------------+--------------+-----------------+---------------+";
        temp = temp->next;
    }

    // for(auto i:v){
    //     printf("\n|      %s      |    %2d      |      %2d      |        %2d       |      %2d      |      %2d         |      %2d       |"
    //            ,i.Pname, i.brstTime, i.arvlTime, i.cmplTime, i.wtngTime, i.tartTime, i.wtngTime);
    // cout<<"\n+--------------+------------+--------------+-----------------+--------------+-----------------+---------------+";
    // }

    cout << "\n\n";
    printf("\nAverage Completion time : %.2fns", avgc);
    printf("\nAverage Waiting time : %.2fns", avgw);
    printf("\nAverage TurnAround time : %.2fns", avgt);
    printf("\nAverage Response time : %.2fns", avgw);
}

// void printGantt(){

//     cout<<"\n\nGantt Chart : ";

//     cout<<"\n\n+";
//     for(auto p:v){
//         for(int i=0; i<2*p.brstTime; i++){
//             cout<<"-";
//         }
//         cout<<"+";
//     }

//     cout<<"\n|";
//     for(auto p:v){
//         for(int i=0; i<p.brstTime-1; i++){
//             cout<<" ";
//         }
//         cout<<p.Pname;
//         for(int i=0; i<p.brstTime-1; i++){
//             cout<<" ";
//         }
//         cout<<"|";
//     }

//     cout<<"\n+";
//     for(auto p:v){
//         for(int i=0; i<2*p.brstTime; i++){
//             cout<<"-";
//         }
//         cout<<"+";
//     }

//     cout<<"\n0";
//     for(auto p:v){
//         for(int i=0; i<2*p.brstTime-1; i++){
//             cout<<" ";
//         }
//         printf("%2d", p.cmplTime);
//     }
//     cout<<"\n\n";
// }

int main()
{
    priorityQ *pq1 = NULL;

    cout << "Enter the no of the Processes : ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        struct Process p;
        cout << "Enter Process " << i + 1 << " name, its burst Time and Arrival Time : ";
        cin >> p.Pname >> p.brstTime >> p.arvlTime;
        pq1 = push(pq1, p, 'f');
    }

    // sort according to arrival time + burst Time :
    SJF(pq1);
    calculateTimes();

    display();
    // printGantt();
    return 0;
}

// sample input:-
//  5 P1 6 2 P2 2 5 P3 8 1 P4 3 0 P5 4 4