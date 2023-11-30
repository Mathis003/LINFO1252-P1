#include "mutex.h"

int init_mutex(void *mutex)
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

int destroy_mutex(void *mutex)
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

int lock_mutex(void *mutex)
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

int unlock_mutex(void *mutex)
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

int init_sem(void *sem, int pshared, unsigned int value)
{
    int result;
    #ifdef POSIX
    sem_t *POSIX_sem = (sem_t *) ;
    result = sem_init(POSIX_sem, pshared, value);
    #else
    my_sem_t *my_sem = (my_sem_t *) sem;
    result = my_sem_init(my_sem, pshared, value);
    #endif
    return result;
}

int wait_sem(void *sem)
{
    int result;
    #ifdef POSIX
    sem_t *POSIX_sem = (sem_t *) ;
    result = sem_wait(POSIX_sem);
    #else
    my_sem_t *my_sem = (my_sem_t *) sem;
    result = my_sem_wait(my_sem);
    #endif
    return result;
}

int post_sem(void *sem)
{
    int result;
    #ifdef POSIX
    sem_t *POSIX_sem = (sem_t *) ;
    result = sem_post(POSIX_sem);
    #else
    my_sem_t *my_sem = (my_sem_t *) sem;
    result = my_sem_post(my_sem);
    #endif
    return result;
}

int destroy_sem(void *sem)
{
    int result;
    #ifdef POSIX
    sem_t *POSIX_sem = (sem_t *) ;
    result = sem_destroy(POSIX_sem);
    #else
    my_sem_t *my_sem = (my_sem_t *) sem;
    result = my_sem_destroy(my_sem);
    #endif
    return result;
}