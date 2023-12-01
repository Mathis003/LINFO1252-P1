#include "../headers/producer_consumer.h"

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

        wait_sem(&empty);
        lock_mutex(&mutex);

        if (nbProductionsDone == NB_PRODUCTIONS)
        {
            post_sem(&full);
            unlock_mutex(&mutex);
            break;
        }

        insert_item(item);

        nbProductionsDone++;
        printf("nbProductionsDone : %d\n", nbProductionsDone);

        post_sem(&full);
        unlock_mutex(&mutex);

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
        wait_sem(&full);
        lock_mutex(&mutex);

        if (nbConsumeDone == NB_PRODUCTIONS)
        {
            post_sem(&empty);
            unlock_mutex(&mutex);
            break;
        }
        
        remove_item();
        // item = remove_item();
        // printf("Consumed : %d\n", item);

        nbConsumeDone++;
        printf("nbConsumeDone : %d\n", nbConsumeDone);

        post_sem(&empty);
        unlock_mutex(&mutex);

        process();
    }
    return NULL;
}

void destroy_all(void)
{
    destroy_sem(&empty);
    destroy_sem(&full);
    destroy_mutex(&mutex);
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

    if (init_mutex(&mutex) != 0)
    {
        perror("init_mutex()");
        return EXIT_FAILURE;
    }

    pthread_t producers[nbProducers];
    pthread_t consumers[nbConsumers];

    if (init_sem(&empty, 0, CAPACITY_BUFFER) != 0)
    {
        perror("init_sem()");
        destroy_mutex(&mutex);
        return EXIT_FAILURE;
    }

    if (init_sem(&full, 0, 0) !=  0)
    {
        perror("init_sem()");
        destroy_sem(&empty);
        destroy_mutex(&mutex);
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

    if (destroy_mutex(&mutex) != 0)
    {
        perror("destroy_sem()");
        destroy_sem(&empty);
        destroy_sem(&full);
        return EXIT_FAILURE;
    }

    if (destroy_sem(&empty) != 0)
    {
        perror("destroy_sem()");
        destroy_sem(&full);
        return EXIT_FAILURE;
    }

    if (destroy_sem(&full) != 0)
    {
        perror("destroy_sem()");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}