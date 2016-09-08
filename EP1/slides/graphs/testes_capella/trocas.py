#!/usr/bin/python
import random
import numpy as np
import scipy as sp
import scipy.stats
import sys

# python3 resultados.py r4 10

def confidence_interval(data, confidence=0.95):
	a = 1.0*np.array(data)
	n = len(a)
	m, se = np.mean(a), scipy.stats.sem(a)
	h = se * sp.stats.t._ppf((1+confidence)/2., n-1)
	return m, h

n = sys.argv[2]

print("tipo_escalonador", "media", "ci")
for l in range(1,4):
	c = []
	for i in range(30):
		z = sys.argv[1]+"/"+n+"-"+str(i)+"o"+str(l)
		with open(z) as f:
			for line in f:
				args = line.split()
				if len(args) == 1:
					c.append(float(args[0]))
	m, ci = confidence_interval(c)
	print(l, m, ci)

