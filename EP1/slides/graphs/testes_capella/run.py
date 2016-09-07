#!/usr/bin/python
import os
import sys

for n in [10, 100, 500]:
	for i in range(int(sys.argv[1]), int(sys.argv[2])):
		print (sys.argv[3], ": ", i, "-", n)
		os.system("../ep1 1 ./"+str(n)+"/"+str(i)+" ./result/"+str(n)+"-"+str(i)+"o1")
		os.system("../ep1 2 ./"+str(n)+"/"+str(i)+" ./result/"+str(n)+"-"+str(i)+"o2")
		os.system("../ep1 3 ./"+str(n)+"/"+str(i)+" ./result/"+str(n)+"-"+str(i)+"o3")

# qunatos deadlines não cumpridos
# trocas de contexto