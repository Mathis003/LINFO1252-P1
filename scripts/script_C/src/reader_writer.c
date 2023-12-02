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

    init_sem(&db_writer, 0, 1);
    init_sem(&db_reader, 0, 1);
    init_mutex(&writer_mutex);
    init_mutex(&reader_mutex);
    init_mutex(&general_mutex);

    pthread_t writers[nbWriters];
    pthread_t readers[nbReaders];

    for (int i = 0; i < nbWriters; i++) pthread_create(&writers[i], NULL, writer, NULL);
    for (int i = 0; i < nbReaders; i++) pthread_create(&readers[i], NULL, reader, NULL);

    // printf("Waiting for threads to finish...\n");

    for (int i = 0; i < nbWriters; i++) pthread_join(writers[i], NULL);
    for (int i = 0; i < nbReaders; i++) pthread_join(readers[i], NULL);

    // printf("readsdone: %d, writesdone: %d\n", readsDone, writesDone);

    destroy_sem(&db_writer);
    destroy_sem(&db_reader);
    destroy_mutex(&writer_mutex);
    destroy_mutex(&reader_mutex);
    destroy_mutex(&general_mutex);

    return EXIT_SUCCESS;
}