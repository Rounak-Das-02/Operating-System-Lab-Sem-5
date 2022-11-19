#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int count = 0;
int times = 90000;

sem_t lock, full, empty;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < times; i++)
    {
        sem_wait(&full);
        sem_wait(&lock);
        printf("P : %d\n", count);
        count++;
        sem_post(&lock);
        sem_post(&empty);
    }
    // pthread_exit(NULL);
    return NULL;
}
void *consumer(void *arg)
{
    int i;
    for (i = 0; i < times; i++)
    {
        sem_wait(&empty);
        sem_wait(&lock);
        printf("C : %d\n", count);
        count--;
        sem_post(&lock);
        sem_post(&full);
    }
    return NULL;
    // pthread_exit(NULL);
}

int main()
{
    sem_init(&lock, 0, 1);
    sem_init(&empty, 0, 0);
    sem_init(&full, 0, 99);
    pthread_t p1, p2;
    printf("Initialcount: %d\n", count);
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, consumer, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("Finalcount:%d\n", count);
    pthread_exit(NULL);
    return 0;
}