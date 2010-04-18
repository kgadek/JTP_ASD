#include <stdio.h>

#define INTprint(_typ) printf("Badany typ: " #_typ \
	" ______________________________\n"\
	"\t* rozmiar: %d\n",sizeof(_typ))
#define BITSEXT(_typ,_n) for(x=1<<(8*sizeof(_typ)-2); x>0; x>>=1)\
	printf("%d",((x&_n)>0)?1:0); printf("\n");
#define BITUEXT(_typ,_n) for(x=1<<(8*sizeof(_typ)-1); x>0; x>>=1)\
	printf("%d",((x&_n)>0)?1:0); printf("\n");

int main() {
    int y=15;
    unsigned yu=15;
    long x;
    INTprint(int);
    BITSEXT(int,y);
    printf("___\n");
    BITUEXT(unsigned int,yu)
    return 0;
}

