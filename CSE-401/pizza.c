#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define slice 8
#define student 5

sem_t pizza;
sem_t deliver;
int num_slices = 0;
pthread_mutex_t mutex;

void* student_thread(void* arg){
    while(1){
        sem_wait(&pizza);
        pthread_mutex_lock(&mutex);
        num_slices--;
        if(num_slices==0){
            sem_post(&deliver);
        }
        printf("Student %ld is studying while eating pizza .remainint slice is %d\n",(long)arg,num_slices);
        pthread_mutex_unlock(&mutex);

        
        sleep(1);

    }
    return NULL;
}


void* delivery_thread(void* arg){
    while(1){
        sem_wait(&deliver);
        printf("Pizza delivery in progress...........\n");
        sleep(2);
        pthread_mutex_lock(&mutex);
        num_slices=slice;
        for(int i=0;i<slice;i++){
            sem_post(&pizza);
        }
        printf("New pizza delivered with %d slices.\n",slice);
        pthread_mutex_unlock(&mutex);
        
    }
    return NULL;
}

int main(){
    sem_init(&pizza,0,0);
    sem_init(&deliver,0,1);
    pthread_mutex_init(&mutex,NULL);

    pthread_t students[student],delivery;

    for(long i=0;i<student;i++){
        pthread_create(students+i,NULL,student_thread,(void*)i);
    }
    pthread_create(&delivery,NULL,delivery_thread,NULL);

    for(int i=0;i<student;i++){
        pthread_join(students[i],NULL);
    }
    pthread_join(delivery,NULL);

    sem_destroy(&pizza);
    sem_destroy(&deliver);
    pthread_mutex_destroy(&mutex);

}
