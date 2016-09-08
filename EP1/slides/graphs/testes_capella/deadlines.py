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

print("deadt_mult", "tipo_1_m", "tipo_1_ic", "tipo_2_m", "tipo_2_ic", "tipo_3_m", "tipo_3_ic")
for deadt in np.linspace(0, 180, 50):
	r = []
	for l in range(1,4):
		c = []
		for i in range(30):
			z = sys.argv[1]+"/"+n+"-"+str(i)+"o"+str(l)
			x = str(n)+"/"+str(i)
			a = {}
			with open(x) as f:
				for line in f:
					args = line.split()
					a[args[1]] = float(args[0])+float(args[2])+deadt
			with open(z) as f:
				nao_c = 0
				total = 0
				for line in f:
					args = line.split()
					if len(args) == 3:
						if a[args[0]] < float(args[1]):
							nao_c += 1
						total += 1
				c.append((total-nao_c)*1.0/total)

		m, ci = confidence_interval(c)
		r.append(str(m))
		r.append(str(ci))
	print(deadt*1.0, ' '.join(r))

