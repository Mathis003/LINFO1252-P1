OUTPUT_FILE="perfs.csv"
TITLE_COLUMNS="NbThreads,Time1,Time2,Time3,Time4,Time5"
NB_THREADS=(1 2 3 4 5 6 7 8)
TIMES=()

echo $TITLE_COLUMNS > $OUTPUT_FILE

# Compilation
make -s clean
make -s

for i in {1..8}
do
    for j in {1..5}
    do
        TIME=$(/usr/bin/time -f %e ./main.out $i 2>&1 | tail -n 1)
        TIMES[${j}-1]=${TIME}
    done
    echo "${NB_THREADS[${i}-1]},${TIMES[0]},${TIMES[1]},${TIMES[2]},${TIMES[3]},${TIMES[4]}" >> $OUTPUT_FILE
done