import matplotlib.pyplot as plt
import numpy as np
import os

os. system('cls')
chm = os.getcwd()

def retirerFin(liste):
	liste2 = []
	for truc in liste:
		liste2.append(float(truc[:-2]))
	return liste2

files = []
names = ["Tri fusion", "Tri rapide", "Tri par tas", "Tri par compte"]

x = np.linspace(0, 656000, 16)

for i in range(4):
	f = open(""+str(i)+".txt" , 'r')
	files.append(f) 
	

for i in range(4):
	fig = plt.figure(1, figsize=(8, 5))	
	y = files[i].readlines()
	y = retirerFin(y)
	plt.title(names[i])
	plt.plot(x, y)
	plt.xlabel("Taille du tableau")
	plt.ylabel("Temps de tri (en s)")
	plt.savefig(names[i])
	plt.show()

