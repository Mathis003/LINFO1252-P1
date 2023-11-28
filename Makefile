CC=gcc
CFLAGS=-Wall -g -pthread
LDFLAGS=-lpthread

SRC_DIR=src
BASH_DIR=$(SRC_DIR)/script_bash
PYTHON_DIR=$(SRC_DIR)/script_python
C_DIR=$(SRC_DIR)/script_C
CSV_DIR=csv_files
GRAPHS_DIR=graphs
BIN_DIR=bin

PROGRAMS=producer_consumer philosopher reader_writer

.PRECIOUS: $(BIN_DIR)/%.bin

all: run csv plot

run: $(addprefix run_, $(PROGRAMS))
run_%:
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(C_DIR)/$*.c $(LDFLAGS) -o $(BIN_DIR)/$*.bin

csv: $(addprefix csv_, $(PROGRAMS))
csv_%:
	@mkdir -p $(CSV_DIR)
	@bash $(BASH_DIR)/perfs_$*.bash

plot: $(addprefix plot_, $(PROGRAMS))
plot_%:
	@mkdir -p $(GRAPHS_DIR)
	@python3 $(PYTHON_DIR)/perfs_graphs.py $(CSV_DIR)/perfs_$*.csv

clean:
	@rm -rf $(BIN_DIR)
clean_all: clean
	@rm -rf $(CSV_DIR) $(GRAPHS_DIR)