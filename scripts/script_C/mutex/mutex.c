#include "mutex.h"

int init(void *mutex)
{
    int result;
    #ifdef POSIX
    result = pthread_mutex_init((pthread_mutex_t *) mutex, NULL);
    #else
    result = my_mutex_init((my_mutex_t *) mutex);
    #endif
    return result;
}

int destroy(void *mutex)
{
    int result;
    #ifdef POSIX
    result = pthread_mutex_destroy((pthread_mutex_t *) mutex);
    #else
    result = my_mutex_destroy((my_mutex_t *) mutex);
    #endif
    return result;
}

int lock(void *mutex)
{
    int result;
    #ifdef POSIX
    result = pthread_mutex_lock((pthread_mutex_t *) mutex);
    #else
    result = my_mutex_lock((my_mutex_t *) mutex);
    #endif
    return result;
}

int unlock(void *mutex)
{
    int result;
    #ifdef POSIX
    result = pthread_mutex_unlock((pthread_mutex_t *) mutex);
    #else
    result = my_mutex_unlock((my_mutex_t *) mutex);
    #endif
    return result;
}