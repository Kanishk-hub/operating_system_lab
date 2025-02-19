#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t mutex;
sem_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Pick up the left chopstick
        sem_wait(&chopsticks[id]);

        // Pick up the right chopstick
        sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);

        // Eating
        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // Put down the left chopstick
        sem_post(&chopsticks[id]);

        // Put down the right chopstick
        sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);

        printf("Philosopher %d is done eating\n", id);
    }
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&chopsticks[i], 0, 1); // Each chopstick is initially available
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for threads to finish (although they run infinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
