#include <stdio.h>
#include <stdlib.h>

FILE *outf;

int main(int argc, char *argv[]) {
	int i,N;
	double a,b,c;
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
	fscanf(outf,"%d",&N);
	for(i=0;i<N;++i) {
		fscanf(outf," (%lf,%lf,%lf) ",&a,&b,&c);
		/* printf("Wczytalem %f %f %f\n",a,b,c); */
	}
	fclose(outf);
	return 0;
}

