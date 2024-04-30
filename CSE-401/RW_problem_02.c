// readers-writers problem 02 : writers preference

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 10
#define NUM_WRITERS 5

sem_t rmutex, wmutex, readTry, resource;
int readcount = 0, writecount = 0;    

void* writer() {
    // entry
    sem_wait(&wmutex);
    
    writecount++;
    if(writecount == 1){
        sem_wait(&readTry);
    }
    
    sem_post(&wmutex);
    
    // resource capture
    sem_wait(&resource);
    
    printf("Writer %lu is writing...\n", pthread_self() % 100);
    sleep(1);
    
    sem_post(&resource);
    
    // exit
    sem_wait(&wmutex);
    
    writecount--;
    if(writecount == 0){
        sem_post(&readTry);
    }
    
    sem_post(&wmutex);
}

void* reader() {
    sem_wait(&readTry);    
    sem_wait(&rmutex);
    
    readcount++;          
    if (readcount == 1) {  
        sem_wait(&resource);    
    }
    
    sem_post(&rmutex);
    sem_post(&readTry);

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
    sem_init(&wmutex, 0, 1);
    sem_init(&readTry, 0, 1);
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
    sem_destroy(&resource);
    
    return 0;
}
