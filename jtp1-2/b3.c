#include <stdio.h>
#include <stdlib.h>

int N,M,**tab;

void rysuj_pion(int,int,int,int,int);
void rysuj_poz(int,int,int,int,int);

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
	rysuj_pion(0,0,M-1,N-1,1);
	for(i=0;i<N;++i) {
		for(j=0;j<M;++j)
			printf("%3d ",tab[i][j]);
		printf("\n");
	}
	for(i=0;i<N;++i)
		free(tab[i]);
	free(tab);
	return 0;
}

void rysuj_pion(int x1,int y1,int x2,int y2,int s) {
	if(x1>x2 || y1>y2)
		return;
	rysuj_poz(x1+1,y1,x2-1,y2,s+y2-y1+1);
	for(;y1<=y2;++y1) {
		tab[y1][x1]=tab[y1][x2]=s++;
	}
}

void rysuj_poz(int x1,int y1,int x2,int y2,int s) {
	if(x1>x2 || y1>y2)
		return;
	rysuj_pion(x1,y1+1,x2,y2-1,s+x2-x1+1);
	for(;x1<=x2;++x1) {
		tab[y1][x1]=tab[y2][x1]=s++;
	}
}

