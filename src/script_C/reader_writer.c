#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

#define NB_READS 2560
#define NB_WRITES 640

/*
* Remarque Assistant:
* Bloqué tous les readers dès que y'a un writer.
* Les writers ont priorités!
* Quand plus de writers (et uniquement dans ce cas ci) => readers se libèrent en cascade.
*/

pthread_mutex_t writer_mutex, reader_mutex, z;
sem_t db_writer, db_reader;

int readsDone, writesDone = 0;
int readersCount, writersCount = 0;

void read_database()
{
    for (int i = 0; i < 10000; i++);
    printf("Reading...: readsDone: %d, writesDone: %d\n", readsDone, writesDone);
}

void write_database()
{
    for (int i = 0; i < 10000; i++);
    printf("Writing... readsDone: %d, writesDone: %d\n", readsDone, writesDone);
}

void *reader(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&z);

        sem_wait(&db_reader);

        pthread_mutex_lock(&reader_mutex);
        readersCount++;

        if (readersCount == 1)
        {
            sem_wait(&db_writer);
        }

        pthread_mutex_unlock(&reader_mutex);
        sem_post(&db_reader);


        pthread_mutex_unlock(&z);

        if (readsDone >= NB_READS)
        {
            sem_post(&db_writer);
            break;
        }

        read_database();
        readsDone++;


        pthread_mutex_lock(&reader_mutex);
        readersCount--;
        if (readersCount == 0)
        {
            sem_post(&db_writer);
        }

        pthread_mutex_unlock(&reader_mutex);
    }
}

void *writer(void *arg)
{
    while (1)
    {

        sem_wait(&db_reader);
        sem_wait(&db_writer);


        if (writesDone == NB_WRITES)
        {
            sem_post(&db_reader);
            sem_post(&db_writer);
            break;
        }

        write_database();
        writesDone++;


        sem_post(&db_writer);
        sem_post(&db_reader);
    }
}

void free_all(pthread_t *writers, pthread_t *readers)
{
    free(writers);
    free(readers);
    sem_destroy(&db_writer);
    sem_destroy(&db_reader);
    pthread_mutex_destroy(&writer_mutex);
    pthread_mutex_destroy(&reader_mutex);
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
    // Semaphore bc sem_wait() and sem_post() are not always called by the same thread!
    error += sem_init(&db_writer, 0, 1);
    error += sem_init(&db_reader, 0, 1);
    if (error != 0)
    {
        perror("sem_init()");
        sem_destroy(&db_writer);
        sem_destroy(&db_reader);
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&writer_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        sem_destroy(&db_writer);
        sem_destroy(&db_reader);
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&reader_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        sem_destroy(&db_writer);
        sem_destroy(&db_reader);
        return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&z, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        sem_destroy(&db_writer);
        sem_destroy(&db_reader);
        pthread_mutex_destroy(&writer_mutex);
        return EXIT_FAILURE;
    }

    pthread_t *writers = malloc(sizeof(pthread_t) * nbWriters);
    pthread_t *readers = malloc(sizeof(pthread_t) * nbReaders);

    for (int i = 0; i < nbWriters; i++)
    {
        if (pthread_create(&writers[i], NULL, writer, NULL) != 0)
        {
            perror("pthread_create()");
            free_all(writers, readers);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbReaders; i++)
    {
        if (pthread_create(&readers[i], NULL, reader, NULL) != 0)
        {
            perror("pthread_create()");
            free_all(writers, readers);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbWriters; i++)
    {
        if (pthread_join(writers[i], NULL) != 0)
        {
            perror("pthread_join()");
            free_all(writers, readers);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nbReaders; i++)
    {
        if (pthread_join(readers[i], NULL) != 0)
        {
            perror("pthread_join()");
            free_all(writers, readers);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}