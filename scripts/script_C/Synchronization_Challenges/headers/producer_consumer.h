#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>

#include "../../active_locks_implementation/headers/test_and_set.h"
#include "../../active_locks_implementation/headers/test_and_test_and_set.h"
#include "../../active_locks_implementation/headers/sem.h"

#define NB_PRODUCTIONS 8192
#define CAPACITY_BUFFER 8

int buffer[CAPACITY_BUFFER];
int nbProductionsDone, nbConsumeDone = 0;
pthread_mutex_t mutex;
sem_t empty, full;
int idx_buffer = 0;

void process(void);

int produce(void);

void insert_item(int item);

void *producer(void *unused);

int remove_item();

void *consumer(void *unused);

void destroy_all(void);

int main(int argc, char *argv[]);

#endif // PRODUCER_CONSUMER_H