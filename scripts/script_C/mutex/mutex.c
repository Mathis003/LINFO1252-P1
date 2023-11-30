#include "mutex.h"

int init(void *mutex)
{
    int result;
    #ifdef POSIX
    pthread_mutex_t *POSIX_mutex = (pthread_mutex_t *) mutex;
    result = pthread_mutex_init(POSIX_mutex, NULL);
    #else
    my_mutex_t *my_mutex = (my_mutex_t *) mutex;
    result = my_mutex_init(my_mutex);
    #endif
    return result;
}

int destroy(void *mutex)
{
    int result;
    #ifdef POSIX
    pthread_mutex_t *POSIX_mutex = (pthread_mutex_t *) mutex;
    result = pthread_mutex_destroy(POSIX_mutex);
    #else
    my_mutex_t *my_mutex = (my_mutex_t *) mutex;
    result = my_mutex_destroy(my_mutex);
    #endif
    return result;
}

int lock(void *mutex)
{
    int result;
    #ifdef POSIX
    pthread_mutex_t *POSIX_mutex = (pthread_mutex_t *) mutex;
    result = pthread_mutex_lock(POSIX_mutex);
    #else
    my_mutex_t *my_mutex = (my_mutex_t *) mutex;
    result = my_mutex_lock(my_mutex);
    #endif
    return result;
}

int unlock(void *mutex)
{
    int result;
    #ifdef POSIX
    pthread_mutex_t *POSIX_mutex = (pthread_mutex_t *) mutex;
    result = pthread_mutex_unlock(POSIX_mutex);
    #else
    my_mutex_t *my_mutex = (my_mutex_t *) mutex;
    result = my_mutex_unlock(my_mutex);
    #endif
    return result;
}