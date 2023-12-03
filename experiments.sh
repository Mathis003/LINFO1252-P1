NB_TIMES=5
SEQ_NB_THREADS=(1 2 4 8 16 32 64)
TIMES=()

NAME_PROGRAM=("main_my_mutex_TS" "main_my_mutex_TTS" "main_my_mutex_BTTS")
SEQ_ITER=(0 1 2)

for k in "${SEQ_ITER[@]}"; do

    EXEC_NAME="bin/${NAME_PROGRAM[$k]}.bin"
    CSV_FILE="csv_files/perfs_${NAME_PROGRAM[$k]}.csv"
    echo $CSV_FILE
    TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
    echo $TITLE_COLUMNS
    for i in "${SEQ_NB_THREADS[@]}"; do
        for j in $(seq 0 $NB_TIMES); do
            START_TIME=$(/usr/bin/date +%s.%N)
            $EXEC_NAME $i > /dev/null
            END_TIME=$(/usr/bin/date +%s.%N)
            TIME=$(echo "$END_TIME - $START_TIME" | bc)
            TIMES[$j]=$TIME
        done
        TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
        echo $TIMES_LINE
    done
    echo " "
done