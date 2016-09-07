#!/usr/bin/python
import random
import numpy as np

tempo = 0.0
count = 0

for n in [10, 100, 500]:
	for i in range(30):
		file = open(str(n)+'/'+str(i), 'w')
		x = np.random.rand(n)*10.0
		y = np.full(n, 10.0)
		y = y - x
		y = y * np.random.rand(n)
		for k in range(n):
			file.write(str(x[k])+" p"+str(k)+" "+str(y[k])+" ")
			file.write(str(x[k]+y[k])+"\n")
		file.close()
		
		tempo = tempo + np.sum(y)
		count += n

print (tempo/3600.0, tempo/count)
