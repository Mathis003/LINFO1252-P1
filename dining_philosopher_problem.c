#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int dining_philosophe(int nbThreads)
{
    return 0;
}

int main(int argc, char *argv[])
{
    int nbThreads = atoi(argv[1]);
    printf("nbThreads: %d\n", nbThreads);
    if (nbThreads <= 0) return 1;
    return dining_philosophe(nbThreads);
}