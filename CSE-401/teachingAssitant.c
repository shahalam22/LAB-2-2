#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // memset
#include <pthread.h>   // pthread_t, pthread_create, pthread_join
#include <semaphore.h> // sem_init, sem_wait, sem_post
#include <time.h>
#include <unistd.h>

#define NUM_SEAT 3
#define SLEEP_MAX 5

// Semaphores
sem_t sem_stu; // 0
sem_t sem_ta;  // 1

// Semaphore as a mutex for accessing chairs
sem_t mutex;

int chair[NUM_SEAT];
int waiting_student = 0; // number of waiting students
int next_seat = 0;       // index of next seat
int next_teach = 0;      // index of the student, who will be next taught

void rand_sleep(void);
void *stu_programming(void *stu_id);
void *ta_teaching(void *arg);

int main()
{
    int student_num;

    // Get number of students from user
    printf("Enter the number of students: ");
    scanf("%d", &student_num);

    if (student_num == 0)
    {
        printf("TA sleeping, no students! \n");
        exit(1);
    }

    pthread_t students[student_num];
    pthread_t ta;
    int student_ids[student_num];

    sem_init(&sem_stu, 0, 0); // initially locked
    sem_init(&sem_ta, 0, 1);  // initially available
    sem_init(&mutex, 0, 1);   // initialize mutex as unlocked

    // Set random seed
    srand(time(NULL));

    // Create TA thread
    pthread_create(&ta, NULL, ta_teaching, NULL);

    // Create student threads
    for (int i = 0; i < student_num; i++)
    {
        student_ids[i] = i + 1;
        pthread_create(&students[i], NULL, stu_programming, (void
*)&student_ids[i]);
    }

    // Join TA thread
    pthread_join(ta, NULL);

    // Join student threads
    for (int i = 0; i < student_num; i++)
    {
        pthread_join(students[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&sem_stu);
    sem_destroy(&sem_ta);
    sem_destroy(&mutex);

    return 0;
}

void *stu_programming(void *stu_id)
{
    int id = *(int *)stu_id;

    printf("[stu] Student %d is leaving for TA office\n", id);

    while (1)
    {
        rand_sleep();

        sem_wait(&mutex); // Lock to access chair[]

        if (waiting_student < NUM_SEAT)
        {
            chair[next_seat] = id;
            waiting_student++; // Increment waiting student count

            printf("[stu] Student %d is waiting seated at hallway\n", id);
            printf("Waiting students: [1] %d [2] %d [3] %d\n",
chair[0], chair[1], chair[2]);
            next_seat = (next_seat + 1) % NUM_SEAT;

            sem_post(&mutex); // Unlock mutex

            // Wake up TA
            sem_post(&sem_stu); // Increase student semaphore value (waiting++)
            sem_wait(&sem_ta);  // Wait for TA to be available
        }
        else // No more chairs available
        {
            sem_post(&mutex); // Unlock mutex

            printf("[stu] No more chairs. Student %d is outside
hallway and will be back later\n", id);
        }
    }
}

void *ta_teaching(void *arg)
{
    while (1)
    {
        if (waiting_student == 0)
        {
            printf("TA is sleeping Zzz, as there are no waiting students\n");
        }

        sem_wait(&sem_stu); // Wait for student to wake up TA

        sem_wait(&mutex); // Lock to access chair[]

        printf("[ta] TA is teaching student %d\n", chair[next_teach]);
        chair[next_teach] = 0;
        waiting_student--; // Decrement waiting student count

        printf("Waiting students: [1] %d [2] %d [3] %d\n", chair[0],
chair[1], chair[2]);
        next_teach = (next_teach + 1) % NUM_SEAT;

        rand_sleep();

        printf("[ta] Teaching finished.\n");

        sem_post(&mutex); // Unlock mutex

        sem_post(&sem_ta); // Make TA available again
    }
}

void rand_sleep(void)
{
    int time = rand() % SLEEP_MAX + 1;
    sleep(time);
}
