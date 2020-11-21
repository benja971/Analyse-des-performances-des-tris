import matplotlib.pyplot as plt
import numpy as np
import os
from math import log

from numpy.core.fromnumeric import size

os. system('cls')

def retirerFin(liste):
	liste2 = []
	for truc in liste:
		liste2.append(float(truc[:-2]))
	return liste2

files = []
names = ["Tri fusion", "Tri rapide", "Tri par tas", "Tri par compte"]

# x = np.linspace(0, 44000, 16)


for i in range(4):
	f = open(""+str(i)+".txt" , 'r')
	files.append(f) 



i = 0
j = 0
for f in files:
	x = []
	y = []
	l1 = []
	l1 = f.readlines()
	l1 = retirerFin(l1)

	for i in range(len(l1)):
		if i%2 == 0:
			x.append(l1[i])
		else:
			y.append(l1[i])

	fig = plt.figure(1, figsize=(8, 5))	
	plt.title(names[j])
	plt.scatter(x,y, marker='o', s = 10, c ="red")
	plt.plot(x, y)
	plt.plot(x, [x[n]*log(x[n]) for n in range(12)])
	plt.xlabel("Taille du tableau")
	plt.ylabel("Temps de tri (en s)")
	plt.savefig(names[j])
	plt.show()
	j+=1

