#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELT_MAX 100000
#define TAILLE 64
#define TAILLEMAX 100000
#define NBTEST 5
#define NBFCT 4

void printTab(unsigned long int *t, unsigned long int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%5d | ", t[i]);
	}
	printf("\n");
}

void initTab(unsigned long int *t, unsigned long int n)
{
	for (int i = 0; i < n; i++)
	{
		t[i] = rand() % ELT_MAX;
	}
}

void fusion(unsigned long int *t, unsigned int d, unsigned int m, unsigned long int f)
{
	/* Création des tableaux auxiliaires */
	long int n1 = m - d + 1;
	long int n2 = f - m;
	int i, j, k;

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

	int flag = 1;

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
	unsigned int largest;

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
		unsigned int b = t[i];
		t[i] = t[largest];
		t[largest] = b;
		tasSifier(t, taille, largest);
	}
}

void tasConstruire(unsigned long int *t, unsigned int long taille)
{
	for (int i = taille / 2; i >= 0; i--)
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
	unsigned int *B, *C;
	B = (unsigned int *)malloc(sizeof(unsigned int) * (n + 1));
	C = (unsigned int *)malloc(sizeof(unsigned int) * ELT_MAX);

	for (unsigned int i = 0; i < ELT_MAX; i++)
	{
		C[i] = 0;
	}
	for (unsigned int i = 0; i <= n; i++)
	{
		C[t[i]]++;
	}
	for (unsigned int i = 1; i < ELT_MAX; i++)
	{
		C[i] = C[i] + C[i - 1];
	}
	for (int i = n; i >= 0; i--)
	{
		B[C[t[i]] - 1] = t[i];
		C[t[i]]--;
	}
	for (unsigned int i = 0; i <= n; i++)
	{
		t[i] = B[i];
	}
}

unsigned long int *copyTab(unsigned long int *Tab, long int j)
{
	unsigned long int *tabt = (unsigned long int *)malloc(sizeof(unsigned long int) * TAILLEMAX);
	if (tabt == NULL)
	{
		printf("Erreur creation tabt");
		exit(1);
	}

	for (int i = 0; i < j; i++)
	{
		tabt[i] = Tab[i];
	}
	// printTab(tabt, j);
	return tabt;
}

double **createTabMoy()
{
	double **Moys = (double **)malloc(NBFCT * sizeof(double *));
	if (Moys == NULL)
	{
		printf("Erreur d'init de Moys**.");
		exit(1);
	}

	for (int i = 0; i < NBFCT; i++)
	{
		Moys[i] = (double *)malloc(sizeof(double));
		if (Moys[i] == NULL)
		{
			printf("Erreur d'init de Moys[%d].", i);
			exit(1);
		}
		Moys[i][0] = 0;
	}

	return Moys;
}

void realloc_p(double ***Moys, int taille, int i)
{
	(*Moys)[i] = (double *)realloc((*Moys)[i], (taille + 2) * sizeof(double));
	(*Moys)[i][taille + 1] = 0;
	if ((*Moys)[i] == NULL)
	{
		printf("Erreur dans le realloc.\n");
		exit(1);
	}
}

void affichertab2d(double **Moys, int *taille)
{
	for (int i = 0; i < *taille; i++)
	{
		for (int j = 0; j < NBFCT; j++)
		{
			printf("| %f ", (double)Moys[i][j]);
		}
		printf("|\n");
	}
}

int main()
{
	unsigned long int *Tab;
	double **Moys = createTabMoy();
	unsigned long int taille = TAILLE;
	int tailleM = 0;

	void (*sortFct[NBFCT])(unsigned long int *t, unsigned int d, unsigned long int n) = {triFusion, triRapide, triTas, triCompte};

	Tab = (unsigned long int *)malloc(sizeof(unsigned long int) * TAILLEMAX);
	if (Tab == NULL)
	{
		printf("Erreur malloc.");
		exit(1);
	}

	FILE *f = NULL;
	f = fopen("chrono.txt", "w");
	if (f == NULL)
	{
		printf("Erreur dans l'ouverture du fichier\n");
		exit(1);
	}

	for (long int i = 32; i < TAILLEMAX; i *= 2)
	{
		for(int k = 0; k < NBTESTS; k++)
		{
			initTab(Tab, i);
			for (int j = 0; j < NBFCT; j++)
			{
				unsigned long int *tabt = copyTab(Tab, i); //Tableau à trier
				clock_t time1 = clock();
				sortFct[j](tabt, 0, i); //Tri
				clock_t time2 = clock();
				Moys[j][tailleM] += (double)(time2 - time1) / 1000;
				realloc_p(&Moys, tailleM, j);
				free(tabt);
			}
		}
		tailleM++;
	}

	affichertab2d(Moys, &tailleM);
	fclose(f);

	printf("Le programme c'est deroule sans problemes.");
	return 0;
}
