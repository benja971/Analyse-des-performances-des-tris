import matplotlib.pyplot as plt
import numpy as np
import os

os. system('cls')

names = ["Tri fusion", "Tri rapide", "Tri par tas", "Tri par compte"]


x = []
y = []
j = 0
for i in range(4):
	with  open(""+str(i)+".txt" , 'r') as f:
		x.clear()
		y.clear()
		l1 = f.readlines()
		
		for i in range(len(l1)):
			if i%2 == 0:
				x.append(int(l1[i][:-1]))
			else:
				y.append(float(l1[i][:-1]))

	fig = plt.figure(1, figsize=(8, 5))
	plt.title(names[j])
	plt.scatter(x,y, marker='o', s = 10, c = 'red')
	plt.plot(x, y, "--")
	plt.xlabel("Taille du tableau")
	plt.ylabel("Temps de tri (en s)")
	plt.savefig(names[j])
	plt.show()
	j+=1

