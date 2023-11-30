#ifndef MUTEX_H
#define MUTEX_H

#ifdef TS_MUTEX
#include "../active_locks_implementation/headers/my_mutex_ts.h"
#elif TTS_MUTEX
#include "../active_locks_implementation/headers/my_mutex_tts.h"
#else
#include <semaphore.h>
#endif

int init(void *mutex);

int destroy(void *mutex);

int lock(void *mutex);

int unlock(void *mutex);

#endif // MUTEX_H