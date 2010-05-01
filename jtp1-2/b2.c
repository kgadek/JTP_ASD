#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

FILE *outf;
double *x,*y,*z,**tab,max,tmp;

double odl(int id_1, int id_2) {
	tmp = sqrt((x[id_1]-x[id_2])*(x[id_1]-x[id_2])+(y[id_1]-y[id_2])*(y[id_1]-y[id_2])+(z[id_1]-z[id_2])*(z[id_1]-z[id_2]));
	max=MAX(max,tmp);
	return tmp;
}

int main(int argc, char *argv[]) {
	int i,j,N;
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
	x = (double *)malloc((unsigned int)N*sizeof(double));
	y = (double *)malloc((unsigned int)N*sizeof(double));
	z = (double *)malloc((unsigned int)N*sizeof(double));
	tab = (double **)malloc((unsigned int)N*sizeof(double*));
	if(x==NULL || y==NULL|| z==NULL || tab==NULL) {
		fprintf(stderr,"Blad alokacji pamieci!\n");
		if(x)
			free(x);
		if(y)
			free(y);
		if(z)
			free(z);
		if(tab)
			free(tab);
		fclose(outf);
		exit(1);
	}
	for(i=0;i<N;++i) {
		(tab[i]) = (double*)calloc((size_t)N,(size_t)sizeof(double));
		fscanf(outf," (%lf,%lf,%lf) ",x+i,y+i,z+i);
	}
	for(i=0;i<N;++i) {
		for(j=i+1;j<N;++j) {
			tab[i][j]=tab[j][i]=odl(i,j);
		}
	}
	/*dbgfor(i=0;i<N;++i)for(j=0;j<N;++j) printf("[%d][%d]=%f\n",i,j,tab[i][j]);*/
	printf("%f\n",max);
	fclose(outf);
	free(x);
	free(y);
	free(z);
	for(i=0;i<N;++i)
		free(tab[i]);
	free(tab);
	return 0;
}

