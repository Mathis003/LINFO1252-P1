#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

int database = 0;

void read_database() {
    printf("read value: %d\n", database);
}

void write_database() {
    database = database+1;
    printf("wrote value: %d\n", database);
}


pthread_mutex_t readMutex;
sem_t writeSem, queueSem;
int readcount=0; // nombre de readers

void *reader(void *arg)
{
 while(true)
 {
   sem_wait(&queueSem);
   pthread_mutex_lock(&readMutex);
   // critical section
   readcount++;
   if (readcount==1)
   { // first reader arrives
     sem_wait(&writeSem);
   }
   pthread_mutex_unlock(&readMutex);
   sem_post(&queueSem);

   read_database();

   pthread_mutex_lock(&readMutex);
   // critical section
   readcount--;
   if(readcount==0)
   { // last reader leaves
     sem_post(&writeSem);
   }
   pthread_mutex_unlock(&readMutex);
 }
}

void *writer(void *arg)
{
 while(true)
 {
   sem_wait(&queueSem);
   sem_wait(&writeSem);
   // critical section
   write_database();
   sem_post(&writeSem);
   sem_post(&queueSem);
 }
}

#define NUM_THREADS 10

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
    if (error != 0) {
        perror("sem_init()");
        return EXIT_FAILURE;
    }

    pthread_t *writters = malloc(sizeof(pthread_t) * nbWritters);
    pthread_t *readers = malloc(sizeof(pthread_t) * nbReaders);

    if (pthread_mutex_init(&readMutex, NULL) != 0)
    {
        perror("pthread_mutex_init()");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < nbWritters; i++) {
        pthread_create(&writters[i], NULL, writer, NULL);
    }

    for (int i = 0; i < nbReaders; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    for (int i = 0; i < nbWritters; i++) {
        pthread_join(writters[i], NULL);
    }

    for (int i = 0; i < nbReaders; i++) {
        pthread_join(readers[i], NULL);
    }

    free(writters);
    free(readers);
    sem_destroy(&writeSem);
    sem_destroy(&queueSem);
    pthread_mutex_destroy(&readMutex);

    return EXIT_SUCCESS;
}