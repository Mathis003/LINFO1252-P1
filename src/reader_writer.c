#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

#define NB_READS 2560
#define NB_WRITES 640

pthread_mutex_t readMutex;
sem_t writeSem, queueSem;
int readCount = 0;
int readsDone = 0;
int writesDone = 0;
int database = 0;

void read_database()
{
    printf("read value: %d\n", database);
}

void write_database()
{
    database++;
    printf("wrote value: %d\n", database);
}

void *reader(void *arg)
{
    while (true)
    {
        sem_wait(&queueSem);
        pthread_mutex_lock(&readMutex);
        // critical section : begin
        readCount++;
        readsDone++;
        if (readCount == 1) sem_wait(&writeSem); // first reader arrives
        // critical section : end
        pthread_mutex_unlock(&readMutex);
        sem_post(&queueSem);

        if (readsDone >= NB_READS)
        {
            pthread_mutex_lock(&readMutex);
            // critical section : begin
            readCount--;
            if (readCount == 0) sem_post(&writeSem); // last reader leaves
            // critical section : end
            pthread_mutex_unlock(&readMutex);
            break;
        }
        
        read_database();

        pthread_mutex_lock(&readMutex);
        // critical section : begin
        readCount--;
        if (readCount == 0) sem_post(&writeSem); // last reader leaves
        // critical section : end
        pthread_mutex_unlock(&readMutex);
    }
}


void *writer(void *arg)
{
    while (true)
    {
        sem_wait(&queueSem);
        sem_wait(&writeSem);
        writesDone++;
        if (writesDone >= NB_WRITES)
        {
            sem_post(&writeSem);
            sem_post(&queueSem);
            break;
        }
        // critical section
        write_database();
        sem_post(&writeSem);
        sem_post(&queueSem);
    }
}

void free_all(pthread_t *writters, pthread_t *readers)
{
    free(writters);
    free(readers);
    sem_destroy(&writeSem);
    sem_destroy(&queueSem);
    pthread_mutex_destroy(&readMutex);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("argc != 3");
        return EXIT_FAILURE;
    }

    const int nbReaders = atoi(argv[1]);
    const int nbWritters = atoi(argv[2]);

    if (nbWritters < 1 || nbReaders < 1)
    {
        perror("0 Readers or 0 Writters!");
        return EXIT_FAILURE;
    }

    int error = 0;
    error += sem_init(&writeSem, 0, 1);
    error += sem_init(&queueSem, 0, 1);
    if (error != 0)
    {
        perror("sem_init()");
        sem_destroy(&writeSem);
        sem_destroy(&queueSem);
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&readMutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        sem_destroy(&writeSem);
        sem_destroy(&queueSem);
        return EXIT_FAILURE;
    }

    pthread_t *writters = malloc(sizeof(pthread_t) * nbWritters);
    pthread_t *readers = malloc(sizeof(pthread_t) * nbReaders);

    for (int i = 0; i < nbWritters; i++)
    {
        if (pthread_create(&writters[i], NULL, writer, NULL) != 0)
        {
            perror("pthread_create()");
            free_all(writer, reader);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbReaders; i++)
    {
        if (pthread_create(&readers[i], NULL, reader, NULL) != 0)
        {
            perror("pthread_create()");
            free_all(writer, reader);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbWritters; i++)
    {
        if (pthread_join(writters[i], NULL) != 0)
        {
            perror("pthread_join()");
            free_all(writer, reader);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbReaders; i++)
    {
        if (pthread_join(readers[i], NULL) != 0)
        {
            perror("pthread_join()");
            free_all(writer, reader);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}