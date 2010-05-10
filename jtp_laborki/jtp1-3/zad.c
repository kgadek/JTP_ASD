#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABSIZE 101		/* 100 cyfr + 1 przeniesienie */
#define SHOWPARAM "Wywolanie:\n\t%s plik_wejsciowy\n",argv[0]
#define GET(arr,el) (((el)>=0)?(arr)[el]:0)

char a[TABSIZE], b[TABSIZE], c[TABSIZE],	/* odpowiednio: tablica
						   wejsciowa A, wejsciowa B,
						   wyjsciowa*/
     r;						/* reszta z dodawania (overflow) */
int i,
    la, lb, lm;					/* dlugosc A, dlugosc B, maksimum dlugosci
   						   z A i B */

int parse(char *, int *);			/* przetworz wejscie do odpowiedniego
						   formatu (kody 0-15)*/

int main(int argc, char **argv)
{
    FILE *fn;
    if (argc != 2) {
	fprintf(stderr, "Nie podano pliku wejsciowego!\n" SHOWPARAM);
	exit(1);
    }
    fn = fopen(argv[1], "r");
    if (!fn) {
	fprintf(stderr, "Nie mozna otworzyc podanego pliku!\n" SHOWPARAM);
	exit(1);
    }
    for (i = 0; i < TABSIZE; ++i)
	a[i] = b[i] = 0;
    fscanf(fn, " %s %s ", a, b);
    if (parse(a, &la) || parse(b, &lb) || !la || !lb) {	/* obsluga bledow:
   							   - bledu parsowania (zly format),
							   - braku jednej/obu liczb */
	fprintf(stderr, "Dane wejsciowe sa niepoprawne!\n" SHOWPARAM);
	fclose(fn);
	exit(1);
    }
    lm = la > lb ? la : lb;
    r = 0;
    for (i = TABSIZE - 1; (i > -1) && (TABSIZE-i-1<lm || r); --i) {
			/* petla iteruje od ostatniego elementu i przerywa dzialanie
			   gdy:
			     tablica jest wypelniona
			   albo
			     juz nie ma nic do dodania */
	--la;
	--lb;
	c[i] = (char) (GET(a, la) + GET(b, lb) + r);	/* makro pozwala ukryc IF-y*/
	if (c[i] > 15) {		/* obsluga overflow */
	    r = 1;
	    c[i] = (char) (c[i] - 16);
	} else
	    r = 0;
	if (c[i] > 9)
	    c[i] = (char) (c[i] + 87);	/* wynik z zakresu a-f */
	else
	    c[i] = (char) (c[i] + 48);	/* wynik z zakresu 0-9 */
    }
    for (i = 0; c[i]=='0'; ++i);
    for (; i < TABSIZE; ++i)
	printf("%c", (char) c[i]);
    printf("\n");
    fclose(fn);
    return 0;
}

int parse(char *tab, int *len)
{
    for ((*len) = 0; tab[*len]; ++(*len)) {
	if (47 < tab[*len] && tab[*len] < 58)	/* cyfra 0-9 */
	    tab[*len] = (char) (tab[*len] - 48);
	else if (64 < tab[*len] && tab[*len] < 71)	/* znak A-F */
	    tab[*len] = (char) (tab[*len] - 65 + 10);
	else if (96 < tab[*len] && tab[*len] < 103)	/* znak a-f */
	    tab[*len] = (char) (tab[*len] - 97 + 10);
	else
	    return 1;
    }
    return 0;
}
