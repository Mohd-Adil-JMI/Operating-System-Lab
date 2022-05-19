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
void display(Queue *queue)
{
    Queue *temp=queue;
    while (temp != NULL)
    {
        cout << "Process : " << temp->pr.Pname<<endl;
        cout<< "Arrival time : "<<temp->pr.arvlTime<<endl;
        cout<< "Burst time : "<<temp->pr.brstTime<<endl;
        temp=temp->next;
    }
}
void GanttChart(Queue *queue){
    if(queue==NULL){
        cout<<"\nNo processes in the Queue";
        return;
    }
    cout<<"\n\nGantt Chart : ";
    Queue *temp=queue;
    cout<<"\n\n+";
    while (temp!=NULL)
    {
        cout<<temp->pr.Pname;
        temp->pr.brstTime--;
        if (temp->pr.brstTime!=0)
        {
            
        }
        
        temp=temp->next;
    }
    
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
    display(queueArrival);
    return 0;
}