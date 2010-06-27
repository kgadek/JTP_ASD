/**
* @file lista.h
* Implementacja listy jednokierunkowej.
*/

#ifndef _KGADEK_LISTA
#define _KGADEK_LISTA

#include "common.h"
#include <iostream>

namespace kpfp {

	/**
	* Lista jednokierunkowa.
	* Czasy wykonywania operacji:
	*	- dost�p do pierwszego elementu: O(1)
	*	- dost�p do ostatniego elementu: O(n)
	* Wystarcza w zupe�no�ci do implementacji stosu (patrz: Stos).
	*/
	template<class T = int> class Lista {
		/**
		* Wska�nik na pierwszy element listy.
		* Podczas wykonywania destruktora, usunie tak�e nast�pniki.
		*/
		struct node {
			/**
			* Wska�nik na element nast�pny.
			*/
			node *n;
			/**
			* Przechowywany obiekt.
			*/
			T v;
			/**
			* Konstruktor.
			*/
			node(const T &x, node *nx = NULL) : n(nx), v(x) {}
			/**
			* Operator przypisania.
			* @param x Kopiowany element.
			* @return Zwraca referencj� do bie��cego node-a.
			*/
			node& operator=(const node &x) {
				v = x.v;
				return *this;
			}
			/**
			* Destruktor.
			* Wykona destrukcj� wszystkich swoich nast�pnik�w.
			*/
			~node() throw() {
				if(n) delete n;
			}
		} *f;
	public:
		/**
		* Domy�lny konstruktor.
		*/
		Lista() : f(NULL) {}
		/**
		* Konstruktor kopiuj�cy.
		* @param x Kopiowany obiekt.
		* Do kopiowania wykorzystuje wska�nik na wska�nik na element nast�pny, co pozwala znacznie skr�ci� kod.
		*/
		Lista(const Lista &x) : f(NULL) {
			for(node **u = &f, *t = x.f; t; u=&((*u)->n), t=t->n)
				(*u) = new node(*t);
		}
		/**
		* Destruktor.
		* @see node::~node
		*/
		~Lista() throw() {
			delete f;
		}
		/**
		* Operator kopiuj�cy.
		* Do kopiowania wykorzystuje wska�nik na wska�nik na element nast�pny, co pozwala znacznie skr�ci� kod.
		* @param x Kopiowany obiekt.
		* @return Zwraca referencj� do siebie.
		* @see Lista::Lista()
		*/
		Lista& operator=(const Lista &x) {
			delete f;
			for(node **u = &f, *t = x.f; t; u=&((*u)->n), t=t->n)
				(*u) = new node(*t);
			return *this;
		}
		/**
		* Zwraca pierwszy element na li�cie.
		* @exception ListaExcEmpty
		*/
		T& front() const {
			try {
				if(!f) throw ListaExcEmpty();
			} CATCH(ListaExc)
			return f->v;
		}
		/**
		* Zwraca ostatni element na li�cie.
		* @exception ListaExcEmpty
		*/
		T& back() const {
			node *x;
			try {
				if(!f) throw ListaExcEmpty();
				x = f;
				while(x->n)	x = x->n;
			} CATCH(ListaExc)
			return x->v;
		}
		/**
		* Zdejmuje pierwszy element z listy.
		* @exception ListaExcEmpty
		*/
		void pop_front() {
			try {
				if(!f) throw ListaExcEmpty();
				node *t = f;
				if(f) t = f->n;
				f->n = NULL;
				delete f;
				f = t;
			} CATCH(ListaExc);
		}
		/**
		* Zdejmuje ostatni element z listy.
		* @exception ListaExcEmpty
		*/
		void pop_back() {
			try {
				if(!f) throw ListaExcEmpty();
				node **t = &f;
				while((*t)->n) t = &((*t)->n);
				delete (*t);
				(*t) = NULL;
			} CATCH(ListaExc)
		}
		/**
		* Dodaje element na pocz�tek listy.
		*/
		void push_front(const T &y) {
			f = new node(y,f);
			if(!f) throw ListaExcBadAlloc();
		}
		/**
		* Dodaje element na koniec listy.
		*/
		void push_back(const T &y) {
			node **t = &f;
			while(*t) t = &((*t)->n);
			*t = new node(y);
		}
		/**
		* Stwierdza, czy lista jest pusta.
		*/
		bool empty() const {
			return f==NULL;
		}
	};

}

#endif
