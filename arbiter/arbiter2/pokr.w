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
\def\bcpss{2}



@* Naglowek programu.

Pliki nagłówkowe i definicje stalych uzytych w programie.

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





@ Zmienne globalne.

Zmienna |input| (o dlugosci |INPUTLEN|) przechwytuje caly napis wejsciowy. Ten nastepnie jest
rozbijany na |X| (imie i nazwisko osoby X), |R| (relacja miedzy X a Y) oraz |Y|
(imie i nazwisko osoby Y). Po przetworzeniu do |X| trafia polaczone imie i nazwisko
(analogicznie |Y|).

|int n| jest licznikiem osob obecnie wystepujacych w drzewie - zarowno wypelniaczy
jak i tych pelnych, wymienionych z imienia na wejsciu.
|int ecnt| wskazuje na nastepne wolne miejsce w tablicy |osoba *E@t$\ldots$@>|.
|int tid| (unikalnie) numeruje poddrzewa.

|osoba *hashtab[@t$\ldots$@>]| jest tablica hashujaca wspomagajaca wyszukiwanie
rozpatrywanych osob. Wyszukiwanie jest pierwsza operacja wykonywana zarowno przy
przetwarzaniu opisu rodowego jak i przy przetwarzaniu zapytania.

@c
class infoSet;
class osoba;
char input[INPUTLEN], X[INPUTLEN], Xa[INPUTLEN], R[INPUTLEN], Y[INPUTLEN], Ya[INPUTLEN];
int n = 0, tid = 0;
int ecnt;
osoba *hashtab[HASHSIZE], **xx,**yy, *r;




@ Procedura main.

Zadaniem |main| jest wczytanie danych wejsciowych i wywolywanie odpowiednich instrukcji
(w zaleznosci od sytuacji).

@c
@<Definicje struktur@>@;
@<Definicje funkcji@>@;
int main() {
	@#
	@<Inicjacja zmiennych@>@;




@ Przetwarzanie danych.

Wczytuje opis relacji z wejscia.

Konczy petle w dwoch wypadkach: gdy nie ma juz nic na wejsciu lub gdy rozpoczeto
podawanie zapytan o pokrewienstwo osob (pytanie o najnizszego wspolnego przodka).

@c
while( 1 ) {
	if( fgets(input,INPUTLEN,stdin) == NULL )
		break;
	@<Wstepnie przetworz tekst@>@;
	if( R[0]==':' )
		break;
	@<Zdobadz pointery do osob@>@;
	@<Dodaj brakujace osoby@>@;	/* tylko jesli dane osoby wczesniej nie wystapily */
	@<Powiaz osoby na podstawie |*R|@>@;
}




@ Rozbijanie tekstu z |input| na |X|, |R|, |Y|.

@<Wstepnie przetworz tekst@>=
sscanf(input," %s %s %s %s %s ",X,Xa,R,Y,Ya);
strcat(X," ");	/* polacz |X| i |Xa| w jedno */
strcat(X,Xa);
strcat(Y," ");	/* polacz |Y| i |Ya| w jedno */
strcat(Y,Ya);




@ Przetwarzanie zapytan.

@c
if(R[0] == ':') {
	do {
		@<Wstepnie przetworz tekst@>@;
		@<Zdobadz pointery do osob@>@;
		if((*xx)->i == NULL && (*yy)->i == NULL) {
						/* Ani dla |**xx| ani |**yy| nie zostal
						   wykonany preprocessing */
			@<Preprocessing poddrzewa |**x|@>@;
			if((*yy)->i == NULL)	/* dla |**yy| nadal nie zostal wykonany
						   preprocessing zatem nie moze miec z |**xx|
						   wspolnego przodka */
				printf("NN\n");
			else 			/* wyznacz LCA na podstawie RMQ */
				printf("%s\n",(*xx)->i->E[RMQ((*xx)->i,(*xx)->e,(*yy)->e)]->name);
		} else if((*yy)->i != (*xx)->i)	/* |**x| i |**y| sa w innych poddrzewach (lub
						 dla |**y| nie zostal wykonany preprocessing) */
			printf("NN\n");
		else
			printf("%s\n",(*xx)->i->E[RMQ((*xx)->i,(*xx)->e,(*yy)->e)]->name);
	} while( fgets(input,INPUTLEN,stdin) != NULL );
}




@ Zakonczenie programu

W sumie przydaloby sie oczyscic pamiec dokladniej ale co tam :P

@c
	return 0; @#
}





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
prawego brata.
W |osoba **r| zapamietany jest adres wskaznika na |*this| od ojca lub
lewego brata.

