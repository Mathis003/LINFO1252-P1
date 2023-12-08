# LINFO1252_P1


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


======== PRODUCER_CONSUMER ========

csv_files/perfs_producer_consumer_POSIX.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.10,0.10,0.10,0.10,0.10
4,0.05,0.05,0.05,0.05,0.05
8,0.02,0.02,0.02,0.02,0.02
16,0.01,0.01,0.01,0.01,0.01
32,0.02,0.02,0.02,0.02,0.02
64,0.03,0.03,0.02,0.02,0.03

csv_files/perfs_producer_consumer_TS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.10,0.10,0.10,0.10,0.10
4,0.05,0.05,0.05,0.05,0.05
8,0.02,0.02,0.02,0.02,0.02
16,0.01,0.01,0.01,0.01,0.01
32,0.07,0.26,0.10,0.02,0.02
64,0.48,0.37,0.44,1.12,0.46

csv_files/perfs_producer_consumer_TTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.11,0.10,0.10,0.10,0.10
4,0.05,0.05,0.05,0.05,0.05
8,0.02,0.02,0.02,0.02,0.02
16,0.01,0.01,0.01,0.01,0.01
32,0.17,0.02,0.02,0.02,0.06
64,0.27,0.49,0.10,0.81,0.31

csv_files/perfs_producer_consumer_BTTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.11,0.11,0.11,0.12,0.11
4,0.08,0.09,0.07,0.06,0.09
8,0.14,0.24,0.42,0.13,0.15
16,1.04,1.06,1.15,1.07,1.14
32,1.40,1.40,1.45,1.28,1.46
64,1.86,1.94,1.86,2.13,1.93


======== READER_WRITER ========

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
4,0.02,0.02,0.02,0.04,0.03
8,0.05,0.01,0.01,0.03,0.01
16,0.01,0.01,0.01,0.01,0.01
32,0.18,0.01,0.01,0.01,0.02
64,0.04,0.13,0.06,0.27,0.05

csv_files/perfs_reader_writer_TTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.04,0.04,0.04,0.04,0.04
4,0.02,0.02,0.02,0.02,0.02
8,0.01,0.01,0.01,0.01,0.01
16,0.01,0.01,0.01,0.01,0.01
32,0.03,0.03,0.07,0.01,0.02
64,0.09,0.18,0.16,0.06,0.23

csv_files/perfs_reader_writer_BTTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.05,0.06,0.06,0.06,0.05
4,0.05,0.05,0.04,0.05,0.07
8,0.11,0.11,0.16,0.06,0.06
16,0.12,0.06,0.19,0.07,0.06
32,0.06,0.06,0.06,0.08,0.11
64,0.07,0.09,0.08,0.08,0.07


======== PHILOSOPHER ========


csv_files/perfs_philosopher_POSIX.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.15,0.11,0.13,0.16,0.16
4,0.33,0.35,0.33,0.36,0.38
8,0.49,0.52,0.51,0.53,0.56
16,0.75,0.77,0.88,0.85,0.87
32,1.53,1.58,1.56,1.48,1.64
64,2.92,2.91,2.83,2.93,2.99

csv_files/perfs_philosopher_TS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.22,0.22,0.21,0.15,0.20
4,0.44,0.44,0.43,0.48,0.51
8,0.90,1.21,1.34,1.30,1.47
16,2.39,2.69,2.19,2.32,3.02
32,6.63,7.23,7.44,6.40,6.52
64,17.44,18.67,16.90,19.29,19.37

csv_files/perfs_philosopher_TTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.15,0.21,0.20,0.21,0.16
4,0.51,0.52,0.51,0.43,0.45
8,0.99,1.16,0.80,1.11,1.11
16,2.07,2.53,2.21,2.32,2.30
32,5.76,5.72,5.84,5.53,5.80
64,16.18,14.33,14.47,14.18,13.90

csv_files/perfs_philosopher_BTTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
2,0.07,0.07,0.07,0.07,0.09
4,0.18,0.20,0.20,0.18,0.18
8,0.31,0.34,0.34,0.39,0.35
16,0.68,0.67,0.68,0.67,0.72
32,1.33,1.41,1.34,1.34,1.35
64,2.73,2.72,2.73,2.77,2.70


======== MAIN_MY_MUTEX ========


csv_files/perfs_main_my_mutex_TS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
1,0.08,0.08,0.08,0.08,0.08
2,0.07,0.07,0.07,0.07,0.07
4,0.08,0.08,0.08,0.08,0.10
8,0.08,0.08,0.08,0.08,0.08
16,0.08,0.08,0.08,0.08,0.08
32,0.14,0.11,0.15,0.13,0.10
64,0.28,0.30,0.24,0.18,0.29

csv_files/perfs_main_my_mutex_TTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
1,0.07,0.07,0.07,0.07,0.07
2,0.07,0.07,0.07,0.07,0.07
4,0.07,0.07,0.07,0.07,0.07
8,0.07,0.07,0.07,0.07,0.07
16,0.07,0.07,0.07,0.07,0.07
32,0.09,0.14,0.07,0.07,0.07
64,0.16,0.18,0.18,0.19,0.10

csv_files/perfs_main_my_mutex_BTTS.csv
NbThreads,Time1,Time2,Time3,Time4,Time5
1,0.07,0.07,0.07,0.07,0.07
2,0.07,0.07,0.07,0.07,0.07
4,0.07,0.07,0.07,0.07,0.07
8,0.07,0.07,0.08,0.07,0.07
16,0.08,0.08,0.08,0.08,0.08
32,0.08,0.08,0.08,0.08,0.08
64,0.08,0.08,0.08,0.08,0.08




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
            TIME=$(/usr/bin/time -f %e $EXEC_NAME $i 2>&1 | tail -n 1)
            TIMES[$j]=$TIME
        done
        TIMES_LINE=$(printf "%d%s" $i $(for ((j=0; j<$NB_TIMES; j++)); do printf ",%s" "${TIMES[$j]}"; done))
        echo $TIMES_LINE
    done
    echo " "
done

SEQ_NB_THREADS=(2 4 8 16 32 64)
NAME_PROGRAM=("producer_consumer_POSIX" "producer_consumer_TS" "producer_consumer_TTS" "producer_consumer_BTTS")
SEQ_ITER=(0 1 2 3)

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