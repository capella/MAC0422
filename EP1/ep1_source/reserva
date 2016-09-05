echo "Para cumprimento de deadline"
echo "Executando com poucos processos"
for j in {1..30}
do
    ./ep1 1 t-1.txt t1-1.txt
    ./ep1 2 t-1.txt t1-2.txt
    ./ep1 3 t-1.txt t1-3.txt
done
echo "Executando com +/- processos"
for j in {1..30}
do 
    ./ep1 1 t-2.txt t2-1.txt 
    ./ep1 2 t-2.txt t2-2.txt
    ./ep1 3 t-2.txt t2-3.txt  
done
echo "Executando com muitos processos"
for j in {1..30}
do
    ./ep1 1 t-3.txt t3-1.txt
    ./ep1 2 t-3.txt t3-2.txt
    ./ep1 3 t-3.txt t3-3.txt  
done