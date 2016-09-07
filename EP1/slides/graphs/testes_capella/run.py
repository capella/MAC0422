#!/usr/bin/python
import os
import sys

for i in range(int(sys.argv[1]), int(sys.argv[2])):
	print (i)
	os.system("../../../ep1 1 ./10/"+str(i)+" ./result/10-"+str(i)+"o1")
	os.system("../../../ep1 2 ./10/"+str(i)+" ./result/10-"+str(i)+"o2")
	os.system("../../../ep1 3 ./10/"+str(i)+" ./result/10-"+str(i)+"o3")

# qunatos deadlines não cumpridos
# trocas de contexto