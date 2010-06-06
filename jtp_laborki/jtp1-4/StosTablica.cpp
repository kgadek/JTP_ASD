#include "StosTablica.h"
#include <cstdlib>
#include <cassert>


StosTablica::StosTablica(unsigned int const _size) :
			ptr(NULL), size(_size), used(0) {
	ptr = (char*)malloc(size*sizeof(char));
	assert( ptr != NULL );
}

StosTablica::StosTablica(StosTablica const &x) :
			ptr(NULL), size(x.size), used(0) {
	ptr = (char*)malloc(size*sizeof(char));
	assert( ptr != NULL );
	for(;used<x.used;++used)
		ptr[used] = x.ptr[used];
}

StosTablica::~StosTablica() {
	free(ptr);
}

StosTablica& StosTablica::operator=(StosTablica const &x) {
	size = x.size;
	free(ptr);
	ptr = (char*)malloc(size*sizeof(char));
	assert( ptr != NULL );
	for(used = 0; used<x.used;++used)
		ptr[used] = x.ptr[used];
	return *this;
}

void StosTablica::push(char x) {
	assert( used < size );
	ptr[used++] = x;
}

char StosTablica::pop() {
	assert( used > 0 );
	return ptr[--used];
}

bool StosTablica::empty() const {
	return used == 0;
}

bool StosTablica::full() const {
	return used == size;
}

