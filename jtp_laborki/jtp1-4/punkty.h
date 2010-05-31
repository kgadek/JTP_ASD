#ifndef _KGADEK_PUNKT_H
#define _KGADEK_PUNKT_H
#include <iostream>

class Punkt;
class Wektor;

class Wektor {
	double x,y,z;
public:
	Wektor();
	Wektor(const double,const double,const double);
	double len() const;
	Wektor operator+(const Wektor&) const;
	Wektor& operator+=(const Wektor&);
	Wektor operator-() const;
	friend Punkt operator+(const Punkt&,const Wektor&);
	friend Punkt& operator+=(Punkt&, const Wektor&);
	friend std::ostream& operator<<(std::ostream &, const Wektor &);
};

class Punkt {
	double x,y,z;
public:
	Punkt();
	Punkt(const double,const double,const double);
	Punkt operator-() const;
	Punkt operator-(const Punkt&) const;
	friend double odl(const Punkt&, const Punkt&);
	friend Punkt operator+(const Punkt&,const Wektor&);
	friend Punkt& operator+=(Punkt&, const Wektor&);
	friend std::ostream& operator<<(std::ostream &, const Punkt &);
};

#endif
