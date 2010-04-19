#include <stdio.h>
#include <stdlib.h>

FILE *outf;

int main(int argc, char *argv[]) {
	if(argc!=2) {
		fprintf(stderr,"Podano zla ilosc parametrow!\n\n"\
				\
				"Wywolanie programu:\n"\
					"\t%s nazwa_pliku\n",\
				argv[0]);
		exit(1);
	}
	outf = fopen(argv[1],"r");
	if(outf == NULL) {
		fprintf(stderr,"Blad pliku! Nie mozna otworzyc pliku do czytania. "\
				"Sprobuj podac\ninna nazwe pliku.\n\n"\
				\
				"Wywolanie programu:\n"\
					"\t%s nazwa_pliku\n",\
				argv[0]);
		exit(1);
	}
	fclose(outf);
	return 0;
}

