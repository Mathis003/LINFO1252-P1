EXEC_NAME="bin/reader_writer.bin"
CSV_FILE="csv_files/perfs_reader_writer.csv"

NB_TIMES=5
SEQ_NB_THREADS=(2 4 8 16 32 64)
TIMES=()

TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
echo $TITLE_COLUMNS > $CSV_FILE

for i in "${SEQ_NB_THREADS[@]}"; do
    for j in $(seq 0 $NB_TIMES); do
        ARGS=$(( ${i} / 2 ))
        TIME=$(/usr/bin/time -f %e $EXEC_NAME $ARGS $ARGS 2>&1 | tail -n 1)
        TIMES[$j]=$TIME
    done
    TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
    echo $TIMES_LINE >> $CSV_FILE
done