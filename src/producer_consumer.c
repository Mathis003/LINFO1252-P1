#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

#define NB_PRODUCTIONS 8192
#define CAPACITY_BUFFER 8
#define MIN INT64_MIN
#define MAX INT64_MAX

int buffer[CAPACITY_BUFFER];
int nbProductionsDone = 0;
int idx_buffer = 0;

pthread_mutex_t mutex;
sem_t empty, full;

void treatment(void)
{
    for (int i = 0; i < 10000; i++);
}

int produce(void)
{
    return rand() % 100;
    // return rand() % MAX;
}

void insert_item(int item)
{
    buffer[idx_buffer] = item;
    idx_buffer = (idx_buffer == CAPACITY_BUFFER) ? idx_buffer : idx_buffer + 1;
}

void *producer(void *args)
{
    int *nbSteps = (int *) args;
    int item;
    for (int i = 0; i < *nbSteps; i++)
    {
        item = produce();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        insert_item(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        treatment();
    }
    return NULL;
}

int remove_item()
{
    idx_buffer--;
    return buffer[idx_buffer];
}

void *consumer(void *args)
{
    int item;
    while (nbProductionsDone < NB_PRODUCTIONS)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // printf("%d\n", nbProductionsDone);
        item = remove_item();
        nbProductionsDone++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("argc != 3");
        return EXIT_FAILURE;
    }

    const int nbConsumers = atoi(argv[1]);
    const int nbProducers = atoi(argv[2]);

    if (nbConsumers < 1 || nbProducers < 1)
    {
        perror("0 Producer or 0 Consumer!");
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        return EXIT_FAILURE;
    }

    pthread_t producers[nbProducers];
    pthread_t consumers[nbConsumers];

    if (sem_init(&empty, 0, CAPACITY_BUFFER) != 0)
    {
        perror("sem_init()");
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }
    if (sem_init(&full, 0, 0) !=  0)
    {
        perror("sem_init()");
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    int nbSteps = NB_PRODUCTIONS / nbProducers;
    int *ptr_nbSteps = &nbSteps;
    int rest = NB_PRODUCTIONS % nbProducers;
    if (rest != 0) (*ptr_nbSteps)++;

    int cnter = 0;

    for (int idx_threads = 0; idx_threads < nbProducers; idx_threads++)
    {
        cnter += *ptr_nbSteps;
        if (pthread_create(&producers[idx_threads], NULL, producer, (void *) ptr_nbSteps) != 0)
        {
            perror("pthread_create()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }

        rest--;
        if (rest == 0) (*ptr_nbSteps)--;
    }

    printf("%d\n", cnter);

    for (int idx_threads = 0; idx_threads < nbConsumers; idx_threads++)
    {
        if (pthread_create(&consumers[idx_threads], NULL, consumer, NULL) != 0)
        {
            perror("pthread_create()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }

    for (int idx_threads = 0; idx_threads < nbProducers; idx_threads++)
    {
        if (pthread_join(producers[idx_threads], NULL) != 0)
        {
            perror("pthread_join()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbConsumers; i++) sem_post(&full);


    for (int idx_threads = 0; idx_threads < nbConsumers; idx_threads++)
    {
        if (pthread_join(consumers[idx_threads], NULL) != 0)
        {
            perror("pthread_join()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }

    printf("%d\n", nbProductionsDone);

    if (pthread_mutex_destroy(&mutex) != 0)
    {
        perror("pthread_mutex_destroy()");
        sem_destroy(&empty);
        sem_destroy(&full);
        return EXIT_FAILURE;
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    return EXIT_SUCCESS;
}