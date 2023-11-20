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

int readsDone, writesDone = 0;
int readersCount, writersCount = 0;

void read_database()
{
    for (int i = 0; i < 10000; i++);
    printf("Reading...\n");
    printf("readsDone: %d, writesDone: %d\n", readsDone, writesDone);
}

void write_database()
{
    for (int i = 0; i < 10000; i++);
    printf("Writing...\n");
    printf("readsDone: %d, writesDone: %d\n", readsDone, writesDone);
}

void *reader(void *unused)
{
    while (1)
    {
        // ** Section Begin : General ** //
        pthread_mutex_lock(&general_mutex);

        sem_wait(&db_reader);

        // ** Section Begin : Readers ** //
        pthread_mutex_lock(&reader_mutex);

        readersCount++;
        if (readersCount == 1)
        {
            sem_wait(&db_writer);
        }

        pthread_mutex_unlock(&reader_mutex);
        // ** Section End : Readers ** //

        sem_post(&db_reader);

        pthread_mutex_unlock(&general_mutex);
        // ** Section End : General ** //

        if (readsDone >= NB_READS)
        {
            sem_post(&db_writer);
            sem_post(&db_reader);
            break;
        }

        read_database();

        // ** Section Begin : Readers ** //
        pthread_mutex_lock(&reader_mutex);

        readsDone++;
        readersCount--;
        if (readersCount == 0)
        {
            sem_post(&db_writer);
        }

        pthread_mutex_unlock(&reader_mutex);
        // ** Section End : Readers ** //
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
            sem_post(&db_reader);
            sem_post(&db_writer);
            break;
        }

        write_database();
        writesDone++;

        sem_post(&db_writer);
        sem_post(&db_reader);
    }
    return NULL;
}

int destroy_all()
{
    if (sem_destroy(&db_writer) != 0) return 0;
    if (sem_destroy(&db_reader) != 0) return 0;
    if (pthread_mutex_destroy(&writer_mutex) != 0) return 0;
    if (pthread_mutex_destroy(&reader_mutex) != 0) return 0;
    return 1;
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

    if (pthread_mutex_init(&general_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        sem_destroy(&db_writer);
        sem_destroy(&db_reader);
        pthread_mutex_destroy(&writer_mutex);
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

    if (destroy_all() == 0)
    {
        perror("destroy_all()");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}