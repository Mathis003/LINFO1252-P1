#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#include "../../active_locks_implementation/headers/test_and_set.h"
#include "../../active_locks_implementation/headers/test_and_test_and_set.h"

typedef struct args_philosopher
{
    int id;
    bool rightGreater;
    pthread_mutex_t *left_baguette;
    pthread_mutex_t *right_baguette;
} args_philosopher_t;

void *create_arg_philosopher(int id, bool rightGreater, pthread_mutex_t *left_baguette, pthread_mutex_t *right_baguette);

void philosopher_eating(int id, bool rightGreater, pthread_mutex_t *left_baguette, pthread_mutex_t *right_baguette);

void philosopher_thinking(int id);

void *philosopher_function(void* arg);

int main(int argc, char *argv[]);