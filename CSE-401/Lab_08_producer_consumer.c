#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int buffer[10];
int in = 0, out = 0;

sem_t mutex;
sem_t empty;
sem_t full;

void* producer(void* arg){
    int item;
    while(1){
        sleep(1);
        item = rand()%10;
        
        sem_wait(&empty);
        
        sem_wait(&mutex);
        
        buffer[in] = item;
        in = (in+1)%10;
        printf("Producer produced: %d\n", item);
        
        sem_post(&mutex);
        
        sem_post(&full);
    }
}

void* consumer(void* arg){
    int item;
    while(1){
        sem_wait(&full);
        
        sem_wait(&mutex);
        
        item = buffer[out];
        out = (out + 1)%10;
        printf("Consumer Consumed: %d\n", item);
        
        sem_post(&mutex);
        
        sem_post(&empty);
    }
}

int main(){
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    //pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    //pthread_join(consumer_thread, NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
