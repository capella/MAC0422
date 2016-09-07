#!/usr/bin/python
import random
import numpy as np

tempo = 0.0
count = 0

for n in [10, 100, 500]:
	print(n, "processos")
	for i in range(30):
		file = open(str(n)+'/'+str(i), 'r')
		x = np.random.rand(n)*10.0
		y = np.full(n, 10.0)
		y = y - x
		y = y * np.random.rand(n)
		file.close()
		
		tempo = tempo + np.sum(y)
		count += n

