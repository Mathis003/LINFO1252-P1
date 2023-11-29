#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <getopt.h>
#include <sys/time.h>
#include <errno.h>
#include <stdbool.h> 


int my_ts_mutex_init();

int my_ts_mutex_destroy();

int my_ts_mutex_lock();

int my_ts_mutex_unlock();