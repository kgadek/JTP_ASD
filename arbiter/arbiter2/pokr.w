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
|HASHSIZE| okresla rozmiar tablicy hashujacej (82837429 = 79M). Wazny jest fakt, iz
jest to liczba pierwsza.

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
	while( 1 ) {
		if( fgets(input,INPUTLEN,stdin) == NULL )
			break;
		@<Wstepnie przetworz tekst@>@;
		@<Zdobadz pointery do osob@>@;
		if( R[0]==':') {
			if(!queryPart) {
				queryPart = 1; // i policz pary LCA
			}
			// query
		} else {
			switch(R[1]) {
			case 'r': if(R[5]=='p')
					  make_grandparent(*xx,*yy);
				  else
					  make_grandparent(*yy,*xx);
				break;
			case 'o': make_cousin(*xx,*yy);
				break;
			case 'i': make_sibling(*xx,*yy);
				break;
			case 'a': make_child(*yy,*xx);
				break;
			case 'h': make_child(*xx,*yy);
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

|int i| jest pomocniczym licznikiem. |int queryPart| informuje, czy nastapila
sekcja z pytaniami o \break pokrewienstwo. |osoba *hashtab[]| jest tablica hashujaca
wspomagajaca wyszukiwanie rozpatrywanej osoby.

@<Zmienne globalne@>=
char input[INPUTLEN], X[INPUTLEN], Xa[INPUTLEN], R[INPUTLEN], Y[INPUTLEN], Ya[INPUTLEN];
osoba *hashtab[HASHSIZE];
int i;
int queryPart = 0;
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

Wskaznik |osoba *n| pelni dwie funkcje
{
\parindent = 60 pt
\item{1.} gdy dany obiekt jest sztuczny, to |*n| wskazuje na |*this|.
\item{2.} gdy obiekt jest konkretna osoba, to wskazuje na nastepny obiekt |osoba| w tablicy
hashujacej
}
|osoba *p| wskazuje na ojca w drzewie genealogicznym, natomiast |*s| wskazuje na jego
prawego brata. W |osoba **r| zapamietany jest adres wskaznika na |*this| od ojca lub
lewego brata.

W lesie zbiorow rozlacznych uzywany jest wskaznik |osoba *l| na lidera grupy, oraz
|int rank| - ranga danej osoby.

@<Definicje struktur@>=
char nn[] = {'N','N',0};
class osoba {
public:
	char *name;		/* imie i nazwisko */
	osoba  *n,		/* w tablicy hashujacej:	nastepny element kolizji */
	       *p, *c, *s, **r,	/* w drzewie genealogicznym:	ojciec. syn, prawy brat,
				 	wskaznik na ta osobe od ojca lub lewego brata */
	       *l;		/* w lesie zbiorow rozlacznych:	wskazanie na ojca, */
	int rank;		/* w lesie zbiorow rozlacznych:	ranga */
	osoba() : name(NULL), n(NULL), p(NULL), s(NULL), r(NULL), l(this), rank(0) {
		name = nn;
	}
	osoba(char *in) : n(NULL), p(NULL), s(NULL), r(NULL), l(this), rank(0) {
		name = new char[strlen(in)+1];
		strcpy(name,in);
	}
	~osoba() {
		if(name!=nn) delete [] name;
	}
};




@q ================================================================================ @>






@* Tablica hashujaca.

Na wstepie wymaga tylko wyczyszczenia.

@<Inicjacja zmiennych@>=
for(i=0;i<HASHSIZE;++i)
	hashtab[i]=NULL;



@ Przeszukiwanie tablicy hashujacej.

W wyniku dzialania ponizszego kodu, w |osoba **xx| jak i w |osoba **yy| beda znajdowac
sie wskazania na pointery do szukanych osob (niezaleznie, czy dana osoba wczesniej
byla rozpatrywana czy nie).

@<Zdobadz pointery do osob@>=
xx = (hashtab+getHash(X));
while((*xx) && (*xx)->name && strcmp((*xx)->name,X))
	xx = &((*xx)->n);
if((*xx)==NULL)
	(*xx) = new osoba(X);
yy = (hashtab+getHash(Y));
while((*yy) && (*yy)->name && strcmp((*yy)->name,Y))
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

Operacja laczenia wierzcholkow |**x@t$\ \rightarrow\ $@>**y|. Zalozenia
(utrzymane po wykonaniu kazdej petli):
{
\parindent = 60 pt
\item{1.} |x!=NULL!=y|.
\item{2.} |*x!=NULL|.
\item{3.} laczone wierzcholki nie sa jednoczesnie pelnymi osobami.
}

Operacja |join(**x,**y)| powoduje polaczenie osoby |**x| z osoba |**y| poprzez
wykonanie:
{
\parindent = 60 pt
\item{A1.} przepisanie dzieci osoby |**y| do osoby |**x|
\item{A2.} usuniecie zbednej osoby (wypelniajacej) |**y|, poprawienie wskaznika |*y|
by wskazywal |(*y)->p|
\item{A3.} wywolanie w gore drzewa (warunki sprawdzane w podanej kolejnosci):
\itemitem{A3.1.} gdy |*y==NULL| - zakonczenie
\itemitem{A3.2.} gdy |*x==NULL| - zamien ojca |**x| na ojca |**y|, popraw
wskaznik od ojca |**y| i zakoncz
\itemitem{A3.3.} gdy |**y| nie jest wypelniaczem - zamien ojcow miejscami i
|join()| na ojcach
\itemitem{A3.4.} wpp - polacz rodzicow
}

@<Definicje funkcji@>=
void join(osoba **x, osoba **y) {
	/*dbg*/printf("join\n");
	osoba *t, **u, *v;
	while(*y != NULL) {			/* A1.	Przepinanie dzieci */
		t = (*x)->c;			/* 	|t| - stary syn |**x| */
		(*x)->c = (*y)->c;		/* 	zastap synow |**x| przez
							synow |**y| */
		u = &((*x)->c);
		if(*u)				/* 	popraw |**r| u nowego syna |**x| */
			(*u)->r = u;
		while(*u) {			/* 	popraw wskazanie na ojca
							nowym synom |**x| */
			(*u)->p = (*x);
			u = &((*u)->s);
		}
		(*u) = t;			/* 	dolacz starych synow |**x| */
		if(t)				/* 	popraw |**r| u starego syna |**x| */
			t->r = u;
		if((*y)->r)			/* 	usun |*y| z listy synow jego ojca */
			(*((*y)->r)) = (*y)->s;
		if((*y)->s)			/* 	popraw |*r| u jego prawego brata */
			(*y)->s->r = (*y)->r;
		v = (*y)->p;			/* 	zapamietaj ojca |*y| w |*t| */
		delete (*y);			/* A2.	Usuniecie |*y| */
		y = &v;
		if((*x)->p == NULL && (*y)) {	/* A3.2. |**x| nie ma ojca */
			(*x)->p = v;		/* 	ustal |v| ojcem |**x| */
			(*x)->s = v->c;		/* 	dodaj |**x| do synow |v| */
			v->c = (*x);
			return;			/* 	zakoncz */
		}
		x = &((*x)->p);			/* ustal |x| na wskaznik na ojca od starego |**x| */
		if((*y) && (*y)->name != nn) {	/* A3.3. |*y| nie jest wypelniaczem */
			u = x; x = y; y = u;	/* 	zamien |x| i |y| miejscami */
		} 
	}
}



@ Operacja laczenia syna z ojcem.

Najpierw sprawdza (A1), czy |y| juz nie jest synem |x|. Gdy tak nie jest, to dopisuje |y|
do listy dzieci |x| i - o ile to konieczne - (A2) wywoluje |join| na rodzicach |x| i |y|.

TODO: (A1) poprzez |x->p == y|

@<Definicje funkcji@>=
void make_child(osoba *x, osoba *y) {
	/*dbg*/printf("make_child\n");
	osoba *t;
	if(x->p == y)				/* A1.	Sprawdzenie, czy |x| juz jest
						 	synem |y|... */
		return;				/* 	...jest wiec zakoncz */
	if(x->p)				/* 	|x| ma rodzine */
		join(&y,&(x->p));
	else {					/* 	|x| jest izolowany */
		t = y->c;
		y->c = x;
		x->p = y;
		x->r = &(y->c);
		x->s = t;
		if(t)
			t->r = &(x->s);
	}
}



@ Operacja laczenia braci.

Zalozenia:
{
\parindent = 60 pt
\item{1.} |x!=NULL!=y|
\item{2.} wejscie jest poprawne (nie powstana cykle etc)
}
Istnieje kilka przypadkow
{
\parindent = 60 pt
\item{A1.} zarowno |x| jak i |y| sa izolowane (bez rodziny)
\item{A2.} dokladnie jedno z |x| i |y| jest izolowane
\item{A3.} |x| i |y| posiadaja (rozne) rodziny
}

@<Definicje funkcji@>=
void make_sibling(osoba *x, osoba *y) {
	/*dbg*/printf("make_sibling\n");
	osoba *t;
	if(!(x->r) && !(y->r)) {		/* A1. Przypadek prosty */
		t = new osoba;			/* 	tworzymy ojca-wypelniacza */
		t->c = x;			/* 	podpinamy |x|, |y|
						 	jako synow */
		x->r = &(t->c);
		x->s = y;
		y->r = &(x->s);
		x->p = y->p = t;
	} else if(!(x->r) || !(y->r)) {		/* A2. Przypadek sredni */
		if(!(x->r)) {			/* 	ustalamy |x| - ma rodzine */
			t = x; x = y; y = t;
		}
		t = x->p->c;
		x->p->c = y;
		y->r = &(x->p->c);
		y->s = t;
		t->r = &(y->s);

	} else {				/* A3. Przypadek trudny... */
		if(x->p->name == nn)		/* 	...znowu okazal sie latwy
							dzieki |join()| */
			join(&y,&x);
		else
			join(&x,&y);
	}
}



@ Operacja laczenia dziadka z wnukiem.

@<Definicje funkcji@>=
void make_grandparent(osoba *x, osoba *y) {
	/*dbg*/printf("make_grandparent\n");
	osoba *t;
	if(y->p)
		t = y->p;
	else {
		t = new osoba;
		y->p = t;
		t->c = y;
		y->r = &(t->c);
	}
	make_child(t,x);
}



@ Nienapisane jeszcze operacje...

@<Definicje funkcji@>=
void make_cousin(osoba *x, osoba *y) {
	/*dbg*/printf("make_cousin\n");
	osoba *t,*u;
	if(!(t = x->p)) {
		t = new osoba;
		t->c = x;
		x->p = t;
		x->r = &(t->c);
	}
	if(!(u = y->p)) {
		u = new osoba;
		u->c = y;
		y->p = u;
		y->r = &(u->c);
	}
	if(u->name!=nn)
		make_sibling(u,t);
	else
		make_sibling(t,u);
}


@q ================================================================================ @>




@*References.
\bibstart

\bibitem{bern}
Algorytm djb2 autorstwa Donalda Bernsteina.

Kod znaleziony na stronie
\pdfURL{http://www.cse.yorku.ca/\~{}oz/hash.html}.
\bibend
