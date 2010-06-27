/**
* @file tests.cpp
* Testy implementacji stosu i listy.
* @see kpfp::kpfpExc
* @see kpfp::Stos
* @see kpfp::Lista
*/

#include <iostream>
#include <iomanip>
#include <cassert>
#include "lista.h"
#include "stos.h"
using namespace std;
using namespace kpfp;

/**
* Program testuj±cy.
*/
int main() {
	ios_base::sync_with_stdio(0);
	int i;
	// ================================================================================
	cout << setiosflags(ios::left) << setw(60) << "Lista...";
	Lista<int> l1;
	l1.push_back(4); l1.push_back(5); l1.push_back(6); l1.push_back(-1000);
	l1.push_front(3); l1.push_front(2); l1.push_front(1); l1.push_front(0);
	l1.back() = 7;
	Lista<int> l2(l1);
	for(i=0;i<8;++i) {
		assert(!l1.empty());
		assert(!l2.empty());
		assert(l1.front() == i);
		assert(l2.back() == 7-i);
		l1.pop_front();
		l2.pop_back();
	}
	assert(l1.empty() && l2.empty());
	cout << "[ OK ]\n";
	// ================================================================================
	cout << setw(60) << "StosTablica...";
	StosTablica<int> st1(8);
	st1.push(7); st1.push(6); st1.push(5); st1.push(4);
	StosTablica<int> st2(st1);
	st1.push(3); st1.push(2); st1.push(1); st1.push(0);
	st2 = st1;
	assert(st1.full());
	assert(st2.full());
	for(i=0;i<8;++i) {
		assert(!st1.empty());
		assert((bool)st1);
		assert(!st2.empty());
		assert((bool)st2);
		assert(st1.front() == i);
		assert(st1.front() == st2.front());
		st1.pop();
		st2.pop();
	}
	assert(st1.empty());
	assert(st2.empty());
	assert(!(bool)st1);
	assert(!(bool)st2);
	cout << "[ OK ]\n";
	// ================================================================================
	cout << setw(60) << "StosTablicaRosnaca...";
	StosTablicaRosnaca<int> str1(8,2);
	str1.push(11); str1.push(10); str1.push(9); str1.push(8);
	str1.push(7); str1.push(6); str1.push(5); str1.push(4);
	str1.push(3); str1.push(2); str1.push(1); str1.push(0);
	StosTablicaRosnaca<int> str2(st1,1);
	str2.push(3); str2.push(2); str2.push(1); str2.push(0);
	str2 = str1;
	assert(!str1.full());
	assert(!str2.full());
	for(i=0;i<12;++i) {
		assert(!str1.empty());
		assert((bool)str1);
		assert(!str2.empty());
		assert((bool)str2);
		assert(str1.front() == i);
		assert(str1.front() == str2.front());
		str1.pop();
		str2.pop();
	}
	assert(str1.empty());
	assert(str2.empty());
	assert(!str1);
	assert(!str2);
	StosTablica<int> st3;
	st3.push(3); st3.push(2); st3.push(1); st3.push(0);
	str2 = st3;
	assert(str2);
	for(i=0;i<4;++i) {
		assert(str2.front() == i);
		str2.pop();
	}
	assert(!str2);
	StosTablicaRosnaca<int> str3(2,0);
	str3.push(1); str3.push(0);
	assert(str3.full());
	cout << "[ OK ]\n";
	// ================================================================================
	cout << setw(60) << "StosLista...";
	StosLista<int> sl1;
	assert(sl1.empty());
	assert(!sl1);
	for(i=99;i>=0;--i)
		sl1.push(i);
	assert(sl1);
	assert(!sl1.empty());
	StosLista<int> sl2(sl1);
	assert(sl2);
	assert(!sl2.empty());
	for(i=0;i<100;++i) {
		assert(sl1.front() == i);
		assert(sl2.front() == i);
		sl1.pop();
		sl2.pop();
	}
	assert(!sl1);
	assert(!sl2);
	assert(sl1.empty());
	assert(sl2.empty());
	cout << "[ OK ]\n";
	return 0;
}
