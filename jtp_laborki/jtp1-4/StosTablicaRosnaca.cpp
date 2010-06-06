#include "StosTablicaRosnaca.h"
#include <cstdlib>
#include <cassert>

StosTablicaRosnaca::StosTablicaRosnaca(unsigned int const _size, unsigned int const _step) :
			StosTablica(_size), step(_step) { }

StosTablicaRosnaca::StosTablicaRosnaca(StosTablica const &x, unsigned int const _step) :
			StosTablica(x), step(_step) {
}

StosTablicaRosnaca::StosTablicaRosnaca(StosTablicaRosnaca const &x) :
			StosTablica(x.size), step(x.step) {
	used = 0;
	for(;used<x.used;++used)
		ptr[used] = x.ptr[used];
}

void StosTablicaRosnaca::push(char x) {
	if(used == size) {
		ptr = (char*)realloc(ptr,(size+=step)*sizeof(char));
		assert( ptr != NULL );
		assert( used < size );
	}
	ptr[used++] = x;
}

StosTablicaRosnaca& StosTablicaRosnaca::operator=(StosTablicaRosnaca const &x) {
	size = x.size; step = x.step;
	free(ptr);
	ptr = (char*)malloc(size*sizeof(char));
	for(used = 0; used<x.used;++used)
		ptr[used] = x.ptr[used];
	assert( ptr != NULL );
	return *this;
}

