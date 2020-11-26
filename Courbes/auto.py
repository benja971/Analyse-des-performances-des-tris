from typing import Counter
import matplotlib.pyplot as plt
from os import listdir, sep, system, remove

from matplotlib.pyplot import show

system('cls')


def courbeParJeu(lx ,ys, n, Tris, Jeux):
	j = 0
	c = []
	for y in ys:
		fig = plt.figure(1, figsize=(8, 5))
		c.append(fig)
		plt.plot(lx, y, "--", label=Tris[j])
		plt.scatter(lx, y, marker='o', s = 10)
		j+=1
		
	plt.legend()
	plt.title("Comparaison des temps obtenus pour les différents tris\n avec jeu de données " +  Jeux[n])
	plt.xlabel("Taille du tableau")
	plt.ylabel("Temps de tri (en ms)")
	plt.savefig("Courbes/" + Jeux[n])
	
	print(c)
	print('\n')
	


def courbeParTri(lx ,y, n, m, Jeux, Tris):
	c = []
	fig = plt.figure(1, figsize=(8, 5))
	c.append(fig)
	plt.plot(lx, y, "--", label=Jeux[n])
	plt.scatter(lx, y, marker='o', s = 10)
	plt.legend()
	plt.title("Comparaison des temps obtenus pour les différents tris\n avec jeu de données " +  Jeux[n])
	plt.xlabel("Taille du tableau")
	plt.ylabel("Temps de tri (en ms)")
	plt.savefig("Courbes/" + Tris[m])	
	print(c)
	
	

Tris = ["Tri fusion", "Tri rapide", "Tri par tas", "Tri par comptage"]
Jeux = ["Aléatoires avec répétitions", "Ordonnées avec répétitions", "Ordonnées sans répétitions", "Inversées avec répétitons", "Inversées sans répétitions"]

n = 0
for file in listdir("Temps"):
	print(file)
	ys, lx ,lt1, lt2, lt3, lt4 = [], [], [], [], [], []

	with open("Temps/" + file) as f:
		for line in f:
			x ,t1, t2, t3, t4 = line.split()
			lx.append(int(x))
			lt1.append(float(t1))
			lt2.append(float(t2))
			lt3.append(float(t3))
			lt4.append(float(t4))

	ys.append(lt1)
	ys.append(lt2)
	ys.append(lt3)
	ys.append(lt4)
	# courbeParJeu(lx ,ys, n, Jeux)
	
	m = 0
	for y in ys:
		print(Tris[m])	
		courbeParTri(lx, y, n, m, Jeux, Tris)
		m+=1
	n+=1




