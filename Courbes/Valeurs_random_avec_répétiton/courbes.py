import matplotlib.pyplot as plt
import os

os. system('cls')

def retirerFin(liste):
	liste2 = []
	for truc in liste:
		liste2.append(float(truc[:-2]))
	return liste2

files = []
names = ["Tri fusion", "Tri rapide", "Tri par tas", "Tri par compte"]

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

	for e in x:
		e *= 10
		print(x)
		
	fig = plt.figure(1, figsize=(8, 5))	
	plt.title(names[j])
	plt.scatter(x,y, marker='o', s = 10, c ="red")
	plt.plot(x, y, "--")
	plt.xlabel("Taille du tableau")
	plt.ylabel("Temps de tri (en s)")
	plt.savefig(names[j])
	plt.show()
	j+=1

