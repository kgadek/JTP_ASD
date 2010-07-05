#ifndef _KPFP_POLYGON
#define _KPFP_POLYGON

#include <vector>
#include "punkty.h"

/**
  * Klasa polygon.
  */
class Polygon {
	/**
	  * Zbiór punktów.
	  */
	std::vector<Punkt> p;
	/**
	  * Iterator służący do wypisywania punktów.
	  * Funkcja show_reset() ustawia go na początek wektora p, natomiast show_next()
	  * zwraca punktu (wraz z przesunięciem) i przesuwa iterator na
	  * następny element wektora. Funkcja show_end() zwraca prawdę gddy iterator
	  * wskazuje na koniec wektora.
	  */
	std::vector<Punkt>::iterator it;
	/**
	  * Przesunięcie o wektor.
	  */
	Wektor w;
public:
	/**
	  * Konstruktor domyślny.
	  */
	Polygon();
	/**
	  * Konstruktor kopiujący.
	  */
	Polygon(const Polygon&);
	/**
	  * Dodawanie kolejnych punktów do polygonu.
	  * Punkt jest przekazywany przez wartość by umożliwić wielokrotne dodawanie
	  * tego samego punktu (np. ze zmienionymi parametrami).
	  */
	void add(Punkt);
	/**
	  * Przesuwanie polygonu o wektor.
	  */
	void move(const Wektor&);
	/**
	  * Ustawia (wewnętrzny) iterator it na początek wektora.
	  */
	void show_reset();
	/**
	  * Następny punkt polygonu.
	  * @returns Punkt polygonu wraz z przesunięciem o wektor.
	  */
	Punkt show_next();
	/**
	  * Stwierdza, czy wypisano wszystkie punkty.
	  * @returns Prawda gddy (wewnętrzny) iterator wskazuje na
	  * koniec wektora.
	  */
	bool show_end() const;
};

#endif
