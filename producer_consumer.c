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

int nbProductionsDone;
int *buffer;
int size_buffer;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;


void treatment(void)
{
    for (int i = 0; i < 10000; i++);
}

int produce(void)
{
    return rand() % MAX;
}

void insert_item(int item)
{
    buffer[size_buffer++] = item;
}

void *producer(void *nbSteps)
{
    int *nberRepet = (int *) nbSteps;
    int item;
    for (int i = 0; i < *nberRepet; i++)
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
    return buffer[size_buffer--];
}

void *consumer(void *args)
{
    // int item;
    while (nbProductionsDone != NB_PRODUCTIONS)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        remove_item();
        // item = remove_item();
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

    buffer = (int *) malloc(CAPACITY_BUFFER * sizeof(int));
    if (buffer == NULL)
    {
        perror("malloc()");
        return EXIT_FAILURE;
    }
    size_buffer = 0;
    nbProductionsDone = 0;
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        return EXIT_FAILURE;
    }
    sem_init(&empty, 0, CAPACITY_BUFFER);
    sem_init(&full, 0, 0);

    pthread_t producers[nbProducers];
    pthread_t consumers[nbConsumers];

    int nbSteps = NB_PRODUCTIONS / nbProducers;
    int rest = NB_PRODUCTIONS % nbProducers;
    if (rest != 0) nbSteps++;
    int i;

    for (i = 0; i < nbProducers; i++)
    {
        if (pthread_create(&producers[i], NULL, &producer, (void *) &nbSteps) != 0)
        {
            perror("pthread_create()");
            return EXIT_FAILURE;
        }

        rest--;
        if (rest == 0) nbSteps--;
    }

    i = 0;
    for (i = 0; i < nbConsumers; i++)
    {
        if (pthread_create(&consumers[i], NULL, &consumer, NULL) != 0)
        {
            perror("pthread_create()");
            return EXIT_FAILURE;
        }
    }

    i = 0;
    for (i = 0; i < nbConsumers; i++)
    {
        if (pthread_join(consumers[i], NULL) != 0)
        {
            perror("pthread_join()");
            return EXIT_FAILURE;
        }
    }

    i = 0;
    for (i = 0; i < nbProducers; i++)
    {
        if (pthread_join(producers[i], NULL) != 0)
        {
            perror("pthread_join()");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}