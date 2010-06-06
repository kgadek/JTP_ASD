#ifndef _STOS_TABLICA_ROSNACA
#define _STOS_TABLICA_ROSNACA

#include "StosTablica.h"

class StosTablicaRosnaca : public StosTablica {
protected:
	unsigned int step;
public:
	StosTablicaRosnaca(unsigned int const _size=100, unsigned int const _step=100);
				/* domyslny konstuktor */
	StosTablicaRosnaca(StosTablica const &, unsigned int const _step=100);
				/* konstruktor kopiujacy z klasy dziedziczonej */
	StosTablicaRosnaca(StosTablicaRosnaca const &);
				/* konstruktor kopiujacy */
	void push(char);	/* specjalizowana funkcja wrzucajaca na stos */
	StosTablicaRosnaca& operator=(StosTablicaRosnaca const &);
				/* operator przypisania (kopiujacy) */
};


#endif
