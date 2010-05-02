#include <stdio.h>
#include <stdlib.h>

unsigned int N,M;
int i,j,**tab;

int main() {
	scanf("%d%d",&N,&M);
	tab=(int**)malloc(N*sizeof(int*));
	for(i=0;i<N;++i) {
		tab[i]=(int*)malloc(M*sizeof(int));
	}
	for(i=0;i<N;++i)
		free(tab[i]);
	free(tab);
	return 0;
}

