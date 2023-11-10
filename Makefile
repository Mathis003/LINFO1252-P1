CC=gcc
CFLAGS=-Wall -g -lpthread
NB_THREADS=4
TARGET=main.out

ifdef THREADS
    NB_THREADS = $(THREADS)
else
    NB_THREADS = 1
endif

all: $(TARGET)

$(TARGET): dining_philosopher_problem.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	${NB_THREADS} ./$(TARGET)

clean:
	rm -f $(TARGET)