NB_TIMES=5
TIMES=()
SEQ_NB_THREADS=(2 4 8 16 32 64)
NAME_PROGRAM=("philosopher_TTS" "philosopher_BTTS")
SEQ_ITER=(0 1)

for k in "${SEQ_ITER[@]}"; do
    EXEC_NAME="bin/${NAME_PROGRAM[$k]}.bin"
    CSV_FILE="csv_files/perfs_${NAME_PROGRAM[$k]}.csv"
    echo $CSV_FILE
    TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
    echo $TITLE_COLUMNS
    for i in "${SEQ_NB_THREADS[@]}"; do
        for j in $(seq 0 $NB_TIMES); do
            TIME=$(/usr/bin/time -f %e $EXEC_NAME $i 2>&1 | tail -n 1)
            TIMES[$j]=$TIME
        done
        TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
        echo $TIMES_LINE
    done
    echo " "
done


NB_TIMES=5
TIMES=()
SEQ_NB_THREADS=(1 2 4 8 16 32 64)
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
            TIME=$(/usr/bin/time -f %e $EXEC_NAME $i 2>&1 | tail -n 1)
            TIMES[$j]=$TIME
        done
        TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
        echo $TIMES_LINE
    done
    echo " "
done