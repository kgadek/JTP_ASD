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
	*	- dostêp do pierwszego elementu: O(1)
	*	- dostêp do ostatniego elementu: O(n)
	* Wystarcza w zupe³no¶ci do implementacji stosu (patrz: Stos).
	*/
	template<class T = int> class Lista {
		/**
		* Wska¼nik na pierwszy element listy.
		* Podczas wykonywania destruktora, usunie tak¿e nastêpniki.
		*/
		struct node {
			/**
			* Wska¼nik na element nastêpny.
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
			* @return Zwraca referencjê do bie¿±cego node-a.
			*/
			node& operator=(const node &x) {
				v = x.v;
				return *this;
			}
			/**
			* Destruktor.
			* Wykona destrukcjê wszystkich swoich nastêpników.
			*/
			~node() throw() {
				if(n) delete n;
			}
		} *f;
	public:
		/**
		* Domy¶lny konstruktor.
		*/
		Lista() : f(NULL) {}
		/**
		* Konstruktor kopiuj±cy.
		* @param x Kopiowany obiekt.
		* Do kopiowania wykorzystuje wska¼nik na wska¼nik na element nastêpny, co pozwala znacznie skróciæ kod.
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
		* Operator kopiuj±cy.
		* Do kopiowania wykorzystuje wska¼nik na wska¼nik na element nastêpny, co pozwala znacznie skróciæ kod.
		* @param x Kopiowany obiekt.
		* @return Zwraca referencjê do siebie.
		* @see Lista::Lista()
		*/
		Lista& operator=(const Lista &x) {
			delete f;
			for(node **u = &f, *t = x.f; t; u=&((*u)->n), t=t->n)
				(*u) = new node(*t);
			return *this;
		}
		/**
		* Zwraca pierwszy element na li¶cie.
		* @exception ListaExcEmpty
		*/
		T& front() const {
			try {
				if(!f) throw ListaExcEmpty();
			} CATCH(ListaExc)
			return f->v;
		}
		/**
		* Zwraca ostatni element na li¶cie.
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
		* Dodaje element na pocz±tek listy.
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
