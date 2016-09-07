#gcloud compute instances start cpu1 cpu2 cpu4 --zone us-central1-b & 
#gcloud compute instances start cpu8 --zone us-east1-b
wait
echo "> CPU ligadas!"

COUNTER=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list)
for i in $COUNTER;
do
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -r ./run.py capellaresumo@$i:~/EP1/testes_capella 2> /dev/null &
    scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -r ./ep1 capellaresumo@$i:~/EP1 2> /dev/null &
done
wait
echo "> Arquivo Copiado a todos"
CPU41=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu4-1)
CPU42=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu4-2)
CPU43=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu4-3)
CPU44=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu4-4)
CPU45=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu4-5)
CPU46=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu4-6)
CPU81=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu8-1)
CPU82=$(gcloud --format="value(networkInterfaces[0].accessConfigs[0].natIP)" compute instances list cpu8-2)
wait

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU41 "cd EP1/testes_capella && python3 ./run.py 0 5 $CPU41" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU41:~/EP1/testes_capella/result/* ./r4/ 2> /dev/null &&
 echo "Finalizando " $CPU41 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU41 "sudo shutdown -h now" 2> /dev/null) &

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU42 "cd EP1/testes_capella && python3 ./run.py 5 10 $CPU42" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU42:~/EP1/testes_capella/result/* ./r4/ 2> /dev/null &&
 echo "Finalizando " $CPU42 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU42 "sudo shutdown -h now" 2> /dev/null) &

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU43 "cd EP1/testes_capella && python3 ./run.py 10 15 $CPU43" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU43:~/EP1/testes_capella/result/* ./r4/ 2> /dev/null &&
 echo "Finalizando " $CPU43 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU43 "sudo shutdown -h now" 2> /dev/null) &

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU44 "cd EP1/testes_capella && python3 ./run.py 15 20 $CPU44" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU44:~/EP1/testes_capella/result/* ./r4/ 2> /dev/null &&
 echo "Finalizando " $CPU44 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU44 "sudo shutdown -h now" 2> /dev/null) &

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU45 "cd EP1/testes_capella && python3 ./run.py 20 25 $CPU45" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU45:~/EP1/testes_capella/result/* ./r4/ 2> /dev/null &&
 echo "Finalizando " $CPU45 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU45 "sudo shutdown -h now" 2> /dev/null) &

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU46 "cd EP1/testes_capella && python3 ./run.py 25 30 $CPU46" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU46:~/EP1/testes_capella/result/* ./r4/ 2> /dev/null &&
 echo "Finalizando " $CPU46 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU46 "sudo shutdown -h now" 2> /dev/null) &

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU81 "cd EP1/testes_capella && python3 ./run.py 0 15 $CPU81" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU81:~/EP1/testes_capella/result/* ./r8/ 2> /dev/null &&
 echo "Finalizando " $CPU81 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU81 "sudo shutdown -h now" 2> /dev/null) &

(ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU82 "cd EP1/testes_capella && python3 ./run.py 15 30 $CPU82" 2> /dev/null &&
 scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU82:~/EP1/testes_capella/result/* ./r8/ 2> /dev/null &&
 echo "Finalizando " $CPU82 &&
 ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no capellaresumo@$CPU82 "sudo shutdown -h now" 2> /dev/null) &

wait
echo "> Finalizando"
echo  $CPU41 $CPU42 $CPU43 $CPU44 $CPU45 $CPU46 $CPU81 $CPU82

