#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ==========[ makra ]========== */
#define MAX(a,b) ((a)>(b)?(a):(b))

/* ==========[ zmienne globalne ]========== */
FILE *outf;
double *x, *y, *z, **tab, tmp;
int max;

/* ==========[ definicje funkcji ]========== */
double odl(int id_1, int id_2)
{
    return sqrt((x[id_1] - x[id_2]) * (x[id_1] - x[id_2]) +
		(y[id_1] - y[id_2]) * (y[id_1] - y[id_2]) + (z[id_1] -
							     z[id_2]) *
		(z[id_1] - z[id_2]));
}


/* ==========[ funkcja main ]========== */
int main(int argc, char *argv[])
{
    int i, j, N;
    /* sprawdzanie przekazanych argumentow */
    if (argc != 2) {		/* zla ilosc argumentow */
	fprintf(stderr, "Podano zla ilosc parametrow!\n\n"
		"Wywolanie programu:\n" "\t%s nazwa_pliku\n", argv[0]);
	exit(1);
    }
    outf = fopen(argv[1], "r");
    if (outf == NULL) {		/* blad dostepu do pliku */
	fprintf(stderr,
		"Blad pliku! Nie mozna otworzyc pliku do czytania. "
		"Sprobuj podac\ninna nazwe pliku.\n\n"
		"Wywolanie programu:\n" "\t%s nazwa_pliku\n", argv[0]);
	exit(1);
    }

    /* czesc wlasciwa programu */
    fscanf(outf, "%d", &N);	/* wczytanie pierwszej linii */
    /* alokacja pamieci---------- */
    x = (double *) malloc((unsigned int) N * sizeof(double));
    y = (double *) malloc((unsigned int) N * sizeof(double));
    z = (double *) malloc((unsigned int) N * sizeof(double));
    tab = (double **) malloc((unsigned int) N * sizeof(double *));
    /* obsluga bledow alokacji pamieci---------- */
    if (x == NULL || y == NULL || z == NULL || tab == NULL) {
	fprintf(stderr, "Blad alokacji pamieci!\n");
	if (x)
	    free(x);
	if (y)
	    free(y);
	if (z)
	    free(z);
	if (tab)
	    free(tab);
	fclose(outf);
	exit(1);
    }
    /* * ciag dalszy alokacji - alokacja tablicy  dwuwymiarowej
     * obsluga bledow
     * wczytywanie wartosci z pliku */
    for (i = 0; i < N; ++i) {
	(tab[i]) = (double *) calloc((size_t) N, (size_t) sizeof(double));
	if (tab[i] == NULL) {
	    fprintf(stderr, "Blad alokacji pamieci!\n");
	    for (j = 0; j < i; ++j)
		free(tab[j]);
	    if (x)
		free(x);
	    if (y)
		free(y);
	    if (z)
		free(z);
	    if (tab)
		free(tab);
	    fclose(outf);
	    exit(1);
	}
	fscanf(outf, " (%lf,%lf,%lf) ", x + i, y + i, z + i);
    }
    /* wyznaczenie odleglosci miedzy punktami */
    for (i = 0; i < N; ++i) {
	for (j = i + 1; j < N; ++j) {	/* mala optymalizacja */
	    tab[i][j] = tab[j][i] = odl(i, j);
	}
    }
    for (i = max = 0; i < N; ++i) {
	for (j = 1; j < N; ++j) {
	    tab[i][0] += tab[i][j];
	}
	if (tab[i][0] > tab[max][0])
	    max = i;
    }
    printf("(%f,%f,%f)\n", x[max], y[max], z[max]);	/* wypisanie wyniku */

    /* zamkniecie pliku, czyszczenie pamieci, zakonczenie programu */
    fclose(outf);
    free(x);
    free(y);
    free(z);
    for (i = 0; i < N; ++i)
	free(tab[i]);
    free(tab);
    return 0;
}
