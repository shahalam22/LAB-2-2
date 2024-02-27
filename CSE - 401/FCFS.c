#include <stdio.h>

int main(){
    int n;

    FILE *fp;
    fp = fopen("FCFS.txt", "r");
    if (fp == NULL){
        printf("File not found!\n");
        return 0;
    }else{
        fscanf(fp, "%d", &n);
    }

    printf("Number of processes: %d\n", n);

    int process[n], arrival_time[n], burst_time[n], priority[n], waiting_time[n], turn_around_time[n], completion_time[n], cpu_time[n];

    for(int i=0; i<n*3; i++){
        fscanf(fp, "%d", &process[i]);
        fscanf(fp, "%d", &arrival_time[i]);
        fscanf(fp, "%d", &burst_time[i]);
        fscanf(fp, "%d", &priority[i]);
    }

    
    // for(int i=0; i<n; i++){
    //     printf("Arrival Time: %d, Burst Time: %d, Priority: %d\n", arrival_time[i], burst_time[i], priority[i]);
    // }

    // sort using arrival time
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arrival_time[i] > arrival_time[j]){
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    printf("\nAfter sorting using arrival time:\n");
    for(int i=0; i<n; i++){
        printf("Arrival Time: %d, Burst Time: %d, Priority: %d\n", arrival_time[i], burst_time[i], priority[i]);
    }


    // calculation of cancelation time
    int time = 0;
    for(int i=0; i<n; i++){
        if(time > arrival_time[i]){
            cpu_time[i] = time;
            completion_time[i] = time + burst_time[i];
            time = completion_time[i];
        }else{
            cpu_time[i] = arrival_time[i];
            completion_time[i] = arrival_time[i] + burst_time[i];
            time = completion_time[i];
        }
    }


    printf("\nCompletion Time -\n");
    for(int i=0; i<n; i++){
        printf("Completion Time of P%d - %d\n", process[i], completion_time[i]);
    }

    // printing gnatt chart
    printf("\nGnatt Chart:\n");
    printf("Process\t\tStart Time\tEnd Time\n");
    for(int i=0; i<n; i++){
        printf("P%d\t\t%d\t\t%d\n", process[i], cpu_time[i], completion_time[i]);
    }

    // calculation of turn around time
    for(int i=0; i<n; i++){
        turn_around_time[i] = completion_time[i] - arrival_time[i];
    }

    printf("\nTurn Around Time -\n");
    for(int i=0; i<n; i++){
        printf("Turn Around Time of P%d - %d\n", process[i], turn_around_time[i]);
    }

    // calculation of waiting time
    for(int i=0; i<n; i++){
        waiting_time[i] = turn_around_time[i] - burst_time[i];
    }

    printf("\nWaiting Time -\n");
    for(int i=0; i<n; i++){
        printf("Waiting Time of P%d - %d\n", process[i], waiting_time[i]);
    }

    // average turn around time
    float avg_turn_around_time = 0;
    for(int i=0; i<n; i++){
        avg_turn_around_time += turn_around_time[i];
    }
    avg_turn_around_time /= n;

    printf("\nAverage Turn Around Time: %.2f\n", avg_turn_around_time);

    // average waiting time
    float avg_waiting_time = 0;
    for(int i=0; i<n; i++){
        avg_waiting_time += waiting_time[i];
    }
    avg_waiting_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);


    return 0;
}