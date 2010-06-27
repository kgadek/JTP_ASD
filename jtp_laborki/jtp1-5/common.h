/**
* @file common.h
* Elementy wsp�lne dla implementacji listy i stosu.
*/

#ifndef _KGADEK_COMMON
#define _KGADEK_COMMON

#include <cstdlib>

/**
* Makro, kt�re baaardzo skraca kod.
* Pozwala na napisanie bloku \c try{...} \c CATCH(x) , kt�ry b�dzie w pierwszej kolejno�ci przechwytywa�
* (charakterystyczny dla danej klasy) b��d, a dopiero p�niej b��d og�lny (typu std::exception).
*/
#define CATCH(x) catch(x &e) {\
			std::cout << "\n\n" << e;\
				exit(1);\
			} catch(std::exception &e) {\
				std::cout << "Nieznany blad:\n" << e.what() << '\n';\
				exit(1);\
			}

namespace kpfp {

	/**
	* Interfejs klasy obs�ugi b��d�w.
	*/
	struct kpfpExc {
		friend std::ostream& operator<<(std::ostream&, kpfpExc&);
		/**
		* Zwraca nazw� b��du.
		* @return Napis opisuj�cy b��d.
		*/
		virtual const char* name() = 0;
		/**
		* Zwraca nazw� klasy b��d�w.
		* @return Napis opisuj�cy typ b��du.
		*/
		virtual const char* classType() = 0;
	};
	/**
	* Przeci��ony operator ,,<<''.
	* Pozwala na wysy�anie b��du typu ,,StosExc'' do ,,std::cout''.
	* @param out Referencja do obiektu std::ostream.
	* @param e Referencja do interejsu obs�ugi b��d�w.
	*/
	std::ostream& operator<<(std::ostream &out, kpfpExc &e) {
		return out << "Error (" << e.classType() << "): " << e.name()
			<< "\nNastapi zamkniecie programu...\n";
	}


	/**
	* Klasa bazowa obs�ugi b��d�w dla grupy klas ,,Stos''.
	* @see kpfpExc
	*/
	struct StosExc : kpfpExc {
		/**
		* Zwraca nazw� klasy b��d�w.
		* @return Napis opisuj�cy typ b��du (b��d stosu).
		*/
		const char* classType() { return "Stos"; }
	};
	/**
	* B��d alokacji pami�ci.
	*/
	struct StosExcBadAlloc : StosExc {
		/**
		* Zwraca nazw� b��du.
		* @return Napis opisuj�cy b��d (b��d alokacji pami�ci stosu).
		*/
		const char* name() { return "0x01: blad alokacji pamieci."; }
	};
	/**
	* Przepe�niony stos.
	* Wyst�puje tylko, gdy implementacja stosu u�ywa bufora o sta�ym rozmiarze.
	*/
	struct StosExcOverfullTable : StosExc {
		/**
		* Zwraca nazw� b��du.
		* @return Napis opisuj�cy b��d (przepe�nienie stosu).
		*/
		const char* name() { return "0x02: stos jest pelny. Zadeklaruj go z wiekszym buforem poczatkowym."; }
	};
	/**
	* Pr�ba odwo�ania do elementu pustego stosu.
	*/
	struct StosExcEmpty : StosExc {
		/**
		* Zwraca nazw� b��du.
		* @return Napis opisuj�cy b��d (pr�ba dost�pu do element�w pustego stosu).
		*/
		const char* name() { return "0x03: stos jest pusty."; }
	};


	/**
	* Klasa bazowa obs�ugi b��d�w dla klasy ,,Lista''.
	* @see kpfpExc
	*/
	struct ListaExc : kpfpExc {
		/**
		* Zwraca nazw� klasy b��d�w.
		* @return Napis opisuj�cy typ b��du (b��d listy).
		*/
		const char* classType() { return "Lista"; }
	};
	/**
	* Odwo�anie do element�w z pustej listy.
	*/
	struct ListaExcEmpty : ListaExc {
		/**
		* Zwraca nazw� b��du.
		* @return Napis opisuj�cy b��d (pr�ba dost�pu do element�w pustej listy).
		*/
		const char* name() { return "0x12: lista jest pusta."; }
	};
	/**
	* B��d alokacji pami�ci.
	*/
	struct ListaExcBadAlloc : ListaExc {
		/**
		* Zwraca nazw� b��du.
		* @return Napis opisuj�cy b��d (b��d alokacji pami�ci listy).
		*/
		const char* name() { return "0x13: blad alokacji pamieci."; }
	};
}

#endif
