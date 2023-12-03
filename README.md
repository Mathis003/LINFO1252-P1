# LINFO1252_P1

TODOLIST:
- Run experiments.sh sur le serveur (pour avoir le .csv de producer_consumer) + replot le graph producer_consumer (avais oublié un process())


NB_TIMES=5
SEQ_NB_THREADS=(2 4 8 16 32 64)
TIMES=()
SEQ_ITER=(0 1 2 3)


NAME_PROGRAM=("producer_consumer_POSIX" "producer_consumer_TS" "producer_consumer_TTS" "producer_consumer_BTTS")

for k in "${SEQ_ITER[@]}"; do

    EXEC_NAME="bin/${NAME_PROGRAM[$k]}.bin"
    CSV_FILE="csv_files/perfs_${NAME_PROGRAM[$k]}.csv"
    echo $CSV_FILE
    TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
    echo $TITLE_COLUMNS
    for i in "${SEQ_NB_THREADS[@]}"; do
        for j in $(seq 0 $NB_TIMES); do
            ARGS=$(( ${i} / 2 ))
            TIME=$(/usr/bin/time -f %e $EXEC_NAME $ARGS $ARGS 2>&1 | tail -n 1)
            TIMES[$j]=$TIME
        done
        TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
        echo $TIMES_LINE
    done
    echo " "
done

NAME_PROGRAM=("reader_writer_POSIX" "reader_writer_TS" "reader_writer_TTS" "reader_writer_BTTS")

for k in "${SEQ_ITER[@]}"; do

    EXEC_NAME="bin/${NAME_PROGRAM[$k]}.bin"
    CSV_FILE="csv_files/perfs_${NAME_PROGRAM[$k]}.csv"
    echo $CSV_FILE
    TITLE_COLUMNS=$(printf "NbThreads%s" $(for ((i=1; i<=$NB_TIMES; i++)); do printf ",Time%d" $i; done))
    echo $TITLE_COLUMNS
    for i in "${SEQ_NB_THREADS[@]}"; do
        for j in $(seq 0 $NB_TIMES); do
            ARGS=$(( ${i} / 2 ))
            TIME=$(/usr/bin/time -f %e $EXEC_NAME $ARGS $ARGS 2>&1 | tail -n 1)
            TIMES[$j]=$TIME
        done
        TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
        echo $TIMES_LINE
    done
    echo " "
done


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


NAME_PROGRAM=("philosopher_POSIX" "philosopher_TS" "philosopher_TTS" "philosopher_BTTS")

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







csv_files/perfs_producer_consumer_POSIX.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.11,0.11,0.11,0.11,0.11
4,0.05,0.05,0.05,0.05,0.05
8,0.02,0.02,0.03,0.02,0.02
16,0.01,0.01,0.01,0.01,0.01
32,0.02,0.02,0.02,0.02,0.02
64,0.02,0.02,0.02,0.02,0.02

csv_files/perfs_producer_consumer_TS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.11,0.11,0.11,0.11,0.11
4,0.05,0.05,0.05,0.05,0.05
8,0.02,0.02,0.02,0.02,0.02
16,0.01,0.01,0.01,0.01,0.01
32,0.04,0.13,0.09,0.02,0.05
64,0.54,0.39,1.01,0.64,2.57

csv_files/perfs_producer_consumer_TTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.11,0.11,0.11,0.11,0.11
4,0.05,0.05,0.05,0.05,0.05
8,0.02,0.02,0.02,0.02,0.02
16,0.01,0.01,0.01,0.01,0.01
32,0.09,0.02,0.14,0.12,0.03
64,0.59,1.06,1.30,0.80,1.01

csv_files/perfs_producer_consumer_BTTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.11,0.12,0.12,0.12,0.11
4,0.07,0.08,0.07,0.07,0.07
8,0.08,0.08,0.07,0.07,0.08
16,0.30,0.30,0.26,0.28,0.26
32,0.47,0.49,0.50,0.46,0.48
64,0.72,0.67,0.71,0.72,0.69

csv_files/perfs_reader_writer_POSIX.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.04,0.04,0.04,0.04,0.04
4,0.02,0.02,0.02,0.02,0.02
8,0.01,0.01,0.01,0.01,0.01
16,0.01,0.01,0.01,0.01,0.01
32,0.01,0.01,0.01,0.01,0.01
64,0.01,0.01,0.01,0.01,0.01

csv_files/perfs_reader_writer_TS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.04,0.04,0.04,0.04,0.04
4,0.02,0.02,0.02,0.02,0.03
8,0.03,0.02,0.01,0.02,0.01
16,0.01,0.01,0.01,0.01,0.01
32,0.10,0.03,0.05,0.02,0.01
64,0.13,0.19,0.29,0.07,0.23

csv_files/perfs_reader_writer_TTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.04,0.04,0.04,0.04,0.04
4,0.03,0.02,0.02,0.03,0.02
8,0.02,0.03,0.01,0.01,0.01
16,0.01,0.01,0.01,0.01,0.01
32,0.05,0.01,0.07,0.04,0.01
64,0.14,0.18,0.08,0.20,0.37

csv_files/perfs_reader_writer_BTTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.06,0.06,0.05,0.06,0.05
4,0.04,0.04,0.04,0.04,0.04
8,0.04,0.04,0.04,0.04,0.04
16,0.04,0.04,0.04,0.04,0.04
32,0.05,0.05,0.04,0.04,0.05
64,0.05,0.04,0.04,0.04,0.04

csv_files/perfs_main_my_mutex_TS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.00,0.00,0.00,0.00,0.00
4,0.00,0.00,0.00,0.00,0.00
8,0.00,0.00,0.00,0.00,0.00
16,0.00,0.00,0.00,0.00,0.00
32,0.00,0.00,0.00,0.00,0.00
64,0.00,0.00,0.00,0.00,0.00

csv_files/perfs_main_my_mutex_TTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.00,0.00,0.00,0.00,0.00
4,0.00,0.00,0.00,0.00,0.00
8,0.00,0.00,0.00,0.00,0.00
16,0.00,0.00,0.00,0.00,0.00
32,0.00,0.00,0.00,0.00,0.00
64,0.00,0.00,0.00,0.00,0.00

csv_files/perfs_main_my_mutex_BTTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.00,0.00,0.00,0.00,0.00
4,0.00,0.00,0.00,0.00,0.00
8,0.00,0.00,0.00,0.00,0.00
16,0.00,0.00,0.00,0.00,0.00
32,0.00,0.00,0.00,0.00,0.00
64,0.00,0.00,0.00,0.00,0.00