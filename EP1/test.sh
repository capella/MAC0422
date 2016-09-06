gcloud compute instances start cpu1 cpu2 cpu4 --zone us-central1-b & 
gcloud compute instances start cpu8 --zone us-east1-b
wait
echo "> CPU ligadas!"

COUNTER=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list)
for i in $COUNTER;
do
	ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i "mkdir tmp"
    (scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -r ./* capellaresumo@$i:~/tmp &&
    ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i "cd tmp && make && ./ep1 3 testes/entradas/t-1.txt out.txt c 2> log" &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/log ./testes/saidas/$i-1log3.txt &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/out.txt ./testes/saidas/$i-1out3.txt &&
    ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i "cd tmp && ./ep1 3 testes/entradas/t-2.txt out.txt c 2> log" &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/log ./testes/saidas/$i-2log3.txt &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/out.txt ./testes/saidas/$i-2out3.txt &&
    ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i "cd tmp && ./ep1 2 testes/entradas/t-1.txt out.txt c 2> log" &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/log ./testes/saidas/$i-1log2.txt &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/out.txt ./testes/saidas/$i-1out2.txt &&
    ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i "cd tmp && ./ep1 2 testes/entradas/t-2.txt out.txt c 2> log" &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/log ./testes/saidas/$i-2log2.txt &&
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i:~/tmp/out.txt ./testes/saidas/$i-2out2.txt &&
    ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$i "rm -rf ./tmp && sudo shutdown -h now") &

done