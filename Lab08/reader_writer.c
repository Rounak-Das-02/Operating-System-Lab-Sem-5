#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int count = 0;
int times = 10;

sem_t mutex, db;
int read_count = 0;

void *reader(void *arg)
{
    for (int i = 0; i < times; i++)
    {
        // Entry Section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
        {
            sem_wait(&db);
        }
        sem_post(&mutex);

        // READING IS PERFORMED : CRITICAL SECTION
        printf("READING .... \n Number of readers, right now is : %d \n", read_count);
        // sleep(1);

        // EXIT SECTION
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&db);
        sem_post(&mutex);
    }
}

void *writer(void *arg)
{
    for (int i = 0; i < times; i++)
    {
        // Entry Section
        sem_wait(&db);

        // Writing is performed ... Critical Section
        printf("WRITING .... \n Number of readers, right now is : %d \n", read_count);
        // sleep(1);

        // Exit section
        sem_post(&db);
    }
}

int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);

    pthread_t reader1, reader2, reader3, reader4;
    pthread_t writer1, writer2;

    // printf("Initialcount: %d\n", count);

    pthread_create(&reader1, NULL, reader, NULL);
    pthread_create(&writer1, NULL, writer, NULL);
    pthread_create(&writer2, NULL, writer, NULL);
    pthread_create(&reader2, NULL, reader, NULL);
    pthread_create(&reader3, NULL, reader, NULL);
    pthread_create(&reader4, NULL, reader, NULL);

    pthread_join(writer2, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(writer1, NULL);
    // printf("Finalcount:%d\n", count);
    pthread_exit(NULL);
    return 0;
}