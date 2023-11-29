#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

#include "../../active_locks_implementation/headers/test_and_set.h"
#include "../../active_locks_implementation/headers/test_and_test_and_set.h"
#include "../../active_locks_implementation/headers/sem.h"

#define NB_READS 2560
#define NB_WRITES 640

pthread_mutex_t writer_mutex, reader_mutex, general_mutex;
sem_t db_writer, db_reader;

int readsDone, writesDone = 0;
int readersCount, writersCount = 0;

void process(void);

void read_database();

void write_database();

void *reader(void *unused);

void *writer(void *unused);

int destroy_sem();

int destroy_all();

int main(int argc, char *argv[]);