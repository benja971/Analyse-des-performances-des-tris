#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELT_MAX 100000
#define TAILLE 64
#define TAILLEMAX 31000
#define NBTESTS 50
#define NBFCT 4
#define PAS 1000

void initTab(unsigned long int *t, unsigned long int n, int jeu)
{
	switch (jeu)
	{
	case 0: //Aleatoire
		for (long int i = 0; i < n; i++)
		{
			t[i] = rand() % ELT_MAX;
		}
		break;

	case 1: //Ordonée avec repétition
		for (long int i = 0; i < n; i++)
		{
			if (rand() % 2 == 1 && i > 1)
			{
				t[i] = (unsigned long int)(((double)(i - 1) / n) * ELT_MAX);
			}
			else
			{
				t[i] = (unsigned long int)(((double)i / n) * ELT_MAX);
			}
		}
		break;

	case 2: //Ordonée sans répétition
		for (long int i = 0; i < n; i++)
		{
			t[i] = (unsigned long int)(((double)i / n) * ELT_MAX);
		}
		break;

	case 3: //Inversée avec répétition
		for (long int i = 0; i < n; i++)
		{
			if (i > 0 && rand() % 2 == 1)
			{
				t[(n - 1) - i] = (unsigned long int)(((double)(i - 1) / n) * ELT_MAX);
			}
			else
			{
				t[(n - 1) - i] = (unsigned long int)(((double)i / n) * ELT_MAX);
			}
		}

	case 4: //Inversée sans répétition
		for (long int i = 0; i < n; i++)
		{
			t[(n - 1) - i] = (unsigned long int)(((double)i / n) * ELT_MAX);
		}
	}
}

