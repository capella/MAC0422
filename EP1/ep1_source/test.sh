#!/bin/bash
echo "Para mudanças de contexto"
echo "Executando com poucos processos"
for j in {1..30}
do
    ./ep1 1 t-1.txt t4-1.txt
    ./capta 10 < t4-1.txt >> t4-1a.txt
    ./ep1 2 t-1.txt t4-2.txt
    ./capta 10 < t4-2.txt >> t4-2a.txt
    ./ep1 3 t-1.txt t4-3.txt
    ./capta 10 < t4-3.txt >> t4-3a.txt  
done
./Transforma 10 < t4-1a.txt > t4-1b.txt
./Transforma 10 < t4-2a.txt > t4-2b.txt
./Transforma 10 < t4-3a.txt > t4-3b.txt
echo "Executando com +/- processos"
for j in {1..30}
do
    ./ep1 1 t-2.txt t5-1.txt
    ./capta 100 < t5-1.txt >> t5-1a.txt
    ./ep1 2 t-2.txt t5-2.txt
    ./capta 100 < t5-2.txt >> t5-2a.txt
    ./ep1 3 t-2.txt t5-3.txt
    ./capta 100 < t5-3.txt >> t5-3a.txt  
done
./Transforma 100 < t5-1a.txt > t5-1b.txt
./Transforma 100 < t5-2a.txt > t5-2b.txt
./Transforma 100 < t5-3a.txt > t5-3b.txt
echo "Executando com muitos processos"
for j in {1..30}
do
    ./ep1 1 t-3.txt t6-1.txt
    ./capta 1000 < t6-1.txt >> t6-1a.txt
    ./ep1 2 t-3.txt t6-2.txt
    ./capta 1000 < t6-2.txt >> t6-2a.txt
    ./ep1 3 t-3.txt t6-3.txt
    ./capta 1000 < t6-3.txt >> t6-3a.txt  
done
./Transforma 1000 < t6-1a.txt > t6-1b.txt
./Transforma 1000 < t6-2a.txt > t6-2b.txt
./Transforma 1000 < t6-3a.txt > t6-3b.txt