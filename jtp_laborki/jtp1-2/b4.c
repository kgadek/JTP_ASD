#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void czytaj(FILE *,int,int*,int*,int*,int*);

int main(int argc, char *argv[]) {
	FILE *fn;
	int i, j, tmp, wyr, fcnt, maxfn, sh,
		gcc, gwc, glc, gzc;			/* globalne liczniki znakow, slow, linii i
									   wyroznionego znaku */
	gwc = glc = gzc = fcnt = gcc = 0;
	maxfn = 5;		/* 5 - dlugosc slowka total */
	wyr = -1;
					/* tu gcc uzywamy jako zmienna pomocnicza */
	for(i=1;i<argc;++i) {
		if(strcmp("-f",argv[i])==0) {
			if(i+1<argc) {
				wyr=argv[i+1][0];
				++i;
				continue;
			} else {
				fprintf(stderr,"Nie podano znaku po opcji -f\n"\
						"Wywolanie programu:\n\t"\
			   			"%s plik1 [plik2] ... [plikM] [-f znak] [plikN] ...\n"\
						"Opcje:\n\t"\
						"-f X\t\t- zlicz ilosc wystapien znaku X\n",
						argv[0]);
				exit(1);
			}
		}
		tmp = (int)strlen(argv[i]);
		if(tmp>maxfn)
			maxfn = tmp;
		++fcnt;
	}
	if(fcnt<1) {
		fprintf(stderr,"Nie podano zadnych plikow wejsciowych.\n\n"\
				"Wywolanie programu:\n\t"\
			   	"%s plik1 [plik2] ... [plikM] [-f znak] [plikN] ...\n"\
				"Opcje:\n\t"\
				"-f X\t\t- zlicz ilosc wystapien znaku X\n",
				argv[0]);
		exit(1);
	}
	sh = fcnt;
	for(i=1;i<argc;++i) {
		if(strcmp("-f",argv[i])==0) {
			++i;		/* pomin opcje -f i jej argument */
			continue;
		}
		fn = fopen(argv[i],"r");
		if(fn == NULL ) {
			fprintf(stderr,"%s - nie mozna odczytac pliku\n",argv[i]);
			--fcnt;
			continue;
		} else {
			if(sh>1) {
				printf("%s: ",argv[i]);
				tmp=maxfn-(int)strlen(argv[i]);
				for(j=0;j<=tmp;++j)
					printf(" ");
			}
			czytaj(fn,wyr,&gcc,&gwc,&gcc,&gzc);
			fclose(fn);
		}
	}
	if(fcnt>1) {		/* ulepszenie w stosunku do wc - wyswietl podsumowanie
						   tylko jesli ilosc odczytanych plikow byla wieksza
						   niz 1 */
		printf("\ntotal: ");
		tmp=maxfn-5;
		for(j=0;j<=tmp;++j)
			printf(" ");
		printf("%5d %5d %5d",glc,gwc,gcc);
		if(wyr!=-1)
			printf(" %5d",gzc);
		printf("\n");
	}
	return 0;
}

void czytaj(FILE *fn, int wyr, int *glc, int *gwc, int *gcc,int *gzc) {
	int lc,wc,cc,zc,c,word;
	lc = wc = cc = zc = word = 0;
	while( (c = fgetc(fn)) !=  EOF) {
		if(c==wyr)
			++zc;
		switch(c) {
			case 10:		/* \n */
				++lc;
				++cc;
				word = 0;
				break;
			case 13:		/* \r 		 uwaga: nie zadziala dobrze na MacOS */
				break;
			case 11:		/* tab */
			case 32:		/* spacja */
				++cc;
				word = 0;
				break;
			default:
				if(!word) {
					word = 1;
					++wc;
				}
				++cc;
		}
	}
	printf("%5d %5d %5d",lc,wc,cc);
	if(wyr!=-1)
		printf(" %5d",zc);
	printf("\n");
	*glc += lc;
	*gwc += wc;
	*gcc += cc;
	*gzc += zc;
}