void fusion(unsigned long int *t, unsigned int d, unsigned int m, unsigned long int f)
{
	/* Création des tableaux auxiliaires */
	long int n1 = m - d + 1;
	long int n2 = f - m;
	long int i, j, k;

	unsigned long int *L, *M;
	L = (unsigned long int *)malloc(sizeof(unsigned long int) * n1);
	M = (unsigned long int *)malloc(sizeof(unsigned long int) * n2);

	for (i = 0; i < n1; i++)
		L[i] = t[d + i];
	for (j = 0; j < n2; j++)
		M[j] = t[m + 1 + j];

	/* Maintain current index of sub-arrays and main array */
	i = 0;
	j = 0;
	k = d;
	/* Until we reach either end of either L or M, pick larger among elements L and M and place them in the correct position at A[p..r] */
	while (i < n1 && j < n2)
	{
		if (L[i] <= M[j])
		{
			t[k] = L[i];
			i++;
		}
		else
		{
			t[k] = M[j];
			j++;
		}
		k++;
	}

	/* When we run out of elements in either L or M, pick up the remaining elements and put in A[p..r] */
	while (i < n1)
	{
		t[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		t[k] = M[j];
		j++;
		k++;
	}

	free(L);
	free(M);
}

void triFusion(unsigned long int *t, unsigned int d, unsigned long int n)
{
	unsigned long int q;

	if (d < n)
	{
		q = (d + n) / 2;
		triFusion(t, d, q);
		triFusion(t, q + 1, n);
		fusion(t, d, q, n);
	}
}

unsigned int partition(unsigned long int *t, unsigned int d, unsigned long int n)
{
	unsigned long int x = t[d];
	unsigned long int i = d - 1;
	unsigned int j = n + 1;
	unsigned long int b;

	long int flag = 1;

	while (flag)
	{
		do
		{
			j = j - 1;
		} while (t[j] > x);
		do
		{
			i = i + 1;
		} while (t[i] < x);
		if (i < j)
		{
			b = t[i];
			t[i] = t[j];
			t[j] = b;
		}
		else
		{
			flag = 0;
		}
	}
	return j;
}

void triRapide(unsigned long int *t, unsigned int d, unsigned long int n)
{
	unsigned long int q;
	if (d < n)
	{
		q = partition(t, d, n);
		triRapide(t, d, q);
		triRapide(t, q + 1, n);
	}
}

unsigned int tasParent(unsigned int i) { return (i - 1) / 2; }
unsigned int tasGauche(unsigned int i) { return 2 * i + 1; }
unsigned int tasDroite(unsigned int i) { return 2 * i + 2; }

void tasSifier(unsigned long int *t, unsigned long int taille, unsigned long int i)
{
	unsigned int l = tasGauche(i);
	unsigned int r = tasDroite(i);
	unsigned long int largest;

	largest = i;
	if (l <= taille)
	{
		if (t[l] > t[i])
		{
			largest = l;
		}
	}
	if (r <= taille)
	{
		if (t[r] > t[largest])
		{
			largest = r;
		}
	}
	if (largest != i)
	{
		unsigned long int b = t[i];
		t[i] = t[largest];
		t[largest] = b;
		tasSifier(t, taille, largest);
	}
}

void tasConstruire(unsigned long int *t, unsigned long int taille)
{
	for (long int i = taille / 2; i >= 0; i--)
	{
		tasSifier(t, taille, i);
	}
}

void triTas(unsigned long int *t, unsigned int d, unsigned long int n)
{
	unsigned long int taille = n;
	unsigned long int b;

	tasConstruire(t, n + 1);
	for (unsigned long int i = taille; i >= 1; i--)
	{

		b = t[0];
		t[0] = t[i];
		t[i] = b;
		taille = taille - 1;
		tasSifier(t, taille, 0);
	}
}

void triCompte(unsigned long int *t, unsigned int d, unsigned long int n)
{
	unsigned long int *B, *C;
	B = (unsigned long int *)malloc(sizeof(unsigned long int) * (n + 1));
	C = (unsigned long int *)malloc(sizeof(unsigned long int) * ELT_MAX);

	for (unsigned long int i = 0; i < ELT_MAX; i++)
	{
		C[i] = 0;
	}
	for (unsigned long int i = 0; i <= n; i++)
	{
		C[t[i]]++;
	}
	for (unsigned long int i = 1; i < ELT_MAX; i++)
	{
		C[i] = C[i] + C[i - 1];
	}
	for (long int i = n; i >= 0; i--)
	{
		B[C[t[i]] - 1] = t[i];
		C[t[i]]--;
	}
	for (unsigned long int i = 0; i <= n; i++)
	{
		t[i] = B[i];
	}

	free(B);
	free(C);
}

unsigned long int *copyTab(unsigned long int *Tab, long int j)
{
	unsigned long int *tabt = (unsigned long int *)malloc(sizeof(unsigned long int) * TAILLEMAX);
	if (tabt == NULL)
	{
		printf("Erreur creation tabt");
		exit(1);
	}

	for (long int i = 0; i < j; i++)
	{
		tabt[i] = Tab[i];
	}
	return tabt;
}

int main()
{
	remove("Temps/jeu_0");
	remove("Temps/jeu_1");
	remove("Temps/jeu_2");
	remove("Temps/jeu_3");
	remove("Temps/jeu_4");
	unsigned long int *Tab;
	unsigned long int taille = TAILLE;
	void (*sortFct[NBFCT])(unsigned long int *t, unsigned int d, unsigned long int n) = {triFusion, triRapide, triTas, triCompte};

	char path[50];
	Tab = (unsigned long int *)malloc(sizeof(unsigned long int) * TAILLEMAX);
	if (Tab == NULL)
	{
		printf("Erreur malloc.");
		exit(1);
	}

	for (int no_jeux = 0; no_jeux < 5; no_jeux++)
	{

		printf("Numero de jeu de données: %d\n", no_jeux);

		for (unsigned long int tailleTab = 1000; tailleTab < TAILLEMAX; tailleTab += PAS)
		{
			float moys[] = {0, 0, 0, 0};
			printf("Taille tab: %li\n", tailleTab);

			for (int nb_tests = 0; nb_tests < NBTESTS; nb_tests++)
			{
				printf("nombre de test: %d\n", nb_tests);
				initTab(Tab, tailleTab, no_jeux);
				for (int j = 0; j < NBFCT; j++)
				{
					printf("Fonction: %d\n", j);
					unsigned long int *tabt = copyTab(Tab, tailleTab); //Tableau à trier
					clock_t debut = clock();
					sortFct[j](tabt, 0, tailleTab); //Tri
					free(tabt);
					moys[j] += (clock() - debut) / 15.0;
					printf("%d %d\r", nb_tests, j);
				}
				system("cls");
			}

			snprintf(path, sizeof path, "Temps/jeu_%d", no_jeux);
			FILE *results_file = fopen(path, "a");
			if (results_file == NULL)
			{
				printf("Impossible d'ouvrir le fichier %s.\n", results_file);
				exit(0);
			}
			fprintf(results_file, "%li %.3f %.3f %.3f %.3f\n", tailleTab, moys[0], moys[1], moys[2], moys[3]);
			fclose(results_file);
		}
	}

	return 0;
}
