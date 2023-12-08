CC=gcc
CFLAGS=-g -pthread
LDFLAGS=-lpthread

SRC_DIR=scripts
BASH_DIR=$(SRC_DIR)/script_bash
PYTHON_DIR=$(SRC_DIR)/script_python
C_DIR=$(SRC_DIR)/script_C/src
CSV_DIR=csv_files
GRAPHS_DIR=graphs
BIN_DIR=bin

DEPENDENCIES_PROGRAMS_POSIX_NAME=user_defined_sync
DEPENDENCIES_PROGRAMS_POSIX=$(addsuffix .c, $(addprefix $(C_DIR)/, $(DEPENDENCIES_PROGRAMS_POSIX_NAME)))

DEPENDENCIES_PROGRAMS_NAME=my_mutex my_sem user_defined_sync
DEPENDENCIES_PROGRAMS=$(addsuffix .c, $(addprefix $(C_DIR)/, $(DEPENDENCIES_PROGRAMS_NAME)))

NB_THREADS?=1
HALF_THREADS=$(shell echo $$(( $(NB_THREADS) / 2 )))

.PRECIOUS: $(BIN_DIR)/%.bin

make: build
	

### Build : BEGIN ###

build: build_philosopher build_reader_writer build_producer_consumer


build_philosopher: build_philosopher_POSIX build_philosopher_TS build_philosopher_TTS build_philosopher_BTTS

build_philosopher_POSIX: $(DEPENDENCIES_PROGRAMS_POSIX) $(C_DIR)/philosopher.c | $(BIN_DIR)
	@$(CC) -D POSIX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/philosopher_POSIX.bin $^

build_philosopher_TS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/philosopher.c | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/philosopher_TS.bin $^

build_philosopher_TTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/philosopher.c | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/philosopher_TTS.bin $^

build_philosopher_BTTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/philosopher.c | $(BIN_DIR)
	@$(CC) -D BTTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/philosopher_BTTS.bin $^


build_reader_writer: build_reader_writer_POSIX build_reader_writer_TS build_reader_writer_TTS build_reader_writer_BTTS

build_reader_writer_POSIX: $(DEPENDENCIES_PROGRAMS_POSIX) $(C_DIR)/reader_writer.c | $(BIN_DIR)
	@$(CC) -D POSIX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/reader_writer_POSIX.bin $^

build_reader_writer_TS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/reader_writer.c | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/reader_writer_TS.bin $^

build_reader_writer_TTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/reader_writer.c | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/reader_writer_TTS.bin $^

build_reader_writer_BTTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/reader_writer.c | $(BIN_DIR)
	@$(CC) -D BTTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/reader_writer_BTTS.bin $^


build_producer_consumer: build_producer_consumer_POSIX build_producer_consumer_TS build_producer_consumer_TTS build_producer_consumer_BTTS

build_producer_consumer_POSIX: $(DEPENDENCIES_PROGRAMS_POSIX) $(C_DIR)/producer_consumer.c | $(BIN_DIR)
	@$(CC) -D POSIX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/producer_consumer_POSIX.bin $^

build_producer_consumer_TS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/producer_consumer.c | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/producer_consumer_TS.bin $^

build_producer_consumer_TTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/producer_consumer.c | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/producer_consumer_TTS.bin $^

build_producer_consumer_BTTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/producer_consumer.c | $(BIN_DIR)
	@$(CC) -D BTTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/producer_consumer_BTTS.bin $^


build_main_my_mutex: build_main_my_mutex_TS build_main_my_mutex_TTS build_main_my_mutex_BTTS

build_main_my_mutex_TS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/main_my_mutex.c | $(BIN_DIR)
	@$(CC) -D TS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main_my_mutex_TS.bin $^

build_main_my_mutex_TTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/main_my_mutex.c | $(BIN_DIR)
	@$(CC) -D TTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main_my_mutex_TTS.bin $^

build_main_my_mutex_BTTS: $(DEPENDENCIES_PROGRAMS) $(C_DIR)/main_my_mutex.c | $(BIN_DIR)
	@$(CC) -D BTTS_MUTEX $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main_my_mutex_BTTS.bin $^

### Build : END ###


### Run : BEGIN ###

run_all: run_philosopher run_producer_consumer run_reader_writer

run_philosopher: run_philosopher_POSIX run_philosopher_TS run_philosopher_TTS run_philosopher_BTTS

run_producer_consumer: run_producer_consumer_POSIX run_producer_consumer_TS run_producer_consumer_TTS run_producer_consumer_BTTS

run_reader_writer: run_reader_writer_POSIX run_reader_writer_TS run_reader_writer_TTS run_reader_writer_BTTS

run_philosopher_POSIX: build_philosopher_POSIX
	@./$(BIN_DIR)/philosopher_POSIX.bin $(NB_THREADS)

run_philosopher_TS: build_philosopher_TS
	@./$(BIN_DIR)/philosopher_TS.bin $(NB_THREADS)

run_philosopher_TTS: build_philosopher_TTS
	@./$(BIN_DIR)/philosopher_TTS.bin $(NB_THREADS)

run_philosopher_BTTS: build_philosopher_BTTS
	@./$(BIN_DIR)/philosopher_BTTS.bin $(NB_THREADS)

