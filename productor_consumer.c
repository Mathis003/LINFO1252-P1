/*
Tâche 1.2 – Coder le problème des producteurs-consommateurs : 

- Une donnée produite ne doit jamais ‘écraser’ une donnée non consommée ! 
- Le nombre d’éléments produits (et donc consommé) est toujours de 8192.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

#define CAPACITY_BUFFER 8
#define MIN INT64_MIN
#define MAX INT64_MAX

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
    return rand() % (MAX - MIN + 1) + MIN;
}

void insert_item(int idx, int item)
{
    buffer[size_buffer++] = item;
}

void *producer(void *args)
{
    int nberRepet = 10;
    int item;
    for (int i = 0; i < nberRepet; i++)
    {
        item = produce();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        insert_item(empty.__size, item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        treatment();
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
    size_buffer = 0;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, CAPACITY_BUFFER);
    sem_init(&full, 0, 0);

    return EXIT_SUCCESS;
}