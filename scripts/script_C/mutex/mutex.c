#include "mutex.h"

int init(void *mutex)
{
    #ifdef POSIX
    printf("Perfect.\n");
    int err = pthread_mutex_init((pthread_mutex_t *) mutex, NULL);
    #else
    printf("Bad.\n");
    err = my_mutex_init((my_mutex_t *) mutex);
    #endif
    return err;
}

int destroy(void *mutex)
{
    #ifdef POSIX
    int err = pthread_mutex_destroy((pthread_mutex_t *) mutex);
    #else
    err = my_mutex_destroy((my_mutex_t *) mutex);
    #endif
    return err;
}

int lock(void *mutex)
{
    #ifdef POSIX
    int err = pthread_mutex_lock((pthread_mutex_t *) mutex);
    #else
    err = my_mutex_lock((my_mutex_t *) mutex);
    #endif
    return err;
}

int unlock(void *mutex)
{
    #ifdef POSIX
    int err = pthread_mutex_unlock((pthread_mutex_t *) mutex);
    #else
    err = my_mutex_unlock((my_mutex_t *) mutex);
    #endif
    return err;
}