run_producer_consumer_POSIX: build_producer_consumer_POSIX
	@./$(BIN_DIR)/producer_consumer_POSIX.bin $(HALF_THREADS) $(HALF_THREADS)

run_producer_consumer_TS: build_producer_consumer_TS
	@./$(BIN_DIR)/producer_consumer_TS.bin $(HALF_THREADS) $(HALF_THREADS)

run_producer_consumer_TTS: build_producer_consumer_TTS
	@./$(BIN_DIR)/producer_consumer_TTS.bin $(HALF_THREADS) $(HALF_THREADS)

run_producer_consumer_BTTS: build_producer_consumer_BTTS
	@./$(BIN_DIR)/producer_consumer_BTTS.bin $(HALF_THREADS) $(HALF_THREADS)

run_reader_writer_POSIX: build_reader_writer_POSIX
	@./$(BIN_DIR)/reader_writer_POSIX.bin $(HALF_THREADS) $(HALF_THREADS)

run_reader_writer_TS: build_reader_writer_TS
	@./$(BIN_DIR)/reader_writer_TS.bin $(HALF_THREADS) $(HALF_THREADS)

run_reader_writer_TTS: build_reader_writer_TTS
	@./$(BIN_DIR)/reader_writer_TTS.bin $(HALF_THREADS) $(HALF_THREADS)

run_reader_writer_BTTS: build_reader_writer_BTTS
	@./$(BIN_DIR)/reader_writer_BTTS.bin $(HALF_THREADS) $(HALF_THREADS)

run_main_my_mutex_TS: build_main_my_mutex_TS
	@./$(BIN_DIR)/main_my_mutex_TS.bin $(NB_THREADS)

run_main_my_mutex_TTS: build_main_my_mutex_TTS
	@./$(BIN_DIR)/main_my_mutex_TTS.bin $(NB_THREADS)

run_main_my_mutex_BTTS: build_main_my_mutex_BTTS
	@./$(BIN_DIR)/main_my_mutex_BTTS.bin $(NB_THREADS)

### Run : END ###

### CSV : BEGIN ###

csv: csv_reader_writer csv_main_my_mutex csv_producer_consumer csv_philosopher

one_arg_%:
	@bash $(BASH_DIR)/perfs_one_arg.sh $(BIN_DIR)/$*.bin $(CSV_DIR)/perfs_$*.csv

two_args_%:
	@bash $(BASH_DIR)/perfs_two_args.sh $(BIN_DIR)/$*.bin $(CSV_DIR)/perfs_$*.csv

csv_philosopher: csv_philosopher_POSIX csv_philosopher_TS csv_philosopher_TTS csv_philosopher_BTTS
csv_philosopher_POSIX: build_philosopher_POSIX one_arg_philosopher_POSIX
csv_philosopher_TS: build_philosopher_TS one_arg_philosopher_TS
csv_philosopher_TTS: build_philosopher_TTS one_arg_philosopher_TTS
csv_philosopher_BTTS: build_philosopher_BTTS one_arg_philosopher_BTTS

csv_reader_writer: csv_reader_writer_POSIX csv_reader_writer_TS csv_reader_writer_TTS csv_reader_writer_BTTS
csv_reader_writer_POSIX: build_reader_writer_POSIX two_args_reader_writer_POSIX
csv_reader_writer_TS: build_reader_writer_TS two_args_reader_writer_TS
csv_reader_writer_TTS: build_reader_writer_TTS two_args_reader_writer_TTS
csv_reader_writer_BTTS: build_reader_writer_BTTS two_args_reader_writer_BTTS

csv_producer_consumer: csv_producer_consumer_POSIX csv_producer_consumer_TS csv_producer_consumer_TTS csv_producer_consumer_BTTS
csv_producer_consumer_POSIX: build_producer_consumer_POSIX two_args_producer_consumer_POSIX
csv_producer_consumer_TS: build_producer_consumer_TS two_args_producer_consumer_TS
csv_producer_consumer_TTS: build_producer_consumer_TTS two_args_producer_consumer_TTS
csv_producer_consumer_BTTS: build_producer_consumer_BTTS two_args_producer_consumer_BTTS

csv_main_my_mutex: csv_main_my_mutex_TS csv_main_my_mutex_TTS csv_main_my_mutex_BTTS
csv_main_my_mutex_TS: build_main_my_mutex_TS one_arg_main_my_mutex_TS
csv_main_my_mutex_TTS: build_main_my_mutex_TTS one_arg_main_my_mutex_TTS
csv_main_my_mutex_BTTS: build_main_my_mutex_BTTS one_arg_main_my_mutex_BTTS

### CSV : END ###

### PLOT : BEGIN ###

plot: plot_main_my_mutex plot_philosopher plot_reader_writer plot_producer_consumer

plot_main_my_mutex: | $(GRAPHS_DIR)
	@python3 $(PYTHON_DIR)/perfs_graph_mutex.py

plot_%: | $(GRAPHS_DIR)
	@python3 $(PYTHON_DIR)/perfs_graphs.py $*

### PLOT : END ###

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(GRAPHS_DIR):
	@mkdir -p $(GRAPHS_DIR)

### Clean : BEGIN ###

clean:
	@rm -rf $(BIN_DIR)

clean_all: clean
	rm -rf $(GRAPHS_DIR)
	rm -rf $(CSV_DIR)

### Clean : END ###