CC=gcc
CFLAGS=-Wall -g -pthread

all: philosopher producer_consumer reader_writer

philosopher: src/dining_philosopher_problem.c
	@$(CC) $(CFLAGS) $< -lpthread -o philosopher.out

producer_consumer: src/producer_consumer.c
	@$(CC) $(CFLAGS) $< -lpthread -o producer_consumer.out

reader_writer: src/reader_writer.c
	@$(CC) $(CFLAGS) $< -lpthread -o reader_writer.out

run: src/get_results.bash src/plot_results.py
	@bash src/get_results.bash
	@python3 src/plot_results.py

clean:
	@rm -f philosopher.out producer_consumer.out