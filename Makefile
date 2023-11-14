CC=gcc
CFLAGS=-Wall -g -pthread
LDFLAGS=-lpthread
SRC_DIR=src
CSV_DIR=csv_files
GRAPHS_DIR=graphs

PROGRAMS=philosopher producer_consumer reader_writer
RESULTS_CSV=perfs_philosopher perfs_producer_consumer perfs_reader_writer

.PRECIOUS: %.out

all: $(PROGRAMS)

%.out: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

run_%: %.out
	@mkdir -p $(CSV_DIR)
	@mkdir -p $(GRAPHS_DIR)/png
	@mkdir -p $(GRAPHS_DIR)/pdf
	@bash $(SRC_DIR)/get_results.bash $< "$(CSV_DIR)/perfs_$*.csv" $(if $(filter philosopher,$*),1,2)
	@python3 $(SRC_DIR)/plot_results.py "$(CSV_DIR)/perfs_$*.csv"

run: $(addprefix run_, $(PROGRAMS))

clean:
	@rm -f *.out

clean_all: clean
	@rm -rf $(CSV_DIR) $(GRAPHS_DIR)