|int i| jest unikalnym numerem przydzielanym przez |globTreeIdCnt| dla kazdego spojnego
obszaru.
|l| okresla glebokosc, na ktorej znajduje sie dana osoba. Sluzy takze jako
wskaznik koloru przy przechodzeniu drzewa przez DFS: wartosc |t=0| oznacza, ze
wierzcholek byl nieodwiedzony (bialy), |t<0| - jest przetwarzany (szary),
|t>0| - zostal juz przetworzony (czarny).
|e| wskazuje na pozycje reprezentanta danej osoby w tablicy |**E|.


@<Definicje struktur@>=
char nn[] = {'N','N',0};
class osoba {
public:
	char *name;		/* imie i nazwisko */
	osoba  *n,		/* w tablicy hashujacej: nastepny element kolizji */
	       *p, *c, *s, **r;	/* w drzewie:		 ojciec. syn, prawy brat,
				 	wskaznik na wskaznik na siebie od lewego brata lub ojca */
	infoSet *i;
	int l, e;		/* w LCA:		 glebokosc danej osoby
				   	w poddrzewie genealogicznym, pozycja reprezentanta */
	@#
	@#
	osoba()@+ : name(NULL),
		n(NULL), p(NULL), c(NULL), s(NULL), r(NULL),
		i(NULL), l(0), e(0) {
		name = nn; @+
	}
	osoba(char *in)@+ : name(NULL),
		n(NULL), p(NULL), c(NULL), s(NULL), r(NULL),
		i(NULL), l(0), e(0) {
		name = new char[strlen(in)+1];
		strcpy(name,in);
	}
	~osoba()@+ { @+
		if(name!=nn) delete [] name; @+
	}
};




@q ================================================================================ @>






@* Tablica hashujaca.

Na wstepie wymaga tylko wyczyszczenia.

@<Inicjacja zmiennych@>=
for(int i=0;i<HASHSIZE;++i)
	hashtab[i]=NULL;



@ Przeszukiwanie tablicy hashujacej.

W wyniku dzialania ponizszego kodu, w |osoba *xx| jak i w |osoba *yy| beda znajdowac
sie wskazania na pointery do szukanych osob (o ile sa w tablicy).

@<Zdobadz pointery do osob@>=
xx = hashtab+getHash(X);
while(*xx && strcmp((*xx)->name,X))
	xx = &((*xx)->n);
yy = hashtab+getHash(Y);
while(*yy && strcmp((*yy)->name,Y))
	yy = &((*yy)->n);




@ Dodaj jesli danych osob nie ma.

Gdy brakuje jakichs osob w tablicy hashujacej to je dodaj.

@<Dodaj brakujace osoby@>=
if((*xx)==NULL) {
	(*xx) = new osoba(X);
	++n;
}
if((*yy)==NULL) {
	(*yy) = new osoba(Y);
	++n;
}




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

Operacja laczenia wierzcholkow |*x@t$\ \rightarrow\ $@>*y|. Zalozenia
i jednoczesnie niezmiennik petli: |x!=NULL|

Operacja |join(*x,*y)| powoduje polaczenie osoby |*x| z osoba |*y| poprzez
wykonanie:
{
\parindent = 60 pt
\item{A1.} przepisanie dzieci osoby |*y| do osoby |*x|
\item{A2.} usuniecie zbednej osoby (wypelniajacej) |*y|, poprawienie wskaznika |y|
by wskazywal |y->p|
\item{A3.} wywolanie w gore drzewa (warunki sprawdzane w podanej kolejnosci):
\itemitem{A3.1.} gdy |y==NULL| - zakonczenie
\itemitem{A3.2.} gdy |x==NULL| - zamien ojca |*x| na ojca |*y|, popraw
wskaznik od ojca |*y| i zakoncz
\itemitem{A3.3.} gdy |*y| nie jest wypelniaczem - zamien ojcow miejscami i
|join(@t$\ldots$@>)| na ojcach
\itemitem{A3.4.} wpp - polacz rodzicow
}

