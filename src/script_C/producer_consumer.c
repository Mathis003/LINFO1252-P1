#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

#define NB_PRODUCTIONS 8192
#define CAPACITY_BUFFER 8

int buffer[CAPACITY_BUFFER];
int nbProductionsDone, nbConsumeDone = 0;
pthread_mutex_t mutex;
sem_t empty, full;
int idx_buffer = 0;


void treatment(void)
{
    for (int i = 0; i < 10000; i++);
}

int produce(void)
{
    return INT16_MIN + rand() % (INT16_MAX - INT16_MIN + 1);
}

void insert_item(int item)
{
    buffer[idx_buffer] = item;
    idx_buffer++;
}

void *producer(void *)
{
    int item;
    while (1)
    {
        item = produce();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        if (nbProductionsDone == NB_PRODUCTIONS)
        {
            sem_post(&full);
            pthread_mutex_unlock(&mutex);
            break;
        }

        insert_item(item);
        nbProductionsDone++;
        // printf("Is producing...\n");
        // printf("nbProductionsDone : %d\n", nbProductionsDone);
        sem_post(&full);
        pthread_mutex_unlock(&mutex);

        treatment();
    }
    return NULL;
}

int remove_item()
{
    idx_buffer--;
    return buffer[idx_buffer];
}

void *consumer(void *)
{
    int item;
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if (nbConsumeDone == NB_PRODUCTIONS)
        {
            sem_post(&empty);
            pthread_mutex_unlock(&mutex);
            break;
        }
        item = remove_item();

        // printf("buffer : [ ");
        // for (int i = 0; i < 8; i++) printf("%d ", buffer[i]);
        // printf(" ]\n");
        // printf("consumed : %d\n", item);
        
        nbConsumeDone++;
        // printf("Is consuming...\n");
        // printf("nbConsumeDone : %d\n", nbConsumeDone);

        sem_post(&empty);
        pthread_mutex_unlock(&mutex);
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
        sem_destroy(&empty);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    for (int idx_threads = 0; idx_threads < nbProducers; idx_threads++)
    {
        if (pthread_create(&producers[idx_threads], NULL, producer, NULL) != 0)
        {
            perror("pthread_create()");
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }

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

    if (pthread_mutex_destroy(&mutex) != 0)
    {
        perror("pthread_mutex_destroy()");
        sem_destroy(&empty);
        sem_destroy(&full);
        return EXIT_FAILURE;
    }

    if (sem_destroy(&empty) != 0)
    {
        perror("sem_destroy()");
        sem_destroy(&full);
        return EXIT_FAILURE;
    }

    if (sem_destroy(&full) != 0)
    {
        perror("sem_destroy()");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}