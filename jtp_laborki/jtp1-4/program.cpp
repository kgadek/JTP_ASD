#include "StosTablica.h"
#include "StosTablicaRosnaca.h"
#include <cstdio>
#include <cassert>

/*
Do obslugi alokacji pamieci wykorzystalem alloc/realloc/free, gdyz:
	- malloc nie inicjuje pamieci, wiec konstruktory klas dzialaja
	  w czasie O(1) (new wywoluje konstruktor domyslny przy tworzeniu
	  tablic (zrodlo: http://en.wikipedia.org/wiki/New_(C%2B%2B) ))
 	- realloc, w optymistycznym przypadku, pozwala na szybsze (O(1))
	  zwiekszenie rozmiaru przydzielonej pamieci w procedurze push
	  klasy StosTablicaRosnaca
Podane czasy pomijaja czas na sama alokacje pamieci.
*/

int main() {
	{
	printf("start StosTablica test\n");
	printf("\ttest a\n"); //===================
	StosTablica sta;
	assert( sta.empty() );
	assert( !sta.full() );
	sta.push('a'); sta.push('b'); sta.push('c');
	sta.push('d'); sta.push('e'); sta.push('f');
	sta.push('g'); sta.push('h'); sta.push('i');
	assert( !sta.empty() );
	assert( !sta.full() );

	printf("\ttest b\n"); //===================
	StosTablica stb(sta);
	assert( !stb.empty() );
	assert( !stb.full() );
	stb.push('a'); sta.push('b'); sta.push('c');
	stb.push('d'); sta.push('e'); sta.push('f');
	stb.push('g'); sta.push('h'); sta.push('i');
	assert( !stb.empty() );
	assert( !stb.full() );

	printf("\ttest c\n"); //===================
	StosTablica stc1(5);
	stc1.push('a'); stc1.push('a'); stc1.push('a');
	StosTablica stc2(stc1);
	assert( !stc2.empty() );
	assert( !stc2.full() );
	stc2.push('b'); stc2.push('b');
	assert( !stc2.empty() );
	assert( stc2.full() );
	assert( stc2.pop() == 'b' );
	assert( !stc2.full() );
	assert( stc2.pop() == 'b' );
	assert( stc2.pop() == 'a' );
	assert( stc2.pop() == 'a' );
	assert( stc2.pop() == 'a' );
	assert( stc2.empty() );
	assert( !stc2.full() );

	printf("\ttest d\n"); //===================
	StosTablica std(0);
	assert( std.empty() );
	assert( std.full() );

	printf("\ttest e\n"); //===================
	StosTablica ste1(5);
	ste1.push('a'); ste1.push('a'); ste1.push('a');
	StosTablica ste2(0);
	ste2 = ste1;
	assert( !ste2.empty() );
	assert( !ste2.full() );
	ste2.push('b'); ste2.push('b');
	assert( ste2.full() );
	assert( ste2.pop() == 'b' );
	assert( ste2.pop() == 'b' );
	assert( ste2.pop() == 'a' );
	assert( ste2.pop() == 'a' );
	assert( ste2.pop() == 'a' );
	assert( ste2.empty() );

	printf("\ttest f\n"); //===================
	StosTablica stf1(3);
	stf1.push('a'); stf1.push('a'); stf1.push('a');
	assert( stf1.full() );
	StosTablica stf2(100);
	stf2 = stf1;
	assert( !stf2.empty() );
	assert( stf2.full() );
	printf("end StosTablica test\n");
	}



	{
	printf("start StosTablicaRosnaca test\n");
	printf("\ttest a\n"); //===================
	StosTablicaRosnaca stra(3,0);
	assert( stra.empty() );
	assert( !stra.full() );
	stra.push('a'); stra.push('a'); stra.push('a');
	// stra.push('a'); // to (poprawnie) wyrzuca blad
	assert( !stra.empty() );
	assert( stra.full() );

	printf("\ttest b\n"); //===================
	StosTablicaRosnaca strb1(3,10);
	strb1.push('a'); strb1.push('a'); strb1.push('a');
	strb1.push('a'); strb1.push('a'); strb1.push('a');
	strb1.push('a'); strb1.push('a'); strb1.push('a');
	strb1.push('a'); strb1.push('a'); strb1.push('a');
	strb1.push('a');
	assert( strb1.full() );
	strb1.push('a'); strb1.push('a'); strb1.push('a');
	assert( !strb1.full() );
	assert( strb1.pop() == 'a' );
	StosTablicaRosnaca strb2(2,100);
	strb2 = strb1;
	assert( !strb2.empty() );
	assert( !strb2.full() );
	assert( strb2.pop() == 'a' );
	assert( strb2.pop() == 'a' );
	assert( strb2.pop() == 'a' );
	StosTablicaRosnaca strb3(200,100);
	strb3 = strb1;
	assert( !strb3.empty() );
	assert( !strb3.full() );

	printf("\ttest c\n"); //===================
	StosTablicaRosnaca strc1;
	strc1.push('a'); strc1.push('a'); strc1.push('a');
	strc1.push('a'); strc1.push('a'); strc1.push('a');
	StosTablicaRosnaca strc2(strc1);
	assert( !strc2.empty() );
	assert( strc2.pop() == 'a' );
	StosTablica stc1;
	stc1.push('b');
	StosTablicaRosnaca strc3(stc1,10);
	assert( !strc3.empty() );
	assert( strc3.pop() == 'b' );
	assert( strc3.empty() );
	StosTablicaRosnaca strc4(3,20);
	strc4.push('c'); strc4.push('c'); strc4.push('c');
	strc4.push('c'); strc4.push('c'); strc4.push('c');
	strc4 = stc1;
	assert( strc4.pop() == 'b');
	assert( strc4.empty() );
	printf("end StosTablicaRosnaca test\n");
	}

	return 0;
}

