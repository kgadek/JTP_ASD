#ifndef _KPFP_POLYGON
#define _KPFP_POLYGON

#include <vector>
#include <iostream>


/* deklaracje klas */
class Punkt;
class Wektor;
class Polygon;

/**
  * Klasa wektor.
  */
class Wektor {
        /**
          * Współrzędna x-owa.
          */
        double x;
        /**
          * Współrzędna y-owa.
          */
        double y;
        /**
          * Współrzędna z-owa.
          */
        double z;
public:
        /**
          * Domyślny konstruktor.
          * Warto dodać, że konstruktor automatycznie generowany konstruktor kopiujący
          * jest w 100% poprawnie działający.
          */
        Wektor();
        /**
          * Konstruktor z parametrami.
          * @param _x Współrzędna x-owa
          * @param _y Współrzędna y-owa
          * @param _z Współrzędna z-owa
          */
        Wektor(const double _x,const double _y,const double _z);
        /**
          * Długość wektora.
          * @return Zwraca długość wektora w metryce Euklidesowej.
          */
        double len() const;
        /**
          * Operator dodawania wektorów.
          * @param w Dodawany wektor
          * @return Zwracany jest nowy wektor będący sumą bieżącego i dodawanego
          */
        Wektor operator+(const Wektor &w) const;
        /**
          * Operator dodawania wektorów.
          * Zmienia wartość bieżącego wektora.
          * @param w Dodawany wektor
          * @return Zwracany jest wskaźnik na bieżący wektor.
          */
        Wektor& operator+=(const Wektor &w);
        /**
          * Odwracanie wektora.
          * @return Zwraca kopię bieżącego wektora z przeciwnymi współrzędnymi.
          */
        Wektor operator-() const;
        /**
          * Operator przesuwania punktu o wektor.
          * @return Zwracany jest nowy wektor z przeciwnymi współrzędnymi.
          */
        friend Punkt operator+(const Punkt &p,const Wektor &w);
        /**
          * Operator przesuwania punktu o wektor.
          * @param p Przesuwany punkt.
          * @param w Wektor o który przesuwamy.
          * @return Zwracana jest referencja na przesunięty punkt p.
          */
        friend Punkt& operator+=(Punkt &p, const Wektor &w);
        /**
          * Operator << - wypisywanie wektora do strumienia std::cout.
          * @param out Referencja na strumień wyjściowy.
          * @param w Referencja na wypisywany wektor.
          * @return Referencja na strumień wyjściowy out.
          */
        friend std::ostream& operator<<(std::ostream &out, const Wektor &w);
        /**
          * Zwróć współrzędną x-ową.
          * Funkcja ta jest b. przydatna w widgecie RenderArea.
          * @return Zwraca współrzędną x-ową wektora zrzutowaną do typu całkowitego (int).
          */
        int getIX() const;
        /**
          * Zwróć współrzędną y-ową.
          * Funkcja ta jest b. przydatna w widgecie RenderArea.
          * @return Zwraca współrzędną y-ową wektora zrzutowaną do typu całkowitego (int).
          */
        int getIY() const;
};

/**
  * Klasa punkt.
  */
class Punkt {
        /**
          * Współrzędna x-owa.
          */
        double x;
        /**
          * Współrzędna y-owa.
          */
        double y;
        /**
          * Współrzędna z-owa.
          */
        double z;
public:
        /**
          * Domyślny konstruktor.
          */
        Punkt();
        /**
          * Konstruktor z parametrami.
          * @param a Współrzędna x-owa
          * @param b Współrzędna y-owa
          * @param c Współrzędna z-owa
          */
        Punkt(const double,const double,const double);
        /**
          * Odwróć punkt.
          * @return Zwraca punkt symetrycznt do bieżącego względem punktu [0,0,0].
          */
        Punkt operator-() const;
        /**
          * Operator odejmowania punktów.
          * @param p Punkt odejmowany od bieżącego.
          * @return Zwracany jest punkt będący wynikiem odejmowania współrzędnych punktu
          * p od bieżącego punktu.
          */
        Wektor operator-(const Punkt &p) const;
        /**
          * Odległość dwóch punktów.
          * @param a Pierwszy punkt.
          * @param b Drugi punkt.
          * @return Zwraca odległość dwóch punktów w metryce Euklidesowej.
          */
        friend double odl(const Punkt &a, const Punkt &b);
        friend Punkt operator+(const Punkt&,const Wektor&);	/* dodawanie P + W */
        friend Punkt& operator+=(Punkt&, const Wektor&);
        /**
          * Operator << - wypisywanie punktu do strumienia std::cout.
          * @param out Referencja na strumień wyjściowy.
          * @param w Referencja na wypisywany wektor.
          * @return Referencja na strumień wyjściowy out.
          */
        friend std::ostream& operator<<(std::ostream &, const Punkt &);
        /**
          * Zwróć współrzędną x-ową.
          * Funkcja ta jest b. przydatna w widgecie RenderArea.
          * @return Zwraca współrzędną x-ową wektora zrzutowaną do typu całkowitego (int).
          */
        int getIX() const;
        /**
          * Zwróć współrzędną y-ową.
          * Funkcja ta jest b. przydatna w widgecie RenderArea.
          * @return Zwraca współrzędną y-ową wektora zrzutowaną do typu całkowitego (int).
          */
        int getIY() const;
};

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
	  * Czyści polygon.
	  * Usuwa wszystkie punkty i ustawia przesunięcie o wektor na zero.
	  */
        void clear();
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
