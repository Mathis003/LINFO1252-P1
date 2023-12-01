#ifndef MUTEX_H
#define MUTEX_H

#ifdef TS_MUTEX
#include "my_mutex_ts.h"
#include "my_sem.h"
#elif TTS_MUTEX
#include "my_mutex_tts.h"
#include "my_sem.h"
#elif BTTS_MUTEX
#include "my_mutex_btts.h"
#include "my_sem.h"
#else
#include <stddef.h>
#include <semaphore.h>
#endif

int init_mutex(void *mutex);

int destroy_mutex(void *mutex);

int lock_mutex(void *mutex);

int unlock_mutex(void *mutex);

int init_sem(void *sem, int pshared, unsigned int value);

int wait_sem(void *sem);

int post_sem(void *sem);

int destroy_sem(void *sem);

#endif // MUTEX_H