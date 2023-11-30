#ifndef MAIN_MUTEX_H
#define MAIN_MUTEX_H

#include <stdlib.h>
#include <pthread.h>

#ifdef TS_MUTEX_H
    #include "../headers/test_and_set.h"
    #define init_mutex my_mutex_ts_init
    #define destroy_mutex my_mutex_ts_destroy
    #define lock_mutex my_mutex_ts_lock
    #define unlock_mutex my_mutex_ts_unlock
#elif TTS_MUTEX_H
    #include "../headers/test_and_test_and_set.h"
    #define init_mutex my_mutex_tts_init
    #define destroy_mutex my_mutex_tts_destroy
    #define lock_mutex my_mutex_tts_lock
    #define unlock_mutex my_mutex_tts_unlock
#else
    #define init_mutex pthread_mutex_init
    #define destroy_mutex pthread_mutex_destroy
    #define lock_mutex pthread_mutex_lock
    #define unlock_mutex pthread_mutex_unlock
#endif

int NBER_ITER;

int init_mutex();
int destroy_mutex();
int lock_mutex();
int unlock_mutex();

void process(void);

void *thread_function(void *arg);

int main(int argc, char *argv[]);

#endif // MAIN_MUTEX_H