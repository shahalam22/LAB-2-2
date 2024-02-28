#include <bits/stdc++.h>
using namespace std;

bool inQueue(queue<int> q, int p){
    while(!q.empty()){
        if(q.front() == p){
            return true;
        }
        q.pop();
    }
    return false;
}

int main(){
    int n, quantum_time;

    cout << "Enter the quantum time: ";
    cin >> quantum_time;

    ifstream file("FCFS.txt");
    file >> n;

    int process[n], arrival_time[n], burst_time[n], priority[n], waiting_time[n], turn_around_time[n], completion_time[n];

    for(int i=0; i<n; i++){
        file >> process[i] >> arrival_time[i] >> burst_time[i] >> priority[i];
    }

    file.close();


    //sorting the process according to the arribal time
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arrival_time[i] > arrival_time[j]){
                swap(process[i], process[j]);
                swap(arrival_time[i], arrival_time[j]);
                swap(burst_time[i], burst_time[j]);
                swap(priority[i], priority[j]);
            }
        }
    }


    int demo_burst_time[n];
    for(int i=0; i<n; i++){
        demo_burst_time[i] = burst_time[i];
    }

    queue<int> ready;
    ready.push(process[0]);
    int time = 0;

    cout << "Process\t\tStart Time\tEnd Time\n";

    while(!ready.empty()){
        int p = ready.front();
        ready.pop();

        int index = 0;
        for(int i=0; i<n; i++){
            if(process[i] == p){
                index = i;
                break;
            }
        }

        // // printing queue
        // cout << "Queue: ";
        // queue<int> temp = ready;
        // while(!temp.empty()){
        //     cout << "P" << temp.front() << " ";
        //     temp.pop();
        // }
        // cout << endl;

        if(demo_burst_time[index] > quantum_time){
            int temp_time = time;
            demo_burst_time[index] -= quantum_time;
            time += quantum_time;
            for(int i=0; i<n; i++){
                if(arrival_time[i] <= time && demo_burst_time[i] != 0 && process[i] != p){
                    if(!inQueue(ready, process[i]))
                        ready.push(process[i]);
                }
            }
            if(demo_burst_time[index] != 0){
                ready.push(p);
            }

            cout << "P" << p << "\t\t" << temp_time << "\t\t" << time << endl;
        }
        else{
            int temp_time = time;
            time += demo_burst_time[index];
            demo_burst_time[index] = 0;
            completion_time[index] = time;
            for(int i=0; i<n; i++){
                if(arrival_time[i] <= time && demo_burst_time[i] != 0 && process[i] != p){
                    if(!inQueue(ready, process[i]))
                        ready.push(process[i]);
                }
            }

            cout << "P" << p << "\t\t" << temp_time << "\t\t" << time << endl;
        }
    }


    // for(int i=0; i<n; i++){
    //     turn_around_time[i] = completion_time[i] - arrival_time[i];
    //     waiting_time[i] = turn_around_time[i] - burst_time[i];
    // }

}