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

# Compile le programme "%"
$(BIN_DIR)/%.bin: $(C_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# Créer les répértoires nécessaires et lance l'analyse de performances du programme "%"
run_%: $(BIN_DIR)/%.bin
	@mkdir -p $(CSV_DIR)
	@mkdir -p $(GRAPHS_DIR)/png
	@mkdir -p $(GRAPHS_DIR)/pdf
# @bash $(BASH_DIR)/perfs_$*.bash
# @python3 $(PYTHON_DIR)/perfs_graphs.py $(CSV_DIR)/perfs_$*.csv

# Lance l'analyse de performances sur tous les programmes
run: $(addprefix run_, $(PROGRAMS))

# Supprime le répértoire contenant les exécutable .bin
clean:
	@rm -rf $(BIN_DIR)

# Supprime le répértoire contenant les exécutable .bin, les graphiques de performances et les fichiers .csv
clean_all: clean
	@rm -rf $(CSV_DIR) $(GRAPHS_DIR)