#include <stdio.h>

/* Nawet niebrzydkie makro okreslajace ilosc znakow "_" po nazwie typu */
#define SCREENSIZE 66

/* Nieco brzydkie makro do obslugi liczb calkowitych.

   Wywolanie:
   	INTTEST(_typ,_l,_fmt,_n,_v)
   gdzie:
   		_typ	- nazwa typu
		_l	- dlugosc nazwy typu
		_fmt	- format funkcji printf
		_n	- nazwa zmiennej tymczasowo przechowujacej wartosc
		_v	- przykladowa wartosc ktora badamy binarnie
   Makro wykorzystuje zmienna x, ktora powinna byc dostepna w czasie
   wywolania makra, a takze stala SCREENSIZE.
*/

#define INTTEST(_typ,_l,_fmt,_n,_v)\
    	_n=_v;\
	printf("Badany typ: " #_typ " "); \
	for(x=SCREENSIZE;x>_l;--x) printf("_");\
	printf("\n\t* rozmiar:\t\t\t%d B\n"\
	"\t* przykladowa wartosc:\t\t" _fmt "\n"\
	"\t* binarnie:\t\t\t[",\
	sizeof(_typ),_n);\
	if(_n&1<<(8*sizeof(_typ)-1)) printf("1"); else printf("0"); \
	for(x=1<<(8*sizeof(_typ)-2); x>0; x>>=1)\
	printf("%d",((x&_n)>0)?1:0); printf("]\n");

/* Bardzo brzydkie makro do obslugi liczb zmiennoprzecinkowych.

   Wywolanie:
   	FLOATTEST(_typ,_l,_fmt,_n,_v)
   gdzie:
		_typ	- nazwa typu
		_l	- dlugosc nazwy typu
		_fmt	- format funkcji printf
		_n	- nazwa zmiennej tymczasowo przechowujacej wartosc.
			  Z zalozenia zmienna ta jest w unii zp, ktora
			  jest czyszczona w kazdym ,,wywolaniu" makra, by
			  uzyskac czysta postac binarna.
		_v	- przykladowa wartosc
   Makro wykorzystuje zmienna x, ktora powinna byc dostepna w czasie
   wywolania makra, a takze stala SCREENSIZE.
*/ 
#define FLOATTEST(_typ,_l,_fmt,_n,_v)\
    	for(x=0;x<(signed)sizeof(long double);++x) zp.t[x]=0;\
	_n=_v;\
	printf("Badany typ: " #_typ " " ); \
	for(x=SCREENSIZE;x>_l;--x) printf("_");\
	printf("\n\t* rozmiar:\t\t\t%d B\n"\
	"\t* przykladowa wartosc:\t\t" _fmt "\n"\
	"\t* rozwiniecie binarne:\n\t\t[",\
	sizeof(_typ),_n);\
    	for(x=0;x<(signed)sizeof(_typ);++x)\
	printf("%d%d%d%d%d%d%d%d",(zp.t[x]&1<<7)?1:0,(zp.t[x]&1<<6)?1:0,\
		(zp.t[x]&1<<5)?1:0,(zp.t[x]&1<<4)?1:0,(zp.t[x]&1<<3)?1:0,\
		(zp.t[x]&1<<2)?1:0,(zp.t[x]&1<<1)?1:0,(zp.t[x]&1)?1:0);\
	printf("]\n");

int main() {
    /* zmienne pomocnicza */
    long x;
    /* zmienne potrzebne do wyswietlania tymczasowych wartosci
       jak i ich rozwiniec binarnych */
    short int _short;
    unsigned short int _ushort;
    int _int;
    unsigned int _uint;
    long _long;
    unsigned long _ulong;
    char _char;
    unsigned char _uchar;
    union {
	float _f;
	double _d;
	long double _ld;
	char t[sizeof(long double)];
    } zp;
    /* poczatek bloku informacyjnego dla liczb calkowitych i typu char */
/*     INTTEST(short int,9,"%d",_short,-11); */
/*     INTTEST(unsigned short int,18,"%d",_ushort,12); */
/*     INTTEST(int,3,"%d",_int,-14); */
/*     INTTEST(unsigned int,12,"%d",_uint,14); */
/*     INTTEST(long int,8,"%ld",_long,-17); */
/*     INTTEST(unsigned long int,17,"%ld",_ulong,17); */
/*     INTTEST(char,4,"%d",_char,-21); */
/*     INTTEST(unsigned char,13,"%d",_uchar,23); */
    /* poczatek bloku informacyjnego dla liczb zmiennoprzecinkowych */
/*     FLOATTEST(float,5,"%f",zp._f,-1.5f); */
     FLOATTEST(double,6,"%f",zp._d,123.456f);
/*     FLOATTEST(long double,11,"%Lf",zp._ld,4.492f); */
    return 0;
}

