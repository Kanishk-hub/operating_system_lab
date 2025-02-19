#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 5

int buffer[MAX_BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *param)
{
    int item;
    while (1)
    {
        item = rand() % 100; // Generate random item to produce

        sem_wait(&empty); // Decrease empty semaphore (buffer space)
        sem_wait(&mutex); // Enter critical section

        buffer[in] = item; // Add item to the buffer
        printf("Produced: %d\n", item);

        in = (in + 1) % MAX_BUFFER_SIZE; // Update the producer index

        sem_post(&mutex); // Exit critical section
        sem_post(&full);  // Increase full semaphore (there is a new item to consume)

        sleep(1); // Simulate time to produce an item
    }
}

void *consumer(void *param)
{
    int item;
    while (1)
    {
        sem_wait(&full);  // Decrease full semaphore (items available)
        sem_wait(&mutex); // Enter critical section

        item = buffer[out]; // Remove item from the buffer
        printf("Consumed: %d\n", item);

        out = (out + 1) % MAX_BUFFER_SIZE; // Update the consumer index

        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Increase empty semaphore (buffer space available)

        sleep(1); // Simulate time to consume an item
    }
}

int main()
{
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, MAX_BUFFER_SIZE); // Initially buffer is empty
    sem_init(&full, 0, 0);                // Initially buffer is full
    sem_init(&mutex, 0, 1);               // Mutex to ensure mutual exclusion

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
