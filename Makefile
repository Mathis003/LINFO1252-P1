CC=gcc
CFLAGS=-Wall -g -lpthread

all: philosopher producer_consumer

philosopher: dining_philosopher_problem.c
	@$(CC) $(CFLAGS) $< -o philosopher.out

producer_consumer: producer_consumer.c
	@$(CC) $(CFLAGS) $< -o producer_consumer.out

run: philosopher producer_consumer
	./philosopher.out
	./producer_consumer.out

clean:
	@rm -f philosopher.out producer_consumer.out