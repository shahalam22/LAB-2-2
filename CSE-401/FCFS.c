#include <stdio.h>

int main(){
    int n;

    FILE *fp;
    fp = fopen("FCFS2.txt", "r");
    if (fp == NULL){
        printf("File not found!\n");
        return 0;
    }else{
        fscanf(fp, "%d", &n);
    }

    int process[n], arrival_time[n], burst_time[n], priority[n], waiting_time[n], turn_around_time[n], completion_time[n], cpu_time[n];

    for(int i=0; i<n*3; i++){
        fscanf(fp, "%d", &process[i]);
        fscanf(fp, "%d", &arrival_time[i]);
        fscanf(fp, "%d", &burst_time[i]);
        fscanf(fp, "%d", &priority[i]);
    }


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


    // Gantt Chart
    printf("|");
    for(int i=0; i<n; i++){
        printf("---p%d---|", process[i]);
    }

    printf("\n%d", arrival_time[0]);
    for(int i=0; i<n; i++){
        printf("%9d", completion_time[i]);
    }

    printf("\n");
    

    // calculation of turn around time
    for(int i=0; i<n; i++){
        turn_around_time[i] = completion_time[i] - arrival_time[i];
    }


    // calculation of waiting time
    for(int i=0; i<n; i++){
        waiting_time[i] = turn_around_time[i] - burst_time[i];
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