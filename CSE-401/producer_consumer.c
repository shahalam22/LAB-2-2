#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PROD_NUM 5
#define CONS_NUM 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, empty, full;

void producer_act(void* arg){
    int data;
    while(1){
        data = rand() % 100;
        
        sem_wait(&empty);
        sem_wait(&mutex);
        
        buffer[in] = data;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer %d produced - %d\n", pthread_self() % PROD_NUM, data);
        
        sem_post(&mutex);
        sem_post(&full);
    }
}

void consumer_act(void* arg){
    int data;
    while(1){
        sem_wait(&full);
        sem_wait(&mutex);
        
        data = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer %d consumed - %d\n", pthread_self() % CONS_NUM, data);
        
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main(){
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    
    pthread_t producer_threads[PROD_NUM];
    pthread_t consumer_threads[CONS_NUM];
    
    for(int i=0; i<PROD_NUM; i++){
        pthread_create(&producer_threads[i], NULL, producer_act, NULL);
    }
    
    for(int i=0; i<CONS_NUM; i++){
        pthread_create(&consumer_threads[i], NULL, consumer_act, NULL);
    }
    
    for(int i=0; i<CONS_NUM; i++){
        pthread_join(&producer_threads[i], NULL);
    }
    
    for(int i=0; i<CONS_NUM; i++){
        pthread_join(&consumer_threads[i], NULL);
    }
    
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
