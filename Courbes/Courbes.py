import matplotlib.pyplot as plt
from os import listdir, system

system('cls')

for rep in listdir("Tris_1_par_1"):
	ys= []
	j = 0
	
	for file in listdir("Tris_1_par_1/"+rep):
		y = []
		x = []
		with open("Tris_1_par_1/" + rep +"/" + file) as f:
			l = f.readlines()

		for i in range(0, len(l), 2):	
			x.append(int(l[i]))
			y.append(float(l[i+1]))

		ys.append(y)

		fig = plt.figure(1, figsize=(8, 5))
		plt.scatter(x,ys[j], marker='o', s = 10, c="red")
		plt.plot(x, y, "--", label=file)
		plt.legend()
		plt.title("Comparaisons du "+rep.replace('_', ' ').lower()+" en fonction des jeux de données")
		j+=1

	plt.xlabel("Taille du tableau")
	plt.ylabel("Temps de tri (en s)")
	plt.savefig(rep.replace('_', ' ').lower())
	plt.show()

