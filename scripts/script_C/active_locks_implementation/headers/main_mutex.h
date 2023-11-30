#ifndef MAIN_MUTEX_H
#define MAIN_MUTEX_H

#include <stdlib.h>
#include <pthread.h>

#include "../../mutex/mutex.h"

int NBER_ITER;

void process(void);

void *thread_function(void *arg);

int main(int argc, char *argv[]);

#endif // MAIN_MUTEX_H