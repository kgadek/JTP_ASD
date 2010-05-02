#include <stdio.h>
#include <stdlib.h>

int N,M,**tab;

void rysuj(int,int,int,int,int,int);

int main() {
	int i,j;
	scanf("%d%d",&N,&M);
	tab=(int**)malloc((unsigned int)N*sizeof(int*));
	if(tab==NULL) {
		fprintf(stderr,"Blad alokacji pamieci!\n");
		free(tab);
		exit(1);
	}
	for(i=0;i<N;++i) {
		tab[i]=(int*)malloc((unsigned int)M*sizeof(int));
		if(tab[i]==NULL) {
			fprintf(stderr,"Blad alokacji pamieci!\n");
			for(j=0;j<i;++j)
				free(tab[j]);
			free(tab);
			exit(1);
		}
	}
	for(i=0;i<N;++i)
		free(tab[i]);
	free(tab);
	return 0;
}

void rysuj(int x1,int y1,int x2,int y2,int s,int stx) {
}

