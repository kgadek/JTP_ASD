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
\def\knuth{1}
\def\bern{2}
\def\jwalker{3}


@* Rdzen programu.

Zadaniem |main|a jest wczytanie danych wejsciowych i wywolywanie odpowiednich instrukcji
(w zaleznosci od sytuacji).

Na wejsciu bedzie maksymalnie |8000000| osob (bardzo luzne oszacowanie).

|INPUTLEN| definiuje wielkosc alokowanego miejsca dla imienia i nazwiska.

@d INPUTLEN 1000
@d MEMALLOC(type) (new type)
@d MEMNALLOC(type,N) (new type[N])
@d MEMFREE(obj) delete obj
@d MEMNFREE(obj) delete [] obj
@c
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

@<Definicje struktur@>@;
@<Definicje funkcji@>@;
@<Zmienne globalne@>@;

int main() {
	while( fgets(input,INPUTLEN,stdin) != NULL ) {	/* fgets i sscanf sa "bezpieczne" */
		@<Wstepnie przetworz tekst@>@;
		if( !strcmp(R,":") ) {
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
osoba *xx1, *yy1;	/* pointery na aktualnie przetwarzane obiekty |osoba|... */
avlNode *avlR = NULL;		/* korzen drzewa AVL */



@ Rozbijanie tekstu z |input| na |X|, |R|, |Y|.

@<Wstepnie przetworz tekst@>=
sscanf(input," %s %s %s %s %s ",X,Xa,R,Y,Ya);
strcat(X," ");	/* polacz X i Xa w jedno */
strcat(X,Xa);
strcat(Y," ");	/* polacz Y i Ya w jedno */
strcat(Y,Ya);





@q ================================================================================ @>





@* Klasa |osoba|.

Przechowuje imie i nazwisko oraz wskazniki do ojca i synow.

Ważne jest odpowiednie wywolywanie destruktora. Przy niszcze

@<Definicje struktur@>=
class osoba {
public:
	char *X;		/* imie i nazwiski */
	int hash;		/* hash */
	osoba *p, *l, *r;	/* odpowiednio: parent, lewy, prawy */
	osoba() : X(NULL), hash(0), p(NULL), l(NULL), r(NULL) {}
	~osoba() {
		if(X != NULL) free(X);
	}
};



@ Funkcja hashujaca djb2\cite{bern}.

@<Definicje funkcji@>=
int getHash(char *x) {
	int ret = 5381;
	while(*x)
		ret = ((ret << 5) + ret) ^ (*(x++));
	/* |@t$hash_i = hash_{i-1}*33 \oplus x[i]$@>| */
	return ret;
}





@q ================================================================================ @>





@* Drzewo wyszukiwania.

Drzewo AVL z operacjami |avlNode* Insert(...)| i |avlNode* Query(...)|.

Kolejnosc wierzcholkow: |x| jest lewym synem |y| $\iff$
|(x->hash < y->hash) || ((x->hash == y->hash) && strcmp(x->X,y->X)<0) |.



@ Klasa |avlNode|.

Posiada konstruktor domyslny i inicjujacy.

@<Definicje struktur@>=
class avlNode {
public:
        osoba *key;                     /* klucz-wskaznik na obiekt |osoba| */
        int bal;                        /* wartosc balansu (potrzebne 3 bity) */
        avlNode *l[2];           	/* pointery do dzieci w drzewie */
	avlNode() : key(NULL), bal(0) {
		l[0]=l[1]=NULL;
	}
	avlNode(char *x,int h) : bal(0) {
		int a = strlen(x);
		key->hash = h;
		key = MEMALLOC(osoba);
		key->X = MEMNALLOC(char,a+1);
		strncpy(key->X,x,a+1);
		assert(key->X[a] == '\0');
		l[0]=l[1]=NULL;
	}
	~avlNode() {
		if(key != NULL) MEMFREE(key);
	}
};



@ Porownywanie osob z obiektami |osoba|.

@<Definicje funkcji@>=
int osobaLt(char *x, int h, osoba *y) {
	if(h != y->hash)
		return h < y->hash;
	return strcmp(x,y->X);
}
int osobaGtEq(char *x, int h, osoba *y) {
	if
}
int osobaEq(char *x, int h, osoba *y) {
	return (h == y->hash) && strcmp(x,y->X);
}



@ Dodawanie do drzewa.

Napisane na podstawie The~Art~of~Computer~Programming~\xcite{knuth}{rozdzial 6.2.3}
korzystajac takze ze wskazowek Julienne Walker\cite{jwalker}.

@<Definicje funkcji@>=
avlNode* avlInsert(avlNode **R, char *k, int hash) {
	avlNode *head, *p, *q, *r, *s, *t, *u;
	int a,d;
	if(*R == NULL)						/* Przypadek specjalny: puste drzewo */
		return (*R) = new avlNode(k,hash);	/* zainicjuj i ustaw wartosci */
	u = NULL;					/* to aby sie kompilator nie rzucal */
	head = new avlNode; 				/* utworzenie HEAD */
	head->l[0] = *R;					/* A1. inicjacja */
	t = head;
	q = p = s = *R;
	while(q != NULL) {					/* A2. szukanie */
		if(osobaEq(k,hash,p->key))			
			return p;		/* znaleziono wiec nie dodawaj tylko zwroc wskaznik */
		d = (k > p->key);
		q = p->l[d];					/* A3/A4. przejscie lewo/prawo */
		if(q == NULL) {
			p->l[d] = u = q = new avlNode;
			avlInit(q);
			break;
		} else if(q->bal != 0) {
			t = p;
			s = q;
		}
		p = q;
	}
	q->key = k;						/* A5. wstawianie */
	r = p = s->l[ k > s->key ];				/* A6. poprawa wartosci balansow */
	while(p!=q) {				/* dla kazdego wierzcholka miedzy P a Q (bez Q) */
		d = (k > p->key);		/* 	wybierz kierunek */
		p->bal = 2*d - 1;		/* 	popraw balans */
		p = p->l[d];			/* 	przejdz dalej */
	}
	q = s;					/* zapamietaj s (to bedzie nowy rodzic rotowanego poddrzewa) */
	a = (k < s->key)?-1:1;					/* A7. ustawienie balansu drzewa */
	if(s->bal == 0) {				/* A7.i - lekkie zaburzenie balansu (|+1| lub |-1|) */
		s->bal = a;				/* 	czyli drzewo uroslo */
		return u;
	} else if(s->bal == -a) {			/* A7.ii - wstawienie poprawilo balans drzewa */
		s->bal = 0;
		return u;
	}						/* A7.iii - zaburzenie balansu (|+2| lub |-2|) */
	if(r->bal == a ) {				/* A8. pojedyncza rotacja */
		d = a<0?0:1;			/* wybierz kierunek */
		p = r;				/* rotuj w lewo/prawo (|a| = |+1|/|-1|) wokol |s| */
		s->l[d] = r->l[!d];
		r->l[!d] = s;
		s->bal = r->bal = 0;
	} else {					/* A9. podwojna rotacja */
		d = a<0?0:1;
		p = r->l[1-d];			/* rotuj w prawo/lewo (|a| = |+1|/|-1|) wokol |r| */
		r->l[!d] = p->l[d];		/* a nastepne */
		p->l[d] = r;			/* rotuj w lewo/prawo (|a| = |+1|/|-1|) wokol |r| */
		s->l[d] = p->l[!d];
		p->l[!d] = s;		/* wartosci balansu |s| i |r| zaleza od podprzypadkow:
						(|s->bal|,|r->bal|) = $\left\{\matrix{
							(-a,0) & p->bal = a \hfill \cr
							(0,0) & p->bal = 0 \hfill \cr
							(0,+a) & p->bal = -a\hfill
						}\right.$ */
		s->bal = r->bal = 0;
		if(p->bal == a)
			s->bal = -a;
		else if(p->bal == -a)
			r->bal = a;
	}
	if(head == t)			/* ten fragm. zerznalem (problemy z podmiana korzenia) [2] */ 
		(*R) = p;			/* gdy rotacja zmienila korzen to operuj na korzeniu */
	else
		t->l[s == t->l[1]] = p;		/* wpp popraw wskazanie od ojca P */
	MEMFREE(head);				/* pozbycie sie tymczasowego HEAD-a */
	return u;				/* zwroc wsk. do dodanego wierzcholka */
}



@q ================================================================================ @>





@* Odpowiedz na query.

Zaklepac LCA.

@<Query@>=


@*References.
\bibstart

\bibitem{knuth}
Donald Knuth, Sztuka Programowania, Tom 3 (oryg. The Art of Computer Programming).
\bibitem{bern}
Algorytm djb2 autorstwa Donalda Bernsteina.

Kod znaleziony na stronie
\pdfURL{http://www.cse.yorku.ca/\~{}oz/hash.html}.
\bibitem{jwalker}
Julienne Walker,
$www.eternallyconfuzzled.com/tuts/datastructures/jsw_tut_avl.aspx$.
\bibend
