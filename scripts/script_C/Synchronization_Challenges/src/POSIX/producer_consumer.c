#include "../../headers/producer_consumer.h"

void process(void)
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
    // printf("insert : idx_buffer = %d\n", idx_buffer);
}

void *producer(void *unused)
{
    while (1)
    {
        int item = produce();
        // printf("Produced : %d\n", item);

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
        // printf("nbProductionsDone : %d\n", nbProductionsDone);

        sem_post(&full);
        pthread_mutex_unlock(&mutex);

        process();
    }
    return NULL;
}

int remove_item()
{
    idx_buffer--;
    // int item = buffer[idx_buffer];
    // printf("remove : idx_buffer = %d\n", idx_buffer);
    return buffer[idx_buffer];
}

void *consumer(void *unused)
{
    // int item;
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
        
        remove_item();
        // item = remove_item();
        // printf("Consumed : %d\n", item);

        nbConsumeDone++;
        // printf("nbConsumeDone : %d\n", nbConsumeDone);

        sem_post(&empty);
        pthread_mutex_unlock(&mutex);

        process();
    }
    return NULL;
}

void destroy_all(void)
{
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
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

    for (int i = 0; i < nbProducers; i++)
    {
        if (pthread_create(&producers[i], NULL, producer, NULL) != 0)
        {
            perror("pthread_create()");
            destroy_all();
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbConsumers; i++)
    {
        if (pthread_create(&consumers[i], NULL, consumer, NULL) != 0)
        {
            perror("pthread_create()");
            destroy_all();
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbProducers; i++)
    {
        if (pthread_join(producers[i], NULL) != 0)
        {
            perror("pthread_join()");
            destroy_all();
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbConsumers; i++)
    {
        if (pthread_join(consumers[i], NULL) != 0)
        {
            perror("pthread_join()");
            destroy_all();
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