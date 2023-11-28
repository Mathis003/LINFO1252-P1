#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

#define NB_READS 2560
#define NB_WRITES 640

pthread_mutex_t writer_mutex, reader_mutex, general_mutex;
sem_t db_writer, db_reader;

int readsAuthorized, writesDone = 0;
int readersCount, writersCount = 0;

void process(void)
{
    for (int i = 0; i < 10000; i++);
}

void read_database()
{
    process();
    printf("Reading...\n");
    printf("readsAuthorized: %d, writesDone: %d\n", readsAuthorized, writesDone);
}

void write_database()
{
    process();
    printf("Writing...\n");
    printf("readsAuthorized: %d, writesDone: %d\n", readsAuthorized, writesDone);
}

void *reader(void *unused)
{
    while (1)
    {
        pthread_mutex_lock(&general_mutex);

        sem_wait(&db_reader);

        pthread_mutex_lock(&reader_mutex);

        if (readsAuthorized >= NB_READS)
        {
            pthread_mutex_unlock(&general_mutex);
            sem_post(&db_reader);
            pthread_mutex_unlock(&reader_mutex);
            break;
        }
        
        readsAuthorized++;
        readersCount++;
        
        if (readersCount == 1)
        {
            sem_wait(&db_writer);
        }
        
        pthread_mutex_unlock(&reader_mutex);

        sem_post(&db_reader);

        pthread_mutex_unlock(&general_mutex);

        read_database(); //Critical section

        pthread_mutex_lock(&reader_mutex);

        readersCount--;
        if (readersCount == 0)
        {
            sem_post(&db_writer);
        }

        pthread_mutex_unlock(&reader_mutex);
    }
    return NULL;
}

void *writer(void *unused)
{
    while (1)
    {
        sem_wait(&db_reader);
        sem_wait(&db_writer);

        if (writesDone == NB_WRITES)
        {
            sem_post(&db_writer);
            sem_post(&db_reader);
            break;
        }

        write_database();
        writesDone++;

        sem_post(&db_writer);
        sem_post(&db_reader);
    }
    return NULL;
}

int destroy_sem()
{
    int value = 1;
    if (sem_destroy(&db_writer) != 0) value = 0;
    if (sem_destroy(&db_reader) != 0) value = 0;
    return value;
}

int destroy_all()
{
    int value = destroy_sem();
    if (pthread_mutex_destroy(&writer_mutex) != 0) value = 0;
    if (pthread_mutex_destroy(&reader_mutex) != 0) value = 0;
    if (pthread_mutex_destroy(&general_mutex) != 0) value = 0;
    return value;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("argc != 3");
        return EXIT_FAILURE;
    }

    const int nbReaders = atoi(argv[1]);
    const int nbWriters = atoi(argv[2]);

    if (nbWriters < 1 || nbReaders < 1)
    {
        perror("0 Readers or 0 Writters!");
        return EXIT_FAILURE;
    }

    int error = 0;
    error += sem_init(&db_writer, 0, 1);
    error += sem_init(&db_reader, 0, 1);
    if (error != 0)
    {
        perror("sem_init()");
        destroy_sem();
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&writer_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        destroy_sem();
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&reader_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        pthread_mutex_destroy(&writer_mutex);
        destroy_sem();
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&general_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        destroy_sem();
        pthread_mutex_destroy(&writer_mutex);
        pthread_mutex_destroy(&reader_mutex);
        return EXIT_FAILURE;
    }

    pthread_t writers[nbWriters];
    pthread_t readers[nbReaders];

    for (int i = 0; i < nbWriters; i++)
    {
        if (pthread_create(&writers[i], NULL, writer, NULL) != 0)
        {
            perror("pthread_create()");
            destroy_all();
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbReaders; i++)
    {
        if (pthread_create(&readers[i], NULL, reader, NULL) != 0)
        {
            perror("pthread_create()");
            destroy_all();
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbWriters; i++)
    {
        if (pthread_join(writers[i], NULL) != 0)
        {
            perror("pthread_join()");
            destroy_all();
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbReaders; i++)
    {
        if (pthread_join(readers[i], NULL) != 0)
        {
            perror("pthread_join()");
            destroy_all();
            return EXIT_FAILURE;
        }
    }

    if (destroy_all() == 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}