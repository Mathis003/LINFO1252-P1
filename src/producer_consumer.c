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
    idx_buffer++;
    if (idx_buffer == CAPACITY_BUFFER) idx_buffer--;
}

void *producer(void *nbSteps)
{
    int *nberRepet = (int *) nbSteps;
    int item;
    for (int i = 0; i < *nberRepet; i++)
    {
        item = produce();
        // printf("Produced: %d\n", item);

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
    int item = buffer[idx_buffer];
    return item;
}

void *consumer(void *args)
{
    // int item;
    while (nbProductionsDone < NB_PRODUCTIONS)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        // item = remove_item();
        remove_item();
        nbProductionsDone++;
        // printf("Consumed: %d\n", item);

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

    sem_init(&empty, 0, CAPACITY_BUFFER);
    sem_init(&full, 0, 0);

    int *nbSteps = (int *) malloc(sizeof(int));
    if (nbSteps == NULL)
    {
        perror("malloc()");
        sem_destroy(&empty);
        sem_destroy(&full);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    *nbSteps = NB_PRODUCTIONS / nbProducers;
    int rest = NB_PRODUCTIONS % nbProducers;
    if (rest != 0) nbSteps++;

    int i;
    for (i = 0; i < nbProducers; i++)
    {
        if (pthread_create(&producers[i], NULL, producer, (void *) nbSteps) != 0)
        {
            perror("pthread_create()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            free(nbSteps);
            return EXIT_FAILURE;
        }

        rest--;
        if (rest == 0) (*nbSteps)--;
    }

    int j;
    for (j = 0; j < nbConsumers; j++)
    {
        if (pthread_create(&consumers[j], NULL, consumer, NULL) != 0)
        {
            perror("pthread_create()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            free(nbSteps);
            return EXIT_FAILURE;
        }
    }

    int k;
    for (k = 0; k < nbConsumers; k++)
    {
        if (pthread_join(consumers[i], NULL) != 0)
        {
            perror("pthread_join()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            free(nbSteps);
            return EXIT_FAILURE;
        }
    }

    int l;
    for (l = 0; l < nbProducers; l++)
    {
        if (pthread_join(producers[l], NULL) != 0)
        {
            perror("pthread_join()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            free(nbSteps);
            return EXIT_FAILURE;
        }
    }

    free(nbSteps);
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