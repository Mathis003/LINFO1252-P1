EXEC_NAME="bin/test_and_test_and_set.bin"
CSV_FILE="csv_files/perfs_test_and_test_and_set.csv"

NB_TIMES=5
SEQ_NB_THREADS=(1 2 4 8 16 32 64)
TIMES=()

TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
echo $TITLE_COLUMNS > $CSV_FILE

for i in "${SEQ_NB_THREADS[@]}"; do
    for j in $(seq 0 $NB_TIMES); do
        TIME=$(/usr/bin/time -f %e $EXEC_NAME $i 2>&1 | tail -n 1)
        TIMES[$j]=$TIME
    done
    TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
    echo $TIMES_LINE >> $CSV_FILE
done