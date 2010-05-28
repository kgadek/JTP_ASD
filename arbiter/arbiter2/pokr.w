\def\cee/{C}
\def\cpp/{\cee/{\tt++}}


TODO:

 - Pozbyć się hashtablicy z STL-a

 - Dokończyć program




@* Procedura main.

Jej zadaniem jest wczytanie danych wejsciowych i wywolywanie odpowiednich instrukcji
(w zaleznosci od sytuacji).

|INPUTLEN| definiuje wielkosc alokowanego miejsca dla imienia i nazwiska.

@d INPUTLEN 1000
@c
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>

using namespace std;		/* tego sie pozbyc po napisaniu wlasnej hashmapy */
@<Definicje struktur@>@;
@<Definicje funkcji@>@;
@<Zmienne globalne@>@;

int main() {
	while( fgets(input,INPUTLEN,stdin) != NULL ) {		/* fgets i sscanf sa "bezpieczne" */
		@<Wstepnie przetworz tekst@>@;
		if( strcmp(R,":") ) {
			@<Query@>@;
		} else {
		}
	}
	return 0;
}




@ Zmienne globalne.

Zmienna |input| (o dlugosci |INPUTLEN|) przechwytuje caly napis wejsciowy. Ten nastepnie jest
rozbijany na |X| (imie i nazwisko osoby X), |R| (relacja miedzy X a Y) oraz |Y|
(imie i nazwisko osoby Y). Po przetworzeniu do |X| trafia polaczone imie i nazwisko
(analogicznie |Y|).

@<Zmienne globalne@>=
char input[INPUTLEN], X[INPUTLEN], Xa[INPUTLEN], R[INPUTLEN], Y[INPUTLEN], Ya[INPUTLEN];




@ Rozbijanie tekstu w |input| na |X|, |R|, |Y|.

@<Wstepnie przetworz tekst@>=
sscanf(" %s %s %s %s %s ",X,Xa,R,Y,Ya);
strcat(X," "); strcat(X,Xa);				/* polacz X i Xa w jedno */
strcat(Y," "); strcat(Y,Ya);




@ Osoba (|node|).

Przechowuje imie i nazwisko oraz wskazniki do ojca i synow.

@<Definicje struktur@>=
class node {
public:
	char *X;
	node *p, *l, *r;
};




@ Drzewo hashujace.

Sluzy do przechwytywania wskaznika do odpowiedniego |node|-a. Teraz jest to |hash_map| z STL-a
ale kiedys trzeba napisac wlasne...

@<Definicje struktur@>=
struct ltstr {
	bool operator()(const char *s1, const char *s2) const {
		return strcmp(s1,s2) < 0;
	}
};
map<const char*, node*, ltstr> osoby;





@ Funkcje obslugi drzewa hashujacego.

@<Definicje funkcji@>=




@ Odpowiadanie na pytanie.

@<Query@>=
