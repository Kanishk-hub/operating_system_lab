#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t read_mutex, write_mutex;
int read_count = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        sem_wait(&read_mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&write_mutex); // First reader locks the write mutex

        sem_post(&read_mutex);

        printf("Reader %d is reading\n", id);
        sleep(1);

        sem_wait(&read_mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&write_mutex); // Last reader releases the write mutex

        sem_post(&read_mutex);
        sleep(1);
    }
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        sem_wait(&write_mutex); // Writer locks the write mutex
        printf("Writer %d is writing\n", id);
        sleep(2);               // Simulate writing time
        sem_post(&write_mutex); // Writer releases the write mutex
        sleep(1);
    }
}

int main()
{
    pthread_t readers[3], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};

    // Initialize semaphores
    sem_init(&read_mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    // Create reader and writer threads
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (int i = 3; i < 5; i++)
    {
        pthread_create(&writers[i - 3], NULL, writer, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < 3; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&read_mutex);
    sem_destroy(&write_mutex);

    return 0;
}
