#include <stdio.h>

#define INTTEST(_typ,_fmt,_n,_v) _n=_v; printf("Badany typ: " #_typ \
	" ____________________________________________________\n" \
	"\t* rozmiar:\t\t\t%d B\n"\
	"\t* przykladowa wartosc:\t\t" _fmt "\n"\
	"\t* binarnie:\t\t\t[",\
	sizeof(_typ),_n);\
	if(_n&1<<(8*sizeof(_typ)-1)) printf("1"); else printf("0"); \
	for(x=1<<(8*sizeof(_typ)-2); x>0; x>>=1)\
	printf("%d",((x&_n)>0)?1:0); printf("]\n");

#define BITEXT(_typ,_n) if(_n&1<<(8*sizeof(_typ)-1)) printf("1"); else printf("0"); \
	for(x=1<<(8*sizeof(_typ)-2); x>0; x>>=1)\
	printf("%d",((x&_n)>0)?1:0); printf("\n");

int main() {
    long x;
    short int _short;
    unsigned short int _ushort;
    int _int;
    unsigned int _uint;
    long _long;
    unsigned long _ulong;
    char _char;
    unsigned char _uchar;
    INTTEST(short int,"%d",_short,-11);
    INTTEST(unsigned short int,"%d",_ushort,11);
    INTTEST(int,"%d",_int,-14);
    INTTEST(unsigned int,"%d",_uint,14);
    INTTEST(long int,"%ld",_long,-17);
    INTTEST(unsigned long int,"%ld",_ulong,17);
    INTTEST(char,"%d",_char,-21);
    INTTEST(unsigned char,"%d",_uchar,23);
    return 0;
}

