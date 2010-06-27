/**
* @file common.h
* Elementy wspólne dla implementacji listy i stosu.
*/

#ifndef _KGADEK_COMMON
#define _KGADEK_COMMON

#include <cstdlib>

/**
* Makro, które baaardzo skraca kod.
* Pozwala na napisanie bloku \c try{...} \c CATCH(x) , który bêdzie w pierwszej kolejno¶ci przechwytywa³
* (charakterystyczny dla danej klasy) b³±d, a dopiero pó¼niej b³±d ogólny (typu std::exception).
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
	* Interfejs klasy obs³ugi b³êdów.
	*/
	struct kpfpExc {
		friend std::ostream& operator<<(std::ostream&, kpfpExc&);
		/**
		* Zwraca nazwê b³êdu.
		* @return Napis opisuj±cy b³±d.
		*/
		virtual const char* name() = 0;
		/**
		* Zwraca nazwê klasy b³êdów.
		* @return Napis opisuj±cy typ b³êdu.
		*/
		virtual const char* classType() = 0;
	};
	/**
	* Przeci±¿ony operator ,,<<''.
	* Pozwala na wysy³anie b³êdu typu ,,StosExc'' do ,,std::cout''.
	* @param out Referencja do obiektu std::ostream.
	* @param e Referencja do interejsu obs³ugi b³êdów.
	*/
	std::ostream& operator<<(std::ostream &out, kpfpExc &e) {
		return out << "Error (" << e.classType() << "): " << e.name()
			<< "\nNastapi zamkniecie programu...\n";
	}


	/**
	* Klasa bazowa obs³ugi b³êdów dla grupy klas ,,Stos''.
	* @see kpfpExc
	*/
	struct StosExc : kpfpExc {
		/**
		* Zwraca nazwê klasy b³êdów.
		* @return Napis opisuj±cy typ b³êdu (b³±d stosu).
		*/
		const char* classType() { return "Stos"; }
	};
	/**
	* B³±d alokacji pamiêci.
	*/
	struct StosExcBadAlloc : StosExc {
		/**
		* Zwraca nazwê b³êdu.
		* @return Napis opisuj±cy b³±d (b³±d alokacji pamiêci stosu).
		*/
		const char* name() { return "0x01: blad alokacji pamieci."; }
	};
	/**
	* Przepe³niony stos.
	* Wystêpuje tylko, gdy implementacja stosu u¿ywa bufora o sta³ym rozmiarze.
	*/
	struct StosExcOverfullTable : StosExc {
		/**
		* Zwraca nazwê b³êdu.
		* @return Napis opisuj±cy b³±d (przepe³nienie stosu).
		*/
		const char* name() { return "0x02: stos jest pelny. Zadeklaruj go z wiekszym buforem poczatkowym."; }
	};
	/**
	* Próba odwo³ania do elementu pustego stosu.
	*/
	struct StosExcEmpty : StosExc {
		/**
		* Zwraca nazwê b³êdu.
		* @return Napis opisuj±cy b³±d (próba dostêpu do elementów pustego stosu).
		*/
		const char* name() { return "0x03: stos jest pusty."; }
	};


	/**
	* Klasa bazowa obs³ugi b³êdów dla klasy ,,Lista''.
	* @see kpfpExc
	*/
	struct ListaExc : kpfpExc {
		/**
		* Zwraca nazwê klasy b³êdów.
		* @return Napis opisuj±cy typ b³êdu (b³±d listy).
		*/
		const char* classType() { return "Lista"; }
	};
	/**
	* Odwo³anie do elementów z pustej listy.
	*/
	struct ListaExcEmpty : ListaExc {
		/**
		* Zwraca nazwê b³êdu.
		* @return Napis opisuj±cy b³±d (próba dostêpu do elementów pustej listy).
		*/
		const char* name() { return "0x12: lista jest pusta."; }
	};
	/**
	* B³±d alokacji pamiêci.
	*/
	struct ListaExcBadAlloc : ListaExc {
		/**
		* Zwraca nazwê b³êdu.
		* @return Napis opisuj±cy b³±d (b³±d alokacji pamiêci listy).
		*/
		const char* name() { return "0x13: blad alokacji pamieci."; }
	};
}

#endif
