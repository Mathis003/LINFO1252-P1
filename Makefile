CC=gcc
CFLAGS=-g -pthread
LDFLAGS=-lpthread

SRC_DIR=scripts
BASH_DIR=$(SRC_DIR)/script_bash
PYTHON_DIR=$(SRC_DIR)/script_python
C_DIR=$(SRC_DIR)/script_C/src
CHALLENGES_DIR=$(C_DIR)/Synchronization_Challenges/src
CSV_DIR=csv_files
GRAPHS_DIR=graphs
BIN_DIR=bin

DEPENDENCIES_PROGRAMS_POSIX_NAME=mutex
DEPENDENCIES_PROGRAMS_POSIX=$(addsuffix .c, $(addprefix $(C_DIR)/, $(DEPENDENCIES_PROGRAMS_POSIX_NAME)))

DEPENDENCIES_PROGRAMS_TS_NAME=my_mutex_ts my_sem mutex
DEPENDENCIES_PROGRAMS_TS=$(addsuffix .c, $(addprefix $(C_DIR)/, $(DEPENDENCIES_PROGRAMS_TS_NAME)))

DEPENDENCIES_PROGRAMS_TTS_NAME=my_mutex_tts my_sem mutex
DEPENDENCIES_PROGRAMS_TTS=$(addsuffix .c, $(addprefix $(C_DIR)/, $(DEPENDENCIES_PROGRAMS_TTS_NAME)))

NB_THREADS?=1

.PRECIOUS: $(BIN_DIR)/%.bin
.PHONY: all build build_% run clean clean_all run csv


all: run csv plot

build: build_philosopher build_reader_writer build_producer_consumer clean_libraries


build_philosopher: build_philosopher_POSIX build_philosopher_TS build_philosopher_TTS

build_philosopher_POSIX: $(C_DIR)/philosopher.c $(DEPENDENCIES_PROGRAMS_POSIX) | $(BIN_DIR)
	@$(CC) -D POSIX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/philosopher_POSIX.bin $^

build_philosopher_TS: $(C_DIR)/philosopher.c $(DEPENDENCIES_PROGRAMS_TS) | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/philosopher_TS.bin $^

build_philosopher_TTS: $(C_DIR)/philosopher.c $(DEPENDENCIES_PROGRAMS_TTS) | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/philosopher_TTS.bin $^


build_reader_writer: build_reader_writer_POSIX build_reader_writer_TS build_reader_writer_TTS

build_reader_writer_POSIX: $(C_DIR)/reader_writer.c $(DEPENDENCIES_PROGRAMS_POSIX) | $(BIN_DIR)
	@$(CC) -D POSIX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/reader_writer_POSIX.bin $^

build_reader_writer_TS: $(C_DIR)/reader_writer.c $(DEPENDENCIES_PROGRAMS_TS) | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/reader_writer_TS.bin $^

build_reader_writer_TTS: $(C_DIR)/reader_writer.c $(DEPENDENCIES_PROGRAMS_TTS) | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/reader_writer_TTS.bin $^


build_producer_consumer: build_producer_consumer_POSIX build_producer_consumer_TS build_producer_consumer_TTS

build_producer_consumer_POSIX: $(C_DIR)/producer_consumer.c $(DEPENDENCIES_PROGRAMS_POSIX) | $(BIN_DIR)
	@$(CC) -D POSIX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/producer_consumer_POSIX.bin $^

build_producer_consumer_TS: $(C_DIR)/producer_consumer.c $(DEPENDENCIES_PROGRAMS_TS) | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/producer_consumer_TS.bin $^

build_producer_consumer_TTS: $(C_DIR)/producer_consumer.c $(DEPENDENCIES_PROGRAMS_TTS) | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/producer_consumer_TTS.bin $^


build_main_my_mutex: build_main_my_mutex_TS build_main_my_mutex_TTS

build_main_my_mutex_TS: $(C_DIR)/main_my_mutex.c $(DEPENDENCIES_PROGRAMS_TS) | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main_my_mutex_TS.bin $^

