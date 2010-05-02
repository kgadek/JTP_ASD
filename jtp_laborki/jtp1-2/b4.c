#include <stdio.h>

void czytaj(FILE *,int,int*,int*,int*,int*);

int main(int argc, char *argv[]) {
	FILE *fn;
	int i, wyr, gcc, gwc, glc, gzc;
	gcc = gwc = glc = gzc = 0;
	/*dbg*/for(i=1;i<argc;++i) printf("%d: %s\n",i,argv[i]);
	return 0;
}

void czytaj(FILE *fn, int wyr, int *lc, int *wc, int *cc,int *zc) {
	*cc = *wc = *lc = *zc = 0;
	printf("%5d %5d %5d",*lc,*wc,*cc);
	if(wyr!=-1)
		printf(" %5d",*zc);
	printf("\n");
}

