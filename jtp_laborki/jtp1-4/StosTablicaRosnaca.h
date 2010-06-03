#ifndef _STOS_TABLICA_ROSNACA
#define _STOS_TABLICA_ROSNACA

#include "StosTablica.h"

class StosTablicaRosnaca : public StosTablica {
protected:
	unsigned int step;
public:
	StosTablicaRosnaca(unsigned int const _size=100, unsigned int const _step=100);
	StosTablicaRosnaca(StosTablica const &, unsigned int const _step);
	StosTablicaRosnaca(StosTablicaRosnaca const &);
	void push(char);
	StosTablicaRosnaca& operator=(StosTablicaRosnaca const &);
};


#endif
