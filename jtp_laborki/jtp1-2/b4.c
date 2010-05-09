#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NaC -1000		/* duża liczba ujemna - uniknięcie ew. problemów z
				   signed char */
#define EXECPARAM "Wywolanie programu:\n\t"\
	"%s plik1 [plik2] ... [plikM] [-f znak] [plikN] ...\n"\
	"Opcje:\n\t-f X\t\t- zlicz ilosc wystapien znaku X\n",\
	argv[0]

/* ==========[ deklaracja funkcji liczacej znaki ]========== */
void czytaj(FILE *, int, int *, int *, int *, int *);


/* ==========[ funkcja main ]========== */
int main(int argc, char *argv[])
{
    FILE *fn;			/* wskaznik na plik */
    int i, j, tmp,		/* zmienne pomocnicze */
     wyr,			/* znak, ktorego czestosc wystepowania zliczamy */
     fcnt,			/* ilosc plikow, ktore odczytano */
     sh,			/* ilosc plikow podanych na wejsciu */
     maxfn,			/* dlugosc najdluzszej nazwy pliku */
     gcc, gwc, glc, gzc;	/* globalne liczniki znakow, slow, linii i
				   wyroznionego znaku */


    /* inicjacja zmiennych */
    gwc = glc = gzc = fcnt = gcc = 0;
    maxfn = 5;			/* 5 - dlugosc slowka total */
    wyr = NaC;


    /* wstepne czytanie opcji - odnalezienie opcji -f, zliczenie plikow (fcnt),
       wyznaczenie najdluzszej nazwy pliku (maxfn) */
    for (i = 1; i < argc; ++i) {

	if (strcmp("-f", argv[i]) == 0) {	/* jesli znaleziono opcje -f ... */
	    if (wyr != NaC) {	/* ... ale juz wczesniej wczytana */
		fprintf(stderr,
			"Opcje -f podano wielokrotnie\n" EXECPARAM);
		exit(1);
	    }
	    if (i + 1 < argc) {	/* ... przetworz argument -f */
		if (argv[i + 1][1] != 0) {	/* jesli podano string a nie znak  */
		    fprintf(stderr,
			    "Po opcji -f podano ciag znakow a nie znak\n"
			    EXECPARAM);
		    exit(1);
		}
		wyr = argv[i + 1][0];
		++i;
		continue;
	    } else {		/* ... popros o podanie argumentu -f */
		fprintf(stderr,
			"Nie podano znaku po opcji -f\n" EXECPARAM);
		exit(1);
	    }
	}
	/* argument nie jest ani opcja -f ani jej parametrem */
	tmp = (int) strlen(argv[i]);	/* poprawa wartosci maxfn */
	if (tmp > maxfn)
	    maxfn = tmp;

	++fcnt;			/* zwiekszenie wartosci fcnt o ile argv[i] to nie -f ani
				   jej argument */
    }


    /* sprawdzenie, czy podano jakikolwiek plik wejsciowy */
    if (fcnt < 1) {
	fprintf(stderr,
		"Nie podano zadnych plikow wejsciowych.\n" EXECPARAM);
    }
    sh = fcnt;			/* wpisanie do sh ilosci rozpatrywanych plikow wejsciowych */


    /* czesc wlasciwa - liczenie znakow */
    for (i = 1; i < argc; ++i) {	/* dla kazdego parametru... */

	if (strcmp("-f", argv[i]) == 0) {	/* jesli parametr to -f ... */
	    ++i;		/* ...to pomin -f i jego argument */
	    continue;
	}

	fn = fopen(argv[i], "r");	/* probuj otworzyc plik */

	if (fn == NULL) {	/* blad odczytu pliku */
	    fprintf(stderr, "%s - nie mozna odczytac pliku\n", argv[i]);
	    --fcnt;		/* zmniejsz licznik rozpatrzonych plikow */
	    continue;
	} else {
	    /* plik otworzono poprawnie */
	    if (sh > 1) {	/* jesli rozpatrujemy wiele plikow, to wyswietl
				   nazwe aktualnie rozpatrywanego PRZED statystyka
				   (inaczej niz wc) */
		printf("%s: ", argv[i]);
		tmp = maxfn - (int) strlen(argv[i]);	/* ladne wyrownanie */
		for (j = 0; j <= tmp; ++j)
		    printf(" ");
	    }
	    czytaj(fn, wyr, &glc, &gwc, &gcc, &gzc);	/* licz znaki */
	    fclose(fn);		/* zamknij plik */
	}
    }

    /* podsumowanie statystyk wielu plikow */
    if (fcnt > 1) {		/* ulepszenie w stosunku do wc - wyswietl podsumowanie
				   tylko jesli ilosc rozpatrzonych plikow byla wieksza
				   niz 1 */
	printf("\ntotal: ");

	tmp = maxfn - 5;	/* ladne wyrownanie */
	for (j = 0; j <= tmp; ++j)
	    printf(" ");

	printf("%5d %5d %5d", glc, gwc, gcc);
	if (wyr != NaC)
	    printf(" %5d", gzc);
	printf("\n");
    }
    return 0;
}



/* ==========[ definicja funkcji liczacej znaki ]========== */
void czytaj(FILE * fn, int wyr, int *glc, int *gwc, int *gcc, int *gzc)
{
    int lc, wc, cc, zc,		/* liczniki: linii, slow, znakow, znakow X */
     c,				/* zmienna pomocnicza */
     word;			/* znacznik rozpatrywania slowa */

    /* inicjacja zmiennych */
    lc = wc = cc = zc = word = 0;

    /* glowna petla */
    while ((c = fgetc(fn)) != EOF) {
	++cc;			/* policz znak (tak jak wc) */
	if (c == wyr)		/* jesli wczytany znak == znakowi X to zwieksz licznik */
	    ++zc;

	switch (c) {
	case 10:		/* \n - zwieksz licznik nowej linii */
	    ++lc;
	    word = 0;		/* konczy slowo */
	    break;
	case 13:		/* \r  - obsluga windowsowego/macowego CR */
	    word = 0;		/* konczy slowo */
	    break;
	case 9:			/* tab */
	case 32:		/* spacja */
	    word = 0;		/* oba koncza slowo */
	    break;
	default:
	    if (!word) {	/* jesli poczatek slowa... */
		word = 1;
		++wc;		/* ...to je zlicz */
	    }
	}
    }

    /* wyswietlenie statystyk */
    printf("%5d %5d %5d", lc, wc, cc);
    if (wyr != NaC)		/* jesli trzeba, uwzglednij ilosc wystapien znaku X */
	printf(" %5d", zc);
    printf("\n");

    /* popraw liczniki ogolne przekazane przez referencje */
    *glc += lc;
    *gwc += wc;
    *gcc += cc;
    *gzc += zc;
}
