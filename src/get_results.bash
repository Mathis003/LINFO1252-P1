#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <executable_file> <csv_file_name (without .csv extension)> <nber_args>"
    exit 1
fi

if [ ! -x "$1" ]; then
    echo "Error: The first argument must be a valid executable."
    exit 1
fi

if [ -z "$2" ]; then
    echo "Error: The second argument must be a non-empty string (name of the .csv file without .csv extension)."
    exit 1
fi

EXEC_NAME="$1"
CSV_FILE="$2"
NBER_ARGS=$3

NB_TIMES=10
SEQ_NB_THREADS=(2 4 8 16 32 64)
TIMES=()

TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
echo $TITLE_COLUMNS > $CSV_FILE

for i in "${SEQ_NB_THREADS[@]}"; do
    for j in $(seq 1 $NB_TIMES); do
        if [ "$NBER_ARGS" -eq 1 ]; then
            TIME=$(/usr/bin/time -f %e ./$EXEC_NAME $i 2>&1 | tail -n 1)
        else
            TIME=$(/usr/bin/time -f %e ./$EXEC_NAME ${i}/2 ${i}/2 2>&1 | tail -n 1)
        fi
        TIMES[${j}-1]=$TIME
    done
    TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
    echo $TIMES_LINE >> $CSV_FILE
done