// readers-writers problem 03 : serve the one in FIFO manner

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 10
#define NUM_WRITERS 5

sem_t rmutex, resource, serviceQueue;
int readcount = 0, writecount = 0;    

void* writer() {
    // entry
    sem_wait(&serviceQueue);
    sem_wait(&resource);
    sem_post(&serviceQueue);
    
    printf("Writer %lu is writing...\n", pthread_self() % 100);
    sleep(1);
    
    sem_post(&resource);
}

void* reader() {
    sem_wait(&serviceQueue);    
    sem_wait(&rmutex);
    
    readcount++;          
    if (readcount == 1) {  
        sem_wait(&resource);    
    }
    
    sem_post(&serviceQueue);
    sem_post(&rmutex);

    printf("Reader %lu is reading...\n", pthread_self() % 100);
    sleep(1);

    sem_wait(&rmutex);

    readcount--;          
    if (readcount == 0) {   
        sem_post(&resource);    
    }
    sem_post(&rmutex);          
}

int main() {
    sem_init(&rmutex, 0, 1);
    sem_init(&serviceQueue, 0, 1);
    sem_init(&resource, 0, 1);
    
    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writer_threads[i], NULL, writer, NULL);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }
    
    sem_destroy(&rmutex);
    sem_destroy(&serviceQueue);
    sem_destroy(&resource);
    
    return 0;
}
