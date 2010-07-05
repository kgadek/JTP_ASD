#include <cmath>
#include <iostream>
#include "punkty.h"



//#define NDEBUG	/* do testow klas i metod____________________________________________ */
#include <cassert>	/* odkomentowac #define NDEBUG by nie testowac */
#define EQ(a,b) (fabs((double)(a)-(double)(b))<0.0000001)	/* do porownywania double */



/* ========================================[ Wektor ]======================================== */
Wektor::Wektor() : x(0.0), y(0.0), z(0.0) { }

Wektor::Wektor(const double a,const double b,const double c) : x(a), y(b), z(c) { }

inline double Wektor::len() const {
	return sqrt(x*x+y*y+z*z);
}

inline Wektor Wektor::operator+(const Wektor &w) const {
	return Wektor(x+w.x, y+w.y, z+w.z);
}

inline Wektor& Wektor::operator+=(const Wektor &w) {
	x += w.x; y += w.y; z += w.z;
	return *this;
}

inline Wektor Wektor::operator-() const {
	return Wektor(-x, -y, -z);
}

inline std::ostream& operator<<(std::ostream &out, const Wektor &w) {
	out << "(" << w.x << "," << w.y << "," << w.z << ")";
	return out;
}

/* ========================================[ Punkt ]========================================= */
Punkt::Punkt() : x(0.0), y(0.0), z(0.0) { }

Punkt::Punkt(const double a,const double b,const double c) : x(a), y(b), z(c) { }

inline double odl(const Punkt &a, const Punkt &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}

inline Punkt operator+(const Punkt &p, const Wektor &w) {
	return Punkt(p.x+w.x, p.y+w.y, p.z+w.z);
}

inline Punkt& operator+=(Punkt &p, const Wektor &w) {
	p.x += w.x; p.y += w.y; p.z += w.z;
	return p;
}

inline Punkt Punkt::operator-() const {
	return Punkt(-x,-y,-z);
}

inline Wektor Punkt::operator-(const Punkt &p) const {
	return Wektor(x-p.x, y-p.y, z-p.z);
}

inline std::ostream& operator<<(std::ostream &out, const Punkt &w) {
	out << "[" << w.x << "," << w.y << "," << w.z << "]";
	return out;
}

/* ========================================[  Main  ]======================================== */
int main() {
	std::ios_base::sync_with_stdio(0);			/* CIN/COUT booster */

	/* kilka podstawowych testow poprawnosciowych */
	assert( EQ(Wektor(3.0,4.0,0.0).len(),5.0) );		/* W.len() */
	assert( EQ(Wektor(1.0,2.0,3.0).len(),3.74165738677394) );
	assert( EQ(Wektor().len(),0.0) );
								/* W+W    W+=W */
	assert( EQ((Wektor(1.0,2.0,3.0)+Wektor(3.0,2.0,1.0)).len(),6.9282032302755091) );
	assert( EQ((Wektor()+=Wektor(6.0,6.0,6.0)).len(),10.3923048454132637611) );
	assert( EQ((-Wektor()).len(),0.0) );			/* -W */
	assert( EQ((-Wektor(3.0,4.0,5.0)).len(),7.0710678118654) );
	assert( EQ(((-Wektor(3.1415,2.7182,1.4142))+Wektor(3.1415,2.7182,1.4142)).len(),0.0) );
	assert( std::cout << Wektor(1.5,2.5,3.5) << '\n' );	/* cout << W */
	assert( EQ((Punkt()-Punkt(0.0,0.0,0.0)).len(),0.0) );	/* P-P */
	assert( EQ((Punkt(0.0,10.0,-4.0)-Punkt(-4.0,6.0,-8.0)).len(),6.9282032302755091) );
								/* -P    P+W    odl(P,P) */
	assert( EQ(odl(((-Punkt(1.0,2.0,3.0))+Wektor(1.0,2.0,3.0)),Punkt()),0.0) );
	assert( EQ(odl((Punkt()+Wektor()),Punkt()),0) );	/* P+W    odl(P,P) */
	assert( EQ(odl(Punkt(),Punkt()),0.0) );			/* odl(P,P) */
	assert( EQ(odl(Punkt(1.0,2.0,3.0),Punkt(-3.0,-2.0,-1.0)),6.9282032302755091) );
	assert( std::cout << Punkt(1.23,4.56,7.89) << '\n' );	/* cout << P */

	return 0;
}

