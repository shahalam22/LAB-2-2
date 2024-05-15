#include <bits/stdc++.h>
using namespace std;


int main(){
    int n, quantum_time, completed = 0;

    ifstream file("SJF_P.txt");
    file >> n;

    int process[n], arrival_time[n], burst_time[n], priority[n], waiting_time[n], turn_around_time[n], completion_time[n];

    for(int i=0; i<n; i++){
        file >> process[i] >> burst_time[i] >> priority[i] >> arrival_time[i];
    }

    file.close();

    int temp_burst_time[n];
    for (int i = 0; i < n; i++){
        temp_burst_time[i] = burst_time[i];
    }
    

    // sorting the processes according to their arrival time and burst time
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if(arrival_time[j] > arrival_time[j+1]){
                swap(process[j], process[j+1]);
                swap(arrival_time[j], arrival_time[j+1]);
                swap(temp_burst_time[j], temp_burst_time[j+1]);
                swap(priority[j], priority[j+1]);
            }else if(arrival_time[j] == arrival_time[j+1]){
                if(temp_burst_time[j] > temp_burst_time[j+1]){
                    swap(process[j], process[j+1]);
                    swap(arrival_time[j], arrival_time[j+1]);
                    swap(temp_burst_time[j], temp_burst_time[j+1]);
                    swap(priority[j], priority[j+1]);
                }
            }
        }
    }

    // for(int i=0; i<n; i++){
    //     cout << process[i] << " " << arrival_time[i] << " " << temp_burst_time[i] << " " << priority[i] << endl;
    // }

    vector<int> ready_processes;
    int current_time = 0, completed_processes = 0;

    while(completed_processes < n){
        for(int i=0; i<n; i++){
            if(arrival_time[i] <= current_time && temp_burst_time[i] > 0){
                ready_processes.push_back(i);
            }
        }

        if(ready_processes.size() == 0){
            current_time++;
            continue;
        }

        int min_burst_time = INT_MAX, min_burst_index = -1;
        for(int i=0; i<ready_processes.size(); i++){
            if(temp_burst_time[ready_processes[i]] < min_burst_time){
                min_burst_time = temp_burst_time[ready_processes[i]];
                min_burst_index = ready_processes[i];
            }
        }

        temp_burst_time[min_burst_index]--;
        current_time++;

        if(temp_burst_time[min_burst_index] == 0){
            completion_time[min_burst_index] = current_time;
            completed_processes++;
            ready_processes.erase(remove(ready_processes.begin(), ready_processes.end(), min_burst_index), ready_processes.end());
        }
    }

    // Gantt Chart
    cout << "|";
    for(int i=0; i<n; i++){
        cout << "---P" << process[i] << "---|";
    }

    cout << endl;
    cout << arrival_time[0];
    for(int i=0; i<n; i++){
        printf("%9d", completion_time[i]);
    }

    cout << endl;


    // calculating waiting time and turn around time
    for(int i=0; i<n; i++){
        turn_around_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turn_around_time[i] - burst_time[i];
    }

    // average turn around time and waiting time
    float avg_turn_around_time = 0, avg_waiting_time = 0;
    for(int i=0; i<n; i++){
        avg_turn_around_time += turn_around_time[i];
        avg_waiting_time += waiting_time[i];
    }  

    avg_turn_around_time /= n;
    avg_waiting_time /= n;

    cout << "Average Turn Around Time: " << avg_turn_around_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
}