@<Definicje funkcji@>=
void join(osoba *x, osoba *y) {
	osoba *t, **u, *v;
	while(y != NULL) {			/* A1.	Przepinanie dzieci */
		if(x == y)
			return;
		t = x->c;			/* 	|t| - stary syn |**x| */
		x->c = y->c;			/* 	zastap synow |**x| przez
							synow |**y| */
		y->c = NULL;			/* 	odcinamy synow od |**y| */
		u = &(x->c);
		if(*u)				/* 	popraw |**r| u nowego syna |**x| */
			(*u)->r = u;
		while(*u) {			/* 	popraw wskazanie na ojca
							nowym synom |**x| */
			(*u)->p = x;
			u = &((*u)->s);
		}
		(*u) = t;			/* 	dolacz starych synow |**x| */
		if(t)				/* 	popraw |**r| u starego syna |**x| */
			t->r = u;
		if(y->r)			/* 	usun |*y| z listy synow jego ojca */
			(*(y->r)) = y->s;
		if(y->s)			/* 	popraw |*r| u jego prawego brata */
			y->s->r = y->r;
		v = y->p;			/* 	zapamietaj ojca |*y| w |*t| */
		delete y;			/* A2.	Usuniecie |*y| */
		--n;
		y = v;
		if(x->p == NULL && y) {		/* A3.2. |**x| nie ma ojca */
			x->p = y;		/* 	ustal |v| ojcem |**x| */
			x->r = &(y->c);
			x->s = y->c;		/* 	dodaj |**x| do synow |v| */
			if(x->s)
				x->s->r = &(x->s);
			y->c = x;
			return;			/* 	zakoncz */
		}
		x = x->p;			/* ustal |x| na wskaznik na ojca od starego |**x| */
		if(y && y->name != nn) {	/* A3.3. |*y| nie jest wypelniaczem */
			v = x; x = y; y = v;	/* 	zamien |x| i |y| miejscami */
		} 
	}
}



@ Operacja laczenia syna z ojcem.

Najpierw sprawdza (A1), czy |y| juz nie jest synem |x|. Gdy tak nie jest, to dopisuje |y|
do listy dzieci |x| i - o ile to konieczne - (A2) wywoluje |join| na rodzicach |x| i |y|.

TODO: (A1) poprzez |x->p == y|

