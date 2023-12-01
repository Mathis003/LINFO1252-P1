#ifndef MY_SEM_H
#define MY_SEM_H

#ifdef TS_MUTEX
#include "my_mutex_ts.h"
#elif TTS_MUTEX
#include "my_mutex_tts.h"
#elif BTTS_MUTEX
#include "my_mutex_btts.h"
#endif

typedef struct my_sem {
    int value;
    my_mutex_t *mutex;
} my_sem_t;

int my_sem_init(my_sem_t *sem, unsigned int value);

void my_sem_destroy(my_sem_t *sem);

int my_sem_wait(my_sem_t *sem);

int my_sem_post(my_sem_t *sem);

#endif // MY_SEM_H