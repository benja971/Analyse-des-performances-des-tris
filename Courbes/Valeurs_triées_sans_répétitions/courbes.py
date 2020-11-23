import matplotlib.pyplot as plt
import os

os. system('cls')

names = ["Tri fusion", "Tri rapide", "Tri par tas", "Tri par compte"]
i = 0
j = 0

x = []
ys = []
for i in range(4):
	with  open(""+str(i)+".txt" , 'r') as f:
		x.clear()
		y = []
		l1 = f.readlines()
		

		for i in range(len(l1)):
			if i%2 == 0:
				x.append(int(l1[i][:-1]))
			else:
				y.append(float(l1[i][:-1]))

	ys.append(y)	


for y in ys:
	fig = plt.figure(1, figsize=(8, 5))
	plt.scatter(x,y, marker='o', s = 10)
	plt.plot(x, y, "--", label=names[j])
	plt.legend()
	j+=1

plt.title("Comparaison des temps obtenus pour les différents tris\n avec jeu de données ordonnées sans répétitions")
plt.xlabel("Taille du tableau")
plt.ylabel("Temps de tri (en s)")
plt.savefig("ordonnées sans répétitions")
plt.show()