build_main_my_mutex_TTS: $(C_DIR)/main_my_mutex.c $(DEPENDENCIES_PROGRAMS_TTS) | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main_my_mutex_TTS.bin $^




run_philosopher_POSIX:
	./$(BIN_DIR)/philosopher_POSIX.bin $(NB_THREADS)

run_philosopher_TS:
	./$(BIN_DIR)/philosopher_TS.bin $(NB_THREADS)

run_philosopher_TTS:
	./$(BIN_DIR)/philosopher_TTS.bin $(NB_THREADS)

run_producer_consumer_POSIX:
	./$(BIN_DIR)/producer_consumer_POSIX.bin $(NB_THREADS)/2 $(NB_THREADS)/2

run_producer_consumer_TS:
	./$(BIN_DIR)/producer_consumer_TS.bin $(NB_THREADS)/2 $(NB_THREADS)/2

run_producer_consumer_TTS:
	./$(BIN_DIR)/producer_consumer_TTS.bin $(NB_THREADS)/2 $(NB_THREADS)/2

run_reader_writer_POSIX:
	./$(BIN_DIR)/reader_writer_POSIX.bin $(NB_THREADS)/2 $(NB_THREADS)/2

run_reader_writer_TS:
	./$(BIN_DIR)/reader_writer_TS.bin $(NB_THREADS)/2 $(NB_THREADS)/2

run_reader_writer_TTS:
	./$(BIN_DIR)/reader_writer_TTS.bin $(NB_THREADS)/2 $(NB_THREADS)/2

run_main_my_mutex_TS:
	./$(BIN_DIR)/main_my_mutex_TS.bin $(NB_THREADS)

run_main_my_mutex_TTS:
	./$(BIN_DIR)/main_my_mutex_TTS.bin $(NB_THREADS)



clean_all:
	@$(clean)
	rm -rf $(GRAPHS_DIR)
	rm -rf $(CSV_DIR)

clean:
	@$(clean_libraries)
	@$(clean_programs)
	@rm -rf $(BIN_DIR)

clean_programs:
	rm -f $(PROGRAMS)

clean_libraries:
	rm -f $(LIBRARIES_PROGRAMS)




csv: $(addprefix csv_, $(PROGRAMS))

make_csv_%:
	@bash $(BASH_DIR)/perfs_$*.sh

csv_philosopher: csv_philosopher_POSIX csv_philosopher_TS csv_philosopher_TTS

csv_philosopher_POSIX:
	$(make_csv_philosopher_POSIX)

csv_philosopher_TS:
	$(make_csv_philosopher_TS)

csv_philosopher_TTS:
	$(make_csv_philosopher_TTS)


csv_reader_writer: csv_reader_writer_POSIX csv_reader_writer_TS csv_reader_writer_TTS

csv_reader_writer_POSIX:
	$(make_csv_reader_writer_POSIX)

csv_reader_writer_TS:
	$(make_csv_reader_writer_TS)

csv_reader_writer_TTS:
	$(make_csv_reader_writer_TTS)


csv_producer_consumer: csv_producer_consumer_POSIX csv_producer_consumer_TS csv_producer_consumer_TTS

csv_producer_consumer_POSIX:
	$(make_csv_producer_consumer_POSIX)

csv_producer_consumer_TS:
	$(make_csv_producer_consumer_TS)

csv_producer_consumer_TTS:
	$(make_csv_producer_consumer_TTS)


csv_main_my_mutex: csv_main_my_mutex_TS csv_main_my_mutex_TTS

csv_main_my_mutex_TS:
	$(make_csv_main_my_mutex_TS)

csv_main_my_mutex_TTS:
	$(make_csv_main_my_mutex_TTS)




plot: $(addprefix plot_, $(PROGRAMS))
plot_%:
	@mkdir -p $(GRAPHS_DIR)
	@python3 $(PYTHON_DIR)/perfs_graphs.py $(CSV_DIR)/perfs_$*.csv

$(BIN_DIR):
	mkdir -p $(BIN_DIR)