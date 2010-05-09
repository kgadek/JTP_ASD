#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/* ==========[ zmienne globalne ]========== */
int N;
FILE *outf;

/* ==========[ definicje funkcji ]========== */
double rr()
{				/* losowanie liczby z przedzialu [-30,30] */
    return (((double) rand()) / (double) RAND_MAX) * 60.0f - 30.0f;
}

/* ==========[ funkcja main ]========== */
int main(int argc, char *argv[])
{
    int i;
    /* rozpoznawanie blednych parametrow programu */
    if (argc != 3) {		/* zla ilosc parametrow */
	fprintf(stderr, "Podano zla ilosc parametrow!\n\n"
		"Wywolanie programu:\n"
		"\t%s nazwa_pliku liczba_punktow\n", argv[0]);
	exit(1);
    }
    N = atoi(argv[2]);
    if (N == 0 || N == INT_MAX || N == INT_MIN) {	/* podano bledna liczbe */
	fprintf(stderr, "Blad konwersji liczby! Nalezalo podac "
		"liczbe calkowita.\n\n"
		"Wywolanie programu:\n"
		"\t%s nazwa_pliku liczba_punktow\n", argv[0]);
	exit(1);
    }
    outf = fopen(argv[1], "w");
    if (outf == NULL) {		/* blad pliku */
	fprintf(stderr, "Blad pliku! Nie mozna otworzyc pliku do zapisu. "
		"Sprobuj podac inna nazwe pliku.\n\n"
		"Wywolanie programu:\n"
		"\t%s nazwa_pliku liczba_punktow\n", argv[0]);
	exit(1);
    }
    srand((unsigned int) time(NULL));	/* inicjacja generatora  liczb
					   pseudolosowych */
    /* czesc wlasciwa programu - wpisywanie danych do pliku */
    fprintf(outf, "%d\n", N);
    for (i = 0; i < N; ++i)
	fprintf(outf, "(%.4f,%.4f,%.4f)\n", rr(), rr(), rr());
    /* finalizowanie programu */
    fclose(outf);
    return 0;
}
