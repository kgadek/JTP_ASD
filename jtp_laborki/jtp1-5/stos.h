/**
* @file stos.h
* Implementacje stosu.
*/

#ifndef _KGADEK_STOS
#define _KGADEK_STOS

#include <iostream>
#include <exception>
#include "common.h"

namespace kpfp {

	/**
	* Abstrakcyjna klasa bazowa ,,Stos''.
	* Definiuje interfejs obs³ugi stosu. Zawiera tak¿e licznik instancji (zlicza klas pochodne).
	*/
	template <class T> class Stos {
	protected:
		/**
		* Licznik instancji klas pochodnych.
		*/
		static unsigned int licznik;
		/**
		* Ilo¶æ elementow na stosie.
		*/
		unsigned int used;
	public:
		/**
		* Konstruktor domy¶lny.
		*/
		Stos() : used(0) {
			++licznik;
		}
		/**
		* Zwraca ilo¶æ instancji klas pochodnych.
		*/
		static unsigned int getLicznik() {
			return licznik;
		}
		/**
		* Wrzuca na stos.
		* @param x Warto¶æ dodawana na stos.
		*/
		virtual void push(const T &x) = 0;
		/**
		* Zdejmuje ze stosu.
		*/
		virtual void pop() = 0;
		/**
		* Zwraca element z góry stosu.
		* @return Referencja do obiektu na szczycie stosu.
		*/
		virtual T& front() = 0;
		/**
		* Stwierdza, czy stos jest pusty.
		* @returns ,,true'', wtedy i tylko wtedy, gdy stos jest pusty.
		*/
		virtual bool empty() const = 0;
		/**
		* Konwersja do typu bool.
		* @returns ,,true'' wtedy i tylko wtedy, gdy stos jest niepusty.
		*/
		virtual operator bool() const = 0;
	};
	template <class T> unsigned int Stos<T>::licznik = 0;

	/**
	* Stos na tablicy.
	* Implementuje interfejs ,,Stos'' na tablicy o zadanym (w konstruktorze) rozmiarze.
	*/
	template <class T> class StosTablica : public Stos<T> {
	protected:
		/**
		* Wska¼nik na tablicê elementów.
		*/
		T *ptr;
		/**
		* Rozmiar tablicy przechowujacej elementy.
		* Zawsze spelniona jest nierownosc: used <= size.
		*/
		unsigned int size;
	public:
		/**
		* Domy¶lny konstruktor.
		* @param _size Rozmiar alokowanej tablicy.
		* @exception StosExcBadAlloc
		*/
		StosTablica(unsigned int const _size = 100) : ptr(NULL), size(_size) {
			try {
				ptr = new T[size];
				if(!ptr) throw StosExcBadAlloc();
			} CATCH(StosExc)
		}
		/**
		* Konstruktor kopiujacy.
		* @param x Referencja do obiektu StosTablica lub pochodnego.
		* @exception StosExcBadAlloc
		*/
		StosTablica(StosTablica const &x) : ptr(NULL), size(x.size) {
			try {
				ptr = new T[size];
				if(!ptr) throw StosExcBadAlloc();
				for(; Stos<T>::used<x.used; ++Stos<T>::used) ptr[Stos<T>::used] = x.ptr[Stos<T>::used];
			} CATCH(StosExc)
		}
		/**
		* Destruktor.
		*/
		virtual ~StosTablica() throw() {
			delete ptr;
		}
		/**
		* Operator przypisania (kopiuj±cy).
		* @param x Referencja do obiektu StosTablica lub pochodnego.
		* @exception StosExcBadAlloc
		*/
		StosTablica& operator=(StosTablica const &x) {
			try {
				size = x.size;
				delete [] ptr;
				ptr = new T[size];
				if(!ptr) throw StosExcBadAlloc();
				for(Stos<T>::used = 0; Stos<T>::used<x.used;++Stos<T>::used) ptr[Stos<T>::used] = x.ptr[Stos<T>::used];
				return *this;
			} CATCH(StosExc)
		}
		/**
		* Dodaje element na stos.
		* @param x Warto¶æ dodawana na stos.
		* @exception StosExcOverfullTable
		*/
		void push(const T &x) {
			try {
				if(Stos<T>::used >= size) throw StosExcOverfullTable();
				ptr[Stos<T>::used++] = x;
			} CATCH(StosExc)
		}
		/**
		* Zdejmuje element ze stosu.
		* @exception StosExcEmpty
		*/
		void pop() {
			try {
				if( Stos<T>::used-- == 0) throw ListaExcEmpty();
			} CATCH(StosExc)
		}
		/**
		* Zwraca element z góry stosu.
		* @return Referencja do obiektu na szczycie stosu.
		* @exception StosExcEmpty
		*/
		T& front() {
			try {
				if(!ptr) throw StosExcEmpty();
			} CATCH(StosExc);
			return ptr[Stos<T>::used-1];
		}
		/**
		* Stwierdza, czy stos jest pusty.
		* @returns ,,true'' wtedy i tylko wtedy, gdy stos jest pusty.
		*/
		bool empty() const {
			return Stos<T>::used == 0;
		}
		/**
		* Stwierdza, czy stos jest pe³ny.
		* @returns ,,true'', wtedy i tylko wtedy, gdy stos jest pe³ny (size = used).
		*/
		bool full() const {
			return Stos<T>::used == size;
		}
		/**
		* Konwersja do typu bool.
		* @returns ,,true'' wtedy i tylko wtedy, gdy stos jest niepusty.
		*/
		virtual operator bool() const {
			return Stos<T>::used != 0;
		}
	};

