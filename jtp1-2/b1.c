#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int N;
FILE *outf;

double rr() { /* losuj liczbe z przedzialu [-30,30] */
	return (((double)rand())/(double)RAND_MAX)*60.0f-30.0f;
}

int main(int argc, char *argv[]) {
	int i;
	if(argc!=3) {
		fprintf(stderr,"Podano zla ilosc parametrow!\n\n"\
				\
				"Wywolanie programu:\n"\
					"\t%s nazwa_pliku liczba_punktow\n",\
				argv[0]);
		exit(1);
	}
	N = atoi(argv[2]);
	if(N==0 || N==INT_MAX || N==INT_MIN) {
		fprintf(stderr,"Blad konwersji liczby! Nalezalo podac "\
				"liczbe calkowita.\n\n"\
				\
				"Wywolanie programu:\n"\
					"\t%s nazwa_pliku liczba_punktow\n",\
				argv[0]);
		exit(1);
	}
	outf = fopen(argv[1],"w");
	if(outf == NULL) {
		fprintf(stderr,"Blad pliku! Nie mozna otworzyc pliku do zapisu. "\
				"Sprobuj podac inna nazwe pliku.\n\n"\
				\
				"Wywolanie programu:\n"\
					"\t%s nazwa_pliku liczba_punktow\n",\
				argv[0]);
		exit(1);
	}
	srand((unsigned int)time(NULL));
	for(i=0;i<N;++i)
		fprintf(outf,"(%2.4f,%2.4f,%2.4f)\n",rr(),rr(),rr());
	fclose(outf);
	return 0;
}

