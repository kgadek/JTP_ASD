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
	/*dbg*/printf("rysuj\n");
	rysuj_pion(0,0,M-1,N-1,1);
	/*dbg*/printf("wyglad:\n");
	/*dbg*/for(i=0;i<N;++i) { for(j=0;j<M;++j) printf("%3d ",tab[i][j]);
	/*dbg*/	printf("\n"); }
	for(i=0;i<N;++i)
		free(tab[i]);
	free(tab);
	return 0;
}

void rysuj_pion(int x1,int y1,int x2,int y2,int s) {
	int a;
	if(x1>x2 || y1>y2)
		return;
	for(a=y1;a<=y2;++a) {
		tab[a][x1]=tab[a][x2]=s++;
	}
	rysuj_poz(x1+1,y1,x2-1,y2,s);
}

void rysuj_poz(int x1,int y1,int x2,int y2,int s) {
	int a;
	if(x1>x2 || y1>y2)
		return;
	for(a=x1;a<=x2;++a) {
		tab[y1][a]=tab[y2][a]=s++;
	}
	rysuj_pion(x1,y1+1,x2,y2-1,s);
}

