#include<bits/stdc++.h>
using namespace std;

struct Process{
    char Pname[3];
    int arvlTime;
    int brstTime; 
    int cmplTime;
    int wtngTime;
    int tartTime;
    int respTime;
};

vector<Process> v;
int n;
float avgc, avgw, avgt;

bool comparator(const Process& lhs, const Process& rhs) {
   return lhs.arvlTime > rhs.arvlTime;
}
bool operator< (const Process& a1, const Process &a2){
    return a1.brstTime > a2.brstTime;
}

void SJF(vector<Process> v2){
    int cmpt = v2.back().brstTime;
    v.push_back(v2.back());
    v2.pop_back();

    priority_queue<Process, vector<Process>,less<vector<Process>::value_type>> pq;

    while(!v2.empty()){
        while(!v2.empty() && v2.back().arvlTime < cmpt){
            pq.push(v2.back());
            v2.pop_back();
        }

        cmpt += pq.top().brstTime;
        v.push_back(pq.top());
        pq.pop();
    }

    while(!pq.empty()){
        v.push_back(pq.top());
        pq.pop();
    }
}

void calculateTimes(){
    v.front().wtngTime=0;
    v.front().cmplTime = v.front().brstTime;
    float sumc=0, sumw=0, sumt=0;

    //calculating completion time
    int prv = v.front().cmplTime;
    sumc += prv;
    for(int i=1; i<n; i++){
        v[i].cmplTime = prv + v[i].brstTime;
        prv = v[i].cmplTime;
        sumc += v[i].cmplTime;
    }

    //calculating waiting time
    prv = v.front().cmplTime;
    for(int i=1; i<n; i++){
        v[i].wtngTime = prv - v[i].arvlTime;
        prv = v[i].cmplTime;
        sumw += v[i].wtngTime;
    }

    //calculating turn around time
    for(int i=0; i<n; i++){
        v[i].tartTime = v[i].brstTime + v[i].wtngTime;
        sumt += v[i].tartTime;
    }

    //calculating avg(s) time
    avgc = sumc/n;
    avgw = sumw/n;
    avgt = sumt/n;
}

void display(){
    cout<<"\n\nDisplaying the table :- ";

    cout<<"\n\n+--------------+------------+--------------+-----------------+--------------+-----------------+---------------+";
    cout<<"\n| Process name | Burst Time | Arrival Time | Completion Time | Waiting Time | TurnAround Time | Response Time |";
    cout<<"\n+--------------+------------+--------------+-----------------+--------------+-----------------+---------------+";

    for(auto i:v){
        printf("\n|      %s      |    %2d      |      %2d      |        %2d       |      %2d      |      %2d         |      %2d       |"
               ,i.Pname, i.brstTime, i.arvlTime, i.cmplTime, i.wtngTime, i.tartTime, i.wtngTime);
    cout<<"\n+--------------+------------+--------------+-----------------+--------------+-----------------+---------------+";
    }

    cout<<"\n\n";
    printf("\nAverage Completion time : %.2fns", avgc);
    printf("\nAverage Waiting time : %.2fns", avgw);
    printf("\nAverage TurnAround time : %.2fns", avgt);
    printf("\nAverage Response time : %.2fns", avgw);
}

void printGantt(){

    cout<<"\n\nGantt Chart : ";

    cout<<"\n\n+";
    for(auto p:v){
        for(int i=0; i<2*p.brstTime; i++){
            cout<<"-";
        }
        cout<<"+";
    }

    cout<<"\n|";
    for(auto p:v){
        for(int i=0; i<p.brstTime-1; i++){
            cout<<" ";
        }
        cout<<p.Pname;
        for(int i=0; i<p.brstTime-1; i++){
            cout<<" ";
        }
        cout<<"|";
    }

    cout<<"\n+";
    for(auto p:v){
        for(int i=0; i<2*p.brstTime; i++){
            cout<<"-";
        }
        cout<<"+";
    }

    cout<<"\n0";
    for(auto p:v){
        for(int i=0; i<2*p.brstTime-1; i++){
            cout<<" ";
        }
        printf("%2d", p.cmplTime);
    }
    cout<<"\n\n";
}

int main(){
    vector<Process> v2;

    cout<<"Enter the no of the Processes : ";
    cin>>n;

    for(int i=0; i<n; i++){
        struct Process p;
        cout<<"Enter Process "<<i+1<<" name, its burst Time and Arrival Time : ";
        cin>>p.Pname>>p.brstTime>>p.arvlTime;
        v2.push_back(p);
    }

    //sorting the vector acc to arrival time
    sort(v2.begin(), v2.end(), &comparator);

    //sort according to arrival time + burst Time :
    SJF(v2);
    calculateTimes();


    display();
    printGantt();
    return 0;
}

// 5 P1 6 2 P2 2 5 P3 8 1 P4 3 0 P5 4 4