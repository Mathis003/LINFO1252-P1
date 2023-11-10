#!/bin/bash

NB_TIMES=10
SEQ_NB_THREADS=(2 4 8 16 32 64)
TIMES=()

make -s clean
make -s

CSV_FILE="csv_files/perfs_producer_consumer.csv"
TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
echo $TITLE_COLUMNS > $CSV_FILE

for i in "${SEQ_NB_THREADS[@]}";
do
    for j in $(seq 1 $NB_TIMES)
    do
        TIME=$(/usr/bin/time -f %e ./producer_consumer.out ${i}/2 ${i}/2 2>&1 | tail -n 1)
        TIMES[${j}-1]=$TIME
    done
    TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
    echo $TIMES_LINE >> $CSV_FILE
done


CSV_FILE="csv_files/perfs_philosopher.csv"
TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
echo $TITLE_COLUMNS > $CSV_FILE

for i in "${SEQ_NB_THREADS[@]}";
do
    for j in $(seq 1 $NB_TIMES)
    do
        TIME=$(/usr/bin/time -f %e ./philosopher.out $i 2>&1 | tail -n 1)
        TIMES[${j}-1]=$TIME
    done
    TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
    echo $TIMES_LINE >> $CSV_FILE
done

make -s clean