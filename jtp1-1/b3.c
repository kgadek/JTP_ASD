#include <stdio.h>

/* Stala okreslajaca ilosc znakow "_" do wyswietlenia po nazwie typu */
#define SCREENSIZE 66

/* Sposob wyswietlania postaci binarnej. Zalezny od dwoch czynnikow:
   sposobu kodowania na danej architekturze (bit-/little-endian) i
   od tego, czy chcemy otrzymac postac binarna liczby
   (zmiennoprzecinkowe: IEEE 754) czy postac, w jakiej liczba jest
   zapisana w komputerze. Wartosci, jakie nalezy nadac BINDISP
   opisuje ponizsza tabelka:
   
   BINDISP       || IEEE 754 | postac w komputerze
   ==============++==========+====================
   big-endian    ||     0    |          1
   ==============++----------+--------------------
   little-endian ||     1    |          0
*/
#define BINDISP 1

/* Bardzo brzydkie makro (makra) testujace typy danych.
   Wywolanie:
		TEST(_typ,_l,_fmt,_n,_v)
   gdzie:
		_typ	- nazwa typu
		_l		- dlugosc nazwy typu
		_fmt	- format dla funkcji printf
		_n		- nazwa zmiennej tymczasowo przechowujacej wartosc
		_v		- przykladowa wartosc
   Makro wykorzystuje zmienna x, ktora powinna byc dostepna w czasie
   wywolania makra, a takze stala SCREENSIZE. Wyswietlanie wartosci
   binarnej zalezy od wartosci zmiennej BINDISP (patrz: wyzej).
   Zawartosc unii un jest za kazdym razem czyszczona by nie dopuscic
   do wyswietlenia blednej postaci binarnej.
*/ 
#if BINDISP==0
#define LOOP(_typ) for(x=0;x<(signed)sizeof(_typ);++x)
#define BINDISPN "doslownie"
#else
#define LOOP(_typ) for(x=(signed)sizeof(_typ)-1;x>=0;--x)
#define BINDISPN "normalnie"
#endif
#define TEST(_typ,_l,_fmt,_n,_v)\
	for(x=0;x<(signed)sizeof(long double);++x) un.t[x]=0;\
	_n=_v;\
	printf("Badany typ: " #_typ " " ); \
	for(x=SCREENSIZE;x>_l;--x) printf("_");\
	printf("\n\t* rozmiar:\t\t\t%d B\n"\
	"\t* przykladowa wartosc:\t\t" _fmt "\n"\
	"\t* binarnie (" BINDISPN "):\t\t",\
	sizeof(_typ),_n);\
	LOOP(_typ)\
	printf("%d%d%d%d%d%d%d%d",(un.t[x]&1<<7)?1:0,(un.t[x]&1<<6)?1:0,\
		(un.t[x]&1<<5)?1:0,(un.t[x]&1<<4)?1:0,(un.t[x]&1<<3)?1:0,\
		(un.t[x]&1<<2)?1:0,(un.t[x]&1<<1)?1:0,(un.t[x]&1)?1:0);\
	printf("\n");

int main() {
	/* zmienne pomocnicza */
	long x;
	/* zmienne potrzebne do wyswietlania tymczasowych wartosci
	   jak i ich rozwiniec binarnych */
	union {
		short int _short;
		unsigned short int _ushort;
		int _int;
		unsigned int _uint;
		long _long;
		unsigned long _ulong;
		char _char;
		unsigned char _uchar;
		float _f;
		double _d;
		long double _ld;
		char t[sizeof(long double)]; /* long double jest najwieksze */
	} un;
	/* poczatek bloku informacyjnego dla liczb calkowitych i typu char */
	TEST(short int,9,"%d",un._short,-11);
	TEST(unsigned short int,18,"%d",un._ushort,12);
	TEST(int,3,"%d",un._int,-14);
	TEST(unsigned int,12,"%d",un._uint,14);
	TEST(long int,8,"%ld",un._long,-17);
	TEST(unsigned long int,17,"%ld",un._ulong,17);
	TEST(char,4,"%d",un._char,-21);
	TEST(unsigned char,13,"%d",un._uchar,23);
	/* poczatek bloku informacyjnego dla liczb zmiennoprzecinkowych */
	TEST(float,5,"%f",un._f,-1.5f);
	TEST(double,6,"%f",un._d,123.456f);
	TEST(long double,11,"%Lf",un._ld,4.492f);
	return 0;
}

