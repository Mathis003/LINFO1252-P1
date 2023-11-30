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
        lock_mutex(&general_mutex);

        wait_sem(&db_reader);

        lock_mutex(&reader_mutex);

        if (readsDone == NB_READS)
        {
            unlock_mutex(&general_mutex);
            post_sem(&db_reader);
            unlock_mutex(&reader_mutex);
            break;
        }
        
        readsDone++;
        
        readersCount++;
        if (readersCount == 1)
        {
            wait_sem(&db_writer);
        }
        
        unlock_mutex(&reader_mutex);

        post_sem(&db_reader);

        unlock_mutex(&general_mutex);

        read_database();

        lock_mutex(&reader_mutex);

        readersCount--;
        if (readersCount == 0)
        {
            post_sem(&db_writer);
        }

        unlock_mutex(&reader_mutex);
    }
    return NULL;
}

void *writer(void *unused)
{
    while (1)
    {
        wait_sem(&db_reader);
        wait_sem(&db_writer);

        if (writesDone == NB_WRITES)
        {
            post_sem(&db_writer);
            post_sem(&db_reader);
            break;
        }

        write_database();
        writesDone++;

        post_sem(&db_writer);
        post_sem(&db_reader);
    }
    return NULL;
}

int destroy_sems()
{
    int value = 1;
    if (destroy_sem(&db_writer) != 0) value = 0;
    if (destroy_sem(&db_reader) != 0) value = 0;
    return value;
}

int destroy_all()
{
    int value = destroy_sems();
    if (destroy_mutex(&writer_mutex) != 0) value = 0;
    if (destroy_mutex(&reader_mutex) != 0) value = 0;
    if (destroy_mutex(&general_mutex) != 0) value = 0;
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
    error += init_sem(&db_writer, 0, 1);
    error += init_sem(&db_reader, 0, 1);
    if (error != 0)
    {
        perror("init_sem()");
        destroy_sems();
        return EXIT_FAILURE;
    }


    if (init_mutex(&writer_mutex) != 0)
    {
        perror("init_mutex()");
        destroy_sems();
        return EXIT_FAILURE;
    }

    if (init_mutex(&reader_mutex) != 0)
    {
        perror("init_mutex()");
        destroy_mutex(&writer_mutex);
        destroy_sems();
        return EXIT_FAILURE;
    }

    if (init_mutex(&general_mutex) != 0)
    {
        perror("init_mutex()");
        destroy_sems();
        destroy_mutex(&writer_mutex);
        destroy_mutex(&reader_mutex);
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