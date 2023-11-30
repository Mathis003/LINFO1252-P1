#include "../headers/reader_writer.h"

void process(void)
{
    for (int i = 0; i < 10000; i++);
}

void read_database()
{
    process();
    // printf("Reading...\n");
    // printf("readsDone: %d, writesDone: %d\n", readsDone, writesDone);
}

void write_database()
{
    process();
    // printf("Writing...\n");
    // printf("readsDone: %d, writesDone: %d\n", readsDone, writesDone);
}

void *reader(void *unused)
{
    while (1)
    {
        lock(&general_mutex);

        sem_wait(&db_reader);

        lock(&reader_mutex);

        if (readsDone == NB_READS)
        {
            unlock(&general_mutex);
            sem_post(&db_reader);
            unlock(&reader_mutex);
            break;
        }
        
        readsDone++;
        
        readersCount++;
        if (readersCount == 1)
        {
            sem_wait(&db_writer);
        }
        
        unlock(&reader_mutex);

        sem_post(&db_reader);

        unlock(&general_mutex);

        read_database();

        lock(&reader_mutex);

        readersCount--;
        if (readersCount == 0)
        {
            sem_post(&db_writer);
        }

        unlock(&reader_mutex);
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
    if (destroy(&writer_mutex) != 0) value = 0;
    if (destroy(&reader_mutex) != 0) value = 0;
    if (destroy(&general_mutex) != 0) value = 0;
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


    if (init(&writer_mutex) != 0)
    {
        perror("init()");
        destroy_sem();
        return EXIT_FAILURE;
    }

    if (init(&reader_mutex) != 0)
    {
        perror("init()");
        destroy(&writer_mutex);
        destroy_sem();
        return EXIT_FAILURE;
    }

    if (init(&general_mutex) != 0)
    {
        perror("init()");
        destroy_sem();
        destroy(&writer_mutex);
        destroy(&reader_mutex);
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