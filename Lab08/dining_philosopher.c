#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int count = 0;
int times = 10;

sem_t chopstick[5];

void *eating(void *arg)
{
    int *i = arg;

    for (int k = 0; k < times; k++)
    {
        // Entry Section
        if (*i % 2 != 0)
        {
            sem_wait(&chopstick[(*i)]);
            sem_wait(&chopstick[((*i) + 1) % 5]);
        }
        else
        {
            sem_wait(&chopstick[((*i) + 1) % 5]);
            sem_wait(&chopstick[(*i)]);
        }

        // READING IS PERFORMED : CRITICAL SECTION
        // printf("%d and %d are busy\n", (*i), ((*i + 1) % 5));
        printf("EATING ... \n");

        // EXIT SECTION
        sem_post(&chopstick[(*i)]);
        sem_post(&chopstick[((*i) + 1) % 5]);
    }
}

int main()
{
    int philopsopher[5];

    for (int i = 0; i < 5; i++)
    {
        sem_init(&chopstick[i], 0, 1);
        philopsopher[i] = i;
    }

    // 5 philosopher thread instance
    pthread_t p1, p2, p3, p4, p5;

    // Creating 5 Philopher's threads for eating.

    pthread_create(&p1, NULL, eating, (void *)&philopsopher[0]);
    pthread_create(&p2, NULL, eating, (void *)&philopsopher[1]);
    pthread_create(&p3, NULL, eating, (void *)&philopsopher[2]);
    pthread_create(&p4, NULL, eating, (void *)&philopsopher[3]);
    pthread_create(&p5, NULL, eating, (void *)&philopsopher[4]);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);

    pthread_exit(NULL);
    return 0;
}