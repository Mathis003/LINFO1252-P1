OUTPUT_FILE="mesures.csv"
PATH_MAKEFILE="LINFO1252_P1"
TITLE_COLUMNS="NbThreads,Time1,Time2,Time3,Time4,Time5"
NB_THREADS=(1 2 3 4 5 6 7 8)
TIMES=()

echo $TITLE_COLUMNS > $OUTPUT_FILE

make -C $PATH_MAKEFILE -s clean
for i in {1..8}
do
    for j in {1..5}
    do
        TIME=$(/usr/bin/time -f %e make -C $PATH_MAKEFILE -s -j$i 2>&1 | tail -n 1)
        TIMES[${j}-1]=${TIME}
        make -C $PATH_MAKEFILE -s clean
    done
    echo "${NB_THREADS[${i}-1]},${TIMES[0]},${TIMES[1]},${TIMES[2]},${TIMES[3]},${TIMES[4]}" >> $OUTPUT_FILE
done