#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <executable> [csv_file]"
    exit 1
fi

EXEC="$1"

CSV_FILE="${2:-perfssss.csv}"

if [ ! -x "$EXEC" ]; then
    echo "The executable $EXEC does not exist or is not executable."
    exit 1
fi

### Begin Variable ###
NB_TIMES=10
SEQ_NB_THREADS=(2 3 4 5 6 7 8)
### End Variable ###

TIMES=()
TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
echo $TITLE_COLUMNS > $CSV_FILE

make -s clean
make -s

for i in "${SEQ_NB_THREADS[@]}";
do
    for j in $(seq 1 $NB_TIMES)
    do
        TIME=$(/usr/bin/time -f %e ./$EXEC $i 2>&1 | tail -n 1)
        TIMES[${j}-1]=$TIME
    done
    TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
    echo $TIMES_LINE >> $CSV_FILE
done