#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#include "user_defined_sync.h"

int NB_PHILOSOPHERS;

typedef struct args_philosopher
{
    int id;
    void *left_baguette;
    void *right_baguette;
} args_philosopher_t;

void *create_arg_philosopher(int id, void *left_baguette, void *right_baguette);

void philosopher_eating(int id, bool rightGreater, void *left_baguette, void *right_baguette);

void philosopher_thinking(int id);

void *philosopher_function(void* arg);

int main(int argc, char *argv[]);

#endif // PHILOSOPHER_H