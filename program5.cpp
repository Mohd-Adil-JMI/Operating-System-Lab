#include <iostream>
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
struct Queue
{
    Process pr;
    Queue *next;
};
int n;
Queue *push(Queue *queue, Process process)
{
    Queue *node = new Queue;
    node->pr = process;
    node->next = NULL;
    if (queue == NULL)
    {
        queue = node;
    }
    else if (process.arvlTime < queue->pr.arvlTime)
    {
        node->next = queue;
        queue = node;
    }
    else
    {
        Queue *temp = queue;
        while (temp->next != NULL && temp->next->pr.arvlTime < process.arvlTime)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    return queue;
}
void Calculate(Queue *queue)
{

    // completion time
    int prv = 0;
    Queue *temp = queue;
    while (temp != NULL)
    {
        if (prv >= temp->pr.arvlTime)
        {
            temp->pr.cmplTime = prv + temp->pr.brstTime;
            prv = temp->pr.cmplTime;
            temp = temp->next;
        }
        else{
            prv++;
        }
    }
    // turnarround time
    temp = queue;
    while (temp != NULL)
    {
        temp->pr.tartTime = temp->pr.cmplTime - temp->pr.arvlTime;
        temp = temp->next;
    }
    // waiting time
    temp = queue;
    while (temp != NULL)
    {
        temp->pr.wtngTime = temp->pr.tartTime - temp->pr.brstTime;
        temp = temp->next;
    }
}
void display(Queue *queue)
{
    Queue *temp = queue;
    while (temp != NULL)
    {
        cout << "Process : " << temp->pr.Pname << endl;
        cout << "Arrival time : " << temp->pr.arvlTime << endl;
        cout << "Burst time : " << temp->pr.brstTime << endl;
        cout << "Completion time : " << temp->pr.cmplTime << endl;
        cout << "Turn Around time : " << temp->pr.tartTime << endl;
        cout << "Waiting time : " << temp->pr.wtngTime << endl;
        temp = temp->next;
    }
}
void printGanttChart(Queue *queue){
    if(queue==NULL){
        cout<<"\nNo processes in the ready Queue";
        return;
    }

    cout<<"\n\nGantt Chart : ";

   Queue *tmp = queue;
    
    cout<<"\n\n+";
    while(tmp!=NULL){
        for(int i=0; i<2*tmp->pr.brstTime; i++){
            cout<<"-";
        }
        cout<<"+";
        tmp = tmp->next;
    }

    tmp = queue;
    cout<<"\n|";
    while(tmp!=NULL){
        for(int i=0; i<tmp->pr.brstTime-1; i++){
            cout<<" ";
        }
        cout<<tmp->pr.Pname;
        for(int i=0; i<tmp->pr.brstTime-1; i++){
            cout<<" ";
        }
        cout<<"|";
        tmp = tmp->next;
    }

    tmp = queue;
    cout<<"\n+";
    while(tmp!=NULL){
        for(int i=0; i<2*tmp->pr.brstTime; i++){
            cout<<"-";
        }
        cout<<"+";
        tmp = tmp->next;
    }

    tmp = queue;
    cout<<"\n0";
    while(tmp!=NULL){
        for(int i=0; i<2*tmp->pr.brstTime-1; i++){
            cout<<" ";
        }
        // cout<<tmp->cmpTime;
        printf("%2d", tmp->pr.cmplTime);
        tmp = tmp->next;
    }
    cout<<"\n\n";
}
int main()
{
    Queue *queueArrival = NULL;
    cout << "Enter the number of processes : ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        struct Process temp;
        cout << "Enter Process " << i + 1 << " name, its burst Time and Arrival Time : ";
        cin >> temp.Pname >> temp.brstTime >> temp.arvlTime;
        queueArrival = push(queueArrival, temp);
    }
    Calculate(queueArrival);
    display(queueArrival);
    printGanttChart(queueArrival);
    return 0;
}