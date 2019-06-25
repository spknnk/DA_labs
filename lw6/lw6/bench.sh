make
python test.py $1

for i in `seq 5`;
    do ./lw6 < 0${i}.txt > answer ;
    echo "$i\t" ;
    grep time answer
    python3 benchmark.py < 0${i}.txt > answerPy ;
    grep time answerPy
done