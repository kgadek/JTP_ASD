#ifndef _KGADEK_PUNKT_H
#define _KGADEK_PUNKT_H
#include <iostream>

/* deklaracje klas */
class Punkt;
class Wektor;

/* definicje klas */
class Wektor {
	double x,y,z;
public:
	Wektor();					/* domyslny konstruktor */
	Wektor(const double,const double,const double);	/* konstruktor z parametrami*/
				/* konstruktor kopiujacy jest automatycznie generowany */
	double len() const;				/* dlugosc wektora */
	Wektor operator+(const Wektor&) const;		/* dodawanie wektorow */
	Wektor& operator+=(const Wektor&);
	Wektor operator-() const;			/* odwracanie wektora */
	friend Punkt operator+(const Punkt&,const Wektor&);	/* operacje na W i P */
	friend Punkt& operator+=(Punkt&, const Wektor&);
							/* wypisywanie wektora */
	friend std::ostream& operator<<(std::ostream &, const Wektor &);
};

class Punkt {
	double x,y,z;
public:
	Punkt();					/* domyslny konstruktor */
	Punkt(const double,const double,const double);	/* konstruktor z parametrami */
	Punkt operator-() const;			/* zwraca punkt symetryczny
							   wzgledem [0,0,0] */
	Wektor operator-(const Punkt&) const;		/* odejmowanie punktow */
	friend double odl(const Punkt&, const Punkt&);	/* odleglosc dwoch punktow */
	friend Punkt operator+(const Punkt&,const Wektor&);	/* dodawanie P + W */
	friend Punkt& operator+=(Punkt&, const Wektor&);
							/* wypisywanie punktu */
	friend std::ostream& operator<<(std::ostream &, const Punkt &);
};

#endif
