\input graphicx
%\includegraphics[width=16ex]{test}
% Uzycie: mpost plik --> epstopdf plik
\def\cee/{C}
\def\cpp/{\cee/{\tt++}}
\newdimen\biblioindent\biblioindent=.25in
\def\bibitem#1{\par\medskip\noindent
	\hangindent=\biblioindent
	\hbox to \biblioindent{\cite{#1}\hfil}%
	\ignorespaces
}
\def\bibstart{\bgroup\frenchspacing}
\def\bibend{\egroup}
\def\cite#1{[\csname#1\endcsname]}
\def\xcite#1#2{[\csname#1\endcsname, #2]}
\def\bern{1}


@* Rdzen programu.

Zadaniem |main| jest wczytanie danych wejsciowych i wywolywanie odpowiednich instrukcji
(w zaleznosci od sytuacji).

|INPUTLEN| definiuje wielkosc alokowanego miejsca dla imienia i nazwiska.

|HASHSIZE| okresla rozmiar tablicy hashujacej (82837429 = 79M).

@d INPUTLEN 100
@d HASHSIZE 82837429
@c
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

@<Definicje struktur@>@;
@<Zmienne globalne@>@;
@<Definicje funkcji@>@;

int main() {
	@<Inicjacja zmiennych@>@;
	i=0; // i=0 - nie policzylismy jeszcze par LCA
	while( 1 ) {
		if( fgets(input,INPUTLEN,stdin) == NULL )
			break;
		@<Wstepnie przetworz tekst@>@;
		@<Zdobadz pointery do osob@>@;
		if( R[0]==':') {
			if(!i) {
				i=1; // i policz pary LCA
			}
			// query
		} else {
			switch(R[1]) {
			case 'r': if(R[5]=='p')
					  make_grandparent(xx,yy);
				  else
					  make_grandparent(yy,xx);
				break;
			case 'o': make_cousin(xx,yy);
				break;
			case 'i': make_sibling(xx,yy);
				break;
			case 'a': make_child(yy,xx);
				break;
			case 'h': make_child(xx,yy);
			}
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
osoba *hashtab[HASHSIZE];
int i;
osoba **xx,**yy;



@ Rozbijanie tekstu z |input| na |X|, |R|, |Y|.

@<Wstepnie przetworz tekst@>=
sscanf(input," %s %s %s %s %s ",X,Xa,R,Y,Ya);
strcat(X," ");	/* polacz |X| i |Xa| w jedno */
strcat(X,Xa);
strcat(Y," ");	/* polacz |Y| i |Ya| w jedno */
strcat(Y,Ya);





@q ================================================================================ @>






@* Klasa |osoba|.

Zmienna |nn| przechowuje wskaznik na napis |"NN"|.

Sluzy jako obiekt w 3 strukturach danych: w tablicy hashujacej, w drzewie
(genealogicznym) i w lesie zbiorow rozlacznych.

|char *name| jest wskaznikiem na imie i nazwisko danej osoby (alokacja pamieci i kopiowanie
w konstruktorze) lub wskaznikiem na |*nn| (napis |"NN"|).

Wskaznik |osoba *n| pelni dwie
funkcje:
\item{1.} gdy dany obiekt jest sztuczny, to |*n| wskazuje na |*this|.
\item{2.} gdy obiekt jest konkretna osoba, to wskazuje na nastepny obiekt |osoba| w tablicy
hashujacej.

|osoba *p| wskazuje na ojca w drzewie genealogicznym, natomiast |*s| wskazuje na jego
prawego brata.

W lesie zbiorow rozlacznych uzywane sa wskazniki |osoba *l| - wskaznik na lidera grupy,
|int rank| - ranga.

@<Definicje struktur@>=
char nn[] = {'N','N',0};
class osoba {
public:
	char *name;		/* imie i nazwisko */
	osoba  *n,		/* tablica hashujaca:	nastepny element kolizji */
	       *p,		/* drzew genealogiczne:	ojciec*/
	       *c,		/* 			syn */
	       *s,		/* 			(prawy) brat */
	       *l;		/* las zbiorow rozlacznych: 	wskazanie na ojca */
	int rank;		/* 				ranga */
	osoba() : name(nn), n(NULL), p(NULL), s(NULL), l(this), rank(0) { }
	osoba(char *in) : n(NULL), p(NULL), s(NULL), l(this), rank(0) {
		name = new char[strlen(in)+1];
		strcpy(name,in);
	}
	~osoba() {
		if(name!=nn) delete [] name;
	}
};




@q ================================================================================ @>






@* Obsluga tablicy hashujacej.

@<Inicjacja zmiennych@>=
for(i=0;i<HASHSIZE;++i)
	hashtab[i]=NULL;



@ Przeszukiwanie tablicy hashujacej.

Po wykonaniu ciagu tych polecen, w |osoba **xx| jak i w |osoba **yy| beda znajdowac
sie wskazania na pointery do szukanych osob (niezaleznie, czy dana osoba wczesniej
byla rozpatrywana czy nie).

@<Zdobadz pointery do osob@>=
xx = (hashtab+getHash(X));
while((*xx) && strcmp((*xx)->name,X))
	xx = &((*xx)->n);
if((*xx)==NULL)
	(*xx) = new osoba(X);
yy = (hashtab+getHash(Y));
while((*yy) && strcmp((*yy)->name,Y))
	yy = &((*yy)->n);
if((*yy)==NULL)
	(*yy) = new osoba(Y);




@ Funkcja hashujaca djb2~\cite{bern}.

@<Definicje funkcji@>=
unsigned int getHash(char *str) {
	unsigned int ret = 5381;
	while(*str)
		ret = ((ret << 5) + ret) ^ (*(str++));
				/* |@t$hash_i = hash_{i-1}*33 \oplus str[i]$@>| */
	return ret % HASHSIZE;	/* obciecie wyniku */
}


@q ================================================================================ @>

@* Drzewo genealogiczne.



@ Operacja laczenia wierzcholkow.
Zaklada, ze oba parametry '|osoba **x|' i '|osoba **y|' nie wskazuja na NULL. Operacja
|join(osoba **x,osoba **y)| powoduje wlaczenie osoby |*y| do osoby |*x| poprzez:
\item{A1.} przepisanie dzieci osoby |*y| do osoby |*x|
\item{A2.} wywolanie |join()| na ojcach |*x| i |*y|.

@<Definicje funkcji@>=
void join(osoba **x, osoba **y) {
	osoba *t, **u;
	while(1) {				/* A1.	Przepinanie dzieci */
		t = (*x)->c;			/* 	|t| - stare dziecki |*x| */
		(*x)->c = (*y)->c;		/* 	zastap dzieci |*x| przez
							dzieci |*y| */
		while(*u) {			/* 	popraw wskazanie na ojca
							nowym dzieciom |*x| */
			(*u)->p = (*x);
			u = &((*u)->s);
		}
		(*u) = t;			/* 	dolacz stare dzieci |*x| */
		if(!((*y)->p))			/* A2.	Wywolywanie w gore drzewa */
			return;			/* 	nic wiecej do zrobienia */
		x = &((*x)->p);
		y = &((*y)->p);
		if(!(*x) || (*y)->n != (*y)) {	/* 	jesli trzeba zlaczyc
							wierzcholki w druga strone, tj.
							|x@t$\rightarrow$@>y| */
			u = x; x = y; y = u;
		}
	}
}


@q ================================================================================ @>




@*References.
\bibstart

\bibitem{bern}
Algorytm djb2 autorstwa Donalda Bernsteina.

Kod znaleziony na stronie
\pdfURL{http://www.cse.yorku.ca/\~{}oz/hash.html}.
\bibend
