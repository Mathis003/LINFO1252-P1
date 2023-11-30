#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "../../mutex/mutex.h"

#define NB_PRODUCTIONS 8192
#define CAPACITY_BUFFER 8

int buffer[CAPACITY_BUFFER];
int nbProductionsDone, nbConsumeDone = 0;
sem_t empty, full;
int idx_buffer = 0;

#ifdef POSIX
pthread_mutex_t mutex;
#else
my_mutex_t mutex;
#endif

void process(void);

int produce(void);

void insert_item(int item);

void *producer(void *unused);

int remove_item();

void *consumer(void *unused);

void destroy_all(void);

int main(int argc, char *argv[]);

#endif // PRODUCER_CONSUMER_H