@<Definicje funkcji@>=
void make_child(osoba *x, osoba *y) {
	osoba *t;
	if(x->p == y)				/* A1.	Sprawdzenie, czy |x| juz jest
						 	synem |y|... */
		return;				/* 	...jest wiec zakoncz */
	if(x->p) {				/* 	|x| ma rodzine */
		if(y->name != nn)
			join(y,x->p);
		else
			join(x->p,y);
	} else {				/* 	|x| jest izolowany */
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
	osoba *t;
	if(!(x->p) && !(y->p)) {		/* A1. Przypadek prosty */
		t = new osoba;			/* 	tworzymy ojca-wypelniacza */
		++n;
		t->c = x;			/* 	podpinamy |x|, |y|
						 	jako synow */
		x->r = &(t->c);
		x->s = y;
		y->r = &(x->s);
		x->p = y->p = t;
	} else if(!(x->p) || !(y->p)) {		/* A2. Przypadek sredni */
		if(!(x->p)) {			/* 	ustalamy |x| - ma rodzine */
			t = x; x = y; y = t;
		}
		t = x->p->c;
		x->p->c = y;
		y->p = x->p;
		y->r = &(x->p->c);
		y->s = t;
		t->r = &(y->s);

	} else {				/* A3. Przypadek trudny... */
		if(x->p->name == nn)		/* 	...znowu okazal sie latwy
							dzieki |join()| */
			join(y->p,x->p);
		else
			join(x->p,y->p);
	}
}



@ Operacja laczenia dziadka z wnukiem.

@<Definicje funkcji@>=
void make_grandparent(osoba *x, osoba *y) {
	osoba *t;
	if(y->p)
		t = y->p;
	else {
		t = new osoba;
		++n;
		y->p = t;
		t->c = y;
		y->r = &(t->c);
	}
	make_child(t,x);
}



@ Operacja laczenia osoby z jej kuzynem.

@<Definicje funkcji@>=
void make_cousin(osoba *x, osoba *y) {
	osoba *t,*u;
	if(!(t = x->p)) {
		t = new osoba;
		++n;
		t->c = x;
		x->p = t;
		x->r = &(t->c);
	}
	if(!(u = y->p)) {
		u = new osoba;
		++n;
		u->c = y;
		y->p = u;
		y->r = &(u->c);
	}
	if(u->name!=nn)
		make_sibling(u,t);
	else
		make_sibling(t,u);
}



@ Odpalanie mechanizmow wiazacych osoby w drzewie.

Na wejsciu dostalismy opis relacji dwoch osob: |**xx| i |**yy|. Teraz rozrozniamy,
jakiego typu jest to relacja.

@<Powiaz osoby na podstawie |*R|@>=
switch(R[1]) {
	case 'r': if(R[5]=='p') @#
			make_grandparent(*xx,*yy);
		else @#
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





@q ================================================================================ @>


@* Wyznaczanie LCA/RMQ.

Wyznaczanie najnizszego wspolnego przodka (Lowest Common Ancestor) mozna sprowadzic
do problemu znajdowania minimum przedzialu (Range Minimum Query).

@d MTAB (r->i->M)
@d ETAB (r->i->E)
@<Preprocessing poddrzewa |**x|@>=
r = *xx;
while(r->p)
	r = r->p;	/* Znajdz korzen poddrzewa */
r->i = new infoSet(r);
dfs(r,1);		/* wypelnia tablice |osoba *E[1@t$\ldots$@>N]| */
for(int i=0;i<2*(r->i->N)-1;++i)
	r->i->M[i][0] = i;

/* (dynamicznie) wypelnia tablice |int M[1@t$\ldots$@>N][1@t$\ldots$@>lN]| */
for(int j=1, i, k=1;j<=(r->i->lN);++j,k<<=1) {		/* niezmiennik: |@t$k=2^{j-1}$@>| */
	for(i=0;i<2*(r->i->N)-1;++i) {
		if(i+k<2*(r->i->N)-1 && ETAB[MTAB[i+k][j-1]]->l < ETAB[MTAB[i][j-1]]->l)
			MTAB[i][j] = MTAB[i+k][j-1];
		else
			MTAB[i][j] = MTAB[i][j-1];
	}
}



@ Wyznaczanie RMQ poddrzewa.

@<Definicje funkcji@>=
int RMQ(infoSet *is, int a, int b) {
	int k,l;
	if(a>b) {
		k=a; a=b; b=k;
	}
	for(k=0,l=1;l+a<=b;l<<=1,++k) ;
			/* Wyznaczamy |k=@t$\left\lceil \log_2 (j-i+1) \right\rceil$@>|
			   oraz |l=@t$2^k$@>| */
	--k;
	l>>=1;
	if(is->E[is->M[a][k]]->l < is->E[is->M[b-l][k]]->l)
		return is->M[a][k];
	return is->M[b-l][k];
}



@ Struktura przechowujaca wyniki preprocessingu dla poddrzew.

@<Definicje struktur@>=
int dfs_licz(osoba *x) {
	int res = 1;
	for(osoba *it = x->c; it!=NULL; it = it->s)
		res += dfs_licz(it);
	return res;
}
class infoSet{
public:
	osoba **E;
	int **M;
	int N,lN;
	infoSet(osoba *in) : E(NULL), M(NULL), N(0), lN(0) {
		int i,j,k;
		N = dfs_licz(in);		/* wyznacz licznosc poddrzewa */
		k = 2*N-1;
		for(i=1,j=0; i<k; i<<=1,++j)
			if(i & k) lN = j;
			/* dla |N!=0|: |lN=@t$\left\lfloor\log_2 (2N-1)\right\rfloor$@>| */
		E = new osoba*[2*N-1];
		M = new int*[2*N-1];
		for(i=0;i<2*N-1;++i)
			M[i] = new int[lN+1];
	}
	~infoSet() {
		delete [] E;
		if(M) {
			for(int i=0;i<N;++i)
				delete [] M[i];
			delete [] M;
		}
	}
};

@ Funkcja przegladania drzewa.

Wypelnia jednoczesnie tablice |osoba *E[@t$1\ldots 2N-1$@>]|

@<Definicje funkcji@>=
void dfs(osoba *x,int lvl) {
	x->i = r->i;
	x->e = ecnt;
	x->l = -(lvl++);
	x->i->E[ecnt++] = x;
	for(osoba *it = x->c; it!=NULL; it = it->s) {
		dfs(it,lvl);
		x->i->E[ecnt++] = x;
	}
	x->l = -(x->l);
}





@q ================================================================================ @>




@*References.
\bibstart

\bibitem{bern}
Algorytm djb2 autorstwa Donalda Bernsteina.

Kod znaleziony na stronie
\pdfURL{http://www.cse.yorku.ca/\~{}oz/hash.html}.
\bibitem{bcpss}
Michael~A.~Bender, Martín~Farach-Colton, Giridhar~Pemmasani, Steven~Skiena, Pavel~Sumazin.
Lowest Common Ancestors in Trees and Directed Acyclic Graphs.
\bibend
