#include <stdio.h>

#define INTprint(_typ,_n) printf("Badany typ: " #_typ \
	" ______________________________\n" \
	"\t* rozmiar:\t\t%8d\n"\
	"\t* przykladowa wartosc:\t%8d\n"\
	"\t* binarnie:\t\t[",\
	sizeof(_typ),_n);\
	if(_n&1<<(8*sizeof(_typ)-1)) printf("1"); else printf("0"); \
	for(x=1<<(8*sizeof(_typ)-2); x>0; x>>=1)\
	printf("%d",((x&_n)>0)?1:0); printf("]\n");

#define BITEXT(_typ,_n) if(_n&1<<(8*sizeof(_typ)-1)) printf("1"); else printf("0"); \
	for(x=1<<(8*sizeof(_typ)-2); x>0; x>>=1)\
	printf("%d",((x&_n)>0)?1:0); printf("\n");

int main() {
    unsigned int y=15;
    long x;
    INTprint(unsigned int,y);
    printf("___\n");
    return 0;
}