	/**
	* Stos na wektorze.
	* Implementuje interfejs ,,Stos'' na wektorze (tablicy rosn±cej w miarê potrzeby).
	*/
	template <class T> class StosTablicaRosnaca : public StosTablica<T> {
	protected:
		/**
		* Krok tablicy.
		* Gdy zabraknie w tablicy miejsca, zostanie zwiêkszona o warto¶æ step.
		*/
		unsigned int step;
	public:
		/**
		* Domy¶lny konstruktor.
		* @param _size Pocz±tkowy rozmiar wektora.
		* @param _step Krok tablicy.
		*/
		StosTablicaRosnaca(unsigned int const _size=100, unsigned int const _step=100) : StosTablica<T>(_size), step(_step) { }
		/**
		* Konstruktor kopiuj±cy.
		* @param x Referencja do obiektu StosTablica lub pochodnego.
		* @param _step Krok tablicy.
		*/
		StosTablicaRosnaca(StosTablica<T> const &x, unsigned int const _step=100) : StosTablica<T>(x), step(_step) {}
		/**
		* Konstruktor kopiuj±cy.
		* @param x Referencja do obiektu StosTablicaRosn±ca lub pochodnego.
		*/
		StosTablicaRosnaca(StosTablicaRosnaca<T> const &x) : StosTablica<T>(x.size), step(x.step) {
			for(StosTablica<T>::used = 0;StosTablica<T>::used<x.used;++StosTablica<T>::used)
				StosTablica<T>::ptr[StosTablica<T>::used] = x.ptr[StosTablica<T>::used];
		}
		/**
		* Wrzuca na stos.
		* @param x Warto¶æ dodawana na stos.
		*/
		void push(const T &x) {
			if(Stos<T>::used == StosTablica<T>::size) {
				if(!step) throw StosExcOverfullTable();
				T *ptr2;
				ptr2 = new T[StosTablica<T>::size+step];
				if(!ptr2) throw StosExcBadAlloc();
				for(unsigned int i=0;i<StosTablica<T>::size;++i) ptr2[i] = StosTablica<T>::ptr[i];
				delete [] StosTablica<T>::ptr;
				StosTablica<T>::ptr = ptr2;
				StosTablica<T>::size+=step;
			}
			StosTablica<T>::ptr[StosTablica<T>::used++] = x;
		}
		/**
		* Operator przypisania (kopiuj±cy).
		* @param x Kopiowany stos.
		* @exception StosExcBadAlloc
		*/
		StosTablicaRosnaca& operator=(StosTablicaRosnaca<T> const &x) {
			StosTablica<T>::size = x.size;
			step = x.step;
			delete StosTablica<T>::ptr;
			StosTablica<T>::ptr = new T[StosTablica<T>::size];
			for(Stos<T>::used = 0; Stos<T>::used<x.used;++Stos<T>::used)
				StosTablica<T>::ptr[Stos<T>::used] = x.ptr[Stos<T>::used];
			if(!StosTablica<T>::ptr) throw StosExcBadAlloc();
			return *this;
		}
		/**
		* Stwierdza, czy stos jest pe³ny.
		* @returns ,,false'', gdy¿ .
		*/
		bool full() const {
			return Stos<T>::used == StosTablica<T>::size && !step;
		}
	};

	/**
	* Adapter listy jednokierunkowej umo¿liwiaj±cy operacje stosowe.
	*/
	template <class T> class StosLista : public Stos<T> {
	protected:
		/**
		* Lista.
		*/
		Lista<T> p;
	public:
		/**
		* Konstruktor domy¶lny.
		*/
		StosLista() : p() {}
		/**
		* Konstruktor kopiuj±cy.
		* @param x Referencja do StosTablica lub pochodnego.
		*/
		StosLista(const StosLista<T> &x) : p(x.p) {		}
		/**
		* Wrzuca na stos.
		* @param x Warto¶æ dodawana na stos.
		*/
		void push(const T &x) {
			p.push_front(x);
		}
		/**
		* Zdejmuje ze stosu.
		*/
		void pop() {
			p.pop_front();
		}
		/**
		* Zwraca element z góry stosu.
		* @return Referencja do obiektu na szczycie stosu.
		*/
		T& front() {
			return p.front();
		}
		/**
		* Stwierdza, czy stos jest pusty.
		* @returns ,,true'', wtedy i tylko wtedy, gdy stos jest pusty.
		*/
		bool empty() const {
			return p.empty();
		}
		/**
		* Konwersja do typu bool.
		* @returns ,,true'' wtedy i tylko wtedy, gdy stos jest niepusty.
		*/
		operator bool() const {
			return !p.empty();
		}
	};
}

#endif
