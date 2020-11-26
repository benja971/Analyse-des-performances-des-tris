#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELT_MAX 100000
#define TAILLE 64
#define TAILLEMAX 10000000
#define NBTEST 5
#define NBTAILLE 12
#define NBFCT 5

void *malloc_protege(size_t s)
{
  void *p;
  if (p = malloc(s))
    return p;
  else
  {
    perror("erreur allocation\n");
    exit(EXIT_FAILURE);
  }
}

void printTab(unsigned int *t, unsigned int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%5d ", t[i]);
  }
  printf("\n");
}

void initTab(unsigned int *t, unsigned int n)
{
  for (int i = 0; i < n; i++)
  {
    t[i] = rand() % ELT_MAX;
  }
}

void initTabOrd(unsigned int *t, unsigned int n)
{
  for (int i = 0; i < n; i++)
  {
    t[i] = i;
  }
}

void initTabInv(unsigned int *t, unsigned int n)
{
  for (int i = 0; i < n; i++)
  {
    t[i] = n - i;
  }
}

void triInsertion(unsigned int *t, unsigned int d, unsigned int n)
{

  for (int j = 1; j <= n; j++)
  {
    unsigned int key = t[j];
    int i = j - 1;

    /* while((i >= 0)&&(t[i] > key)){ */
    /* 	  t[i+1] = t[i]; */
    /* 	  i--; */
    /* 	} */

    int flag = (t[i] > key);
    while ((i >= 0) && flag)
    {
      t[i + 1] = t[i];
      i--;
      if (i >= 0)
        flag = (t[i] > key);
    }

    t[i + 1] = key;
  }
}

void fusion(unsigned int *t, unsigned int d, unsigned int m, unsigned int f)
{
  /* Création des tableaux auxiliaires */
  int n1 = m - d + 1;
  int n2 = f - m;
  int i, j, k;

  unsigned int *L, *M;
  L = (unsigned int *)malloc_protege(sizeof(unsigned int) * n1);
  M = (unsigned int *)malloc_protege(sizeof(unsigned int) * n2);

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

  free(M);
  free(L);
}

void triFusion(unsigned int *t, unsigned int d, unsigned int n)
{
  unsigned int q;

  /* printf("B : %2d %2d %2d -> ",d,q,n); */
  /* printTab(t,10); */

  if (d < n)
  {
    q = (d + n) / 2;
    triFusion(t, d, q);
    triFusion(t, q + 1, n);
    fusion(t, d, q, n);
  }
  /* printf("A : %2d %2d %2d -> ",d,q,n); */
  /* printTab(t,10); */
}

unsigned int partition(unsigned int *t, unsigned int d, unsigned int n)
{
  unsigned int x = t[d];
  unsigned int i = d - 1;
  unsigned int j = n + 1;
  unsigned int b;

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

void triRapide(unsigned int *t, unsigned int d, unsigned int n)
{
  unsigned int q;
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

void tasSifier(unsigned int *t, unsigned int taille, unsigned int i)
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

void tasConstruire(unsigned int *t, unsigned int taille)
{

  for (int i = taille / 2; i >= 0; i--)
  {
    tasSifier(t, taille, i);
  }
}

void triTas(unsigned int *t, unsigned int d, unsigned int n)
{
  unsigned int taille = n;
  unsigned int b;

  tasConstruire(t, n + 1);
  for (unsigned int i = taille; i >= 1; i--)
  {

    b = t[0];
    t[0] = t[i];
    t[i] = b;
    taille = taille - 1;
    tasSifier(t, taille, 0);
  }
}

void triCompte(unsigned int *t, unsigned int d, unsigned int n)
{
  unsigned int *B, *C;
  B = (unsigned int *)malloc_protege(sizeof(unsigned int) * (n + 1));
  C = (unsigned int *)malloc_protege(sizeof(unsigned int) * ELT_MAX);

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

  free(B);
  free(C);
}

int main()
{

  unsigned int *Tab, *TTT;
  unsigned int taille = TAILLE;

  clock_t start, finish;
  double avg_dur[NBFCT];

  void (*sortFct[NBFCT])(unsigned int *t, unsigned int d, unsigned int n) = {triInsertion, triFusion, triRapide, triTas, triCompte};

  Tab = (unsigned int *)malloc(sizeof(unsigned int) * TAILLEMAX);
  TTT = (unsigned int *)malloc(sizeof(unsigned int) * TAILLEMAX);

  for (int j = 0; j < NBTAILLE; j++)
  {
    for (int k = 0; k < NBFCT; k++)
    {
      avg_dur[k] = 0.0;
    }
    for (int i = 0; i < NBTEST; i++)
    {
      initTab(TTT, taille);
      for (int k = 0; k < NBFCT; k++)
      {
        for (int l = 0; l < taille; l++)
        {
          Tab[l] = TTT[l];
        }
        start = clock();
        sortFct[k](Tab, 0, taille - 1);
        finish = clock();
        avg_dur[k] += ((double)(finish - start)) / CLOCKS_PER_SEC;
      }
    }

    printf("%d", taille);
    for (int k = 0; k < NBFCT; k++)
    {
      avg_dur[k] = avg_dur[k] / NBTEST;
      printf(" %2.3f", avg_dur[k] * 1000);
    }
    printf("\n");

    taille *= 2;
  }

  free(Tab);
  free(TTT);
  return 0;
}