#ifndef MUTEX_H
#define MUTEX_H

#ifdef POSIX
#include <stddef.h>
#include <semaphore.h>
#else
#include "my_mutex.h"
#include "my_sem.h"
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