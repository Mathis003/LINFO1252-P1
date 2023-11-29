#include <stdlib.h>
#include <pthread.h>

int NBER_ITER;

void process(void);

void *thread_function(void *arg);

int main(int argc, char *argv[]);