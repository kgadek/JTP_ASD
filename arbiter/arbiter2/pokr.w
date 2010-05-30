\def\cee/{C}
\def\cpp/{\cee/{\tt++}}
\input texdraw


@* Rdzen programu.

Zadaniem |main|a jest wczytanie danych wejsciowych i wywolywanie odpowiednich instrukcji
(w zaleznosci od sytuacji).

Na wejsciu bedzie maksymalnie |8000000| osob (bardzo luzne oszacowanie).

|INPUTLEN| definiuje wielkosc alokowanego miejsca dla imienia i nazwiska.

@d INPUTLEN 1000
@d MEMALLOC(type) ((type*)malloc(sizeof(type)))
@d MEMNALLOC(type,N) ((type*)malloc((unsigned int)N*sizeof(type)))
@d MEMFREE(obj) free(obj)
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
		/*dbg*/printf("_____________________________\n");
		/*dbg*/printf("X: %s\n",X);
		/*dbg*/printf("R: %s\n",R);
		/*dbg*/printf("Y: %s\n",Y);
		@<Zdobadz wskazniki do osob@>@;
		if( !strcmp(R,":") ) {
			@<Query@>@;
		} else {
		}
	}
	@<Czyszczenie pamieci@>@;
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
avlNode *xx2, *yy2;	/* ...jak i przechowujace je obiekty |avlNode| */
avlNode *avlR;		/* korzen drzewa AVL */



@ Rozbijanie tekstu w |input| na |X|, |R|, |Y|.

@<Wstepnie przetworz tekst@>=
sscanf(input," %s %s %s %s %s ",X,Xa,R,Y,Ya);
strcat(X," ");	/* polacz X i Xa w jedno */
strcat(X,Xa);
strcat(Y," ");	/* polacz Y i Ya w jedno */
strcat(Y,Ya);



@ Ustawianie pointerow.

Kod dzieli sie na 2 czesci:
\item{1.} Utworzenie (tymczasowych?) obiektow |osoba|.
\item{2.} Szukanie powyzszego obiektu w drzewie.
\item\item{2.1.} Jesli nie istnieje - dodaj do drzewa.
\item\item{2.2.} Jesli istnieje - usuniecie tymczasowego obiektu |osoba| i poprawienie
pointera.
Powtorz powyzsze czynnosci dla drugiej osoby.

@<Zdobadz wskazniki do osob@>=
xx1 = MEMALLOC(osoba);		/* 1, */
xx1->X = MEMNALLOC(char,strlen(X)+1);
strcpy(xx1->X,X);
xx1->X = X;
xx1->hash = hashOsoba(X);
xx2 = avlQuery(avlR,xx1);	/* 2. */
/*dbg*/printf("avlQuery>%s< : %d\n",X,xx2!=NULL);
if(!xx2) {			/* 2.1. */
	/*dbg*/printf("\tdodaje >%s<\n",X);
	xx2 = avlInsert(&avlR,xx1);
} else {
	MEMFREE(xx1);		/* 2.2 */
	xx1 = xx2->key;
}
assert(xx1->X == X);

yy1 = MEMALLOC(osoba);
yy1->X = MEMNALLOC(char,strlen(Y)+1);
strcpy(yy1->X,Y);
yy1->hash = hashOsoba(Y);
yy2 = avlQuery(avlR,yy1);
/*dbg*/printf("avlQuery>%s< : %d\n",Y,yy2!=NULL);
if(!yy2) {
	/*dbg*/printf("\tdodaje >%s<\n",Y);
	yy2 = avlInsert(&avlR,yy1);
} else {
	MEMFREE(yy1);
	yy1 = yy2->key;
}
assert(yy1->X == Y);



@ Czyszczenie pamieci.

@<Czyszczenie pamieci@>=
avlFree(&avlR);		/* czysc wszystkie obiekty |avlNode| i |osoba| */



@* Klasa |osoba|.

Przechowuje imie i nazwisko oraz wskazniki do ojca i synow, definiuje tez funkcje
porownujaca |int operator<(osoba const &) const|. Destruktor zaklada, ze czyszczenie
pamieci jest odgorne od |avlNode::~avlNode()|.

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
	int operator<(osoba const *) const;
};



@ Operator mniejszosci klasy osoba.

@<Definicje funkcji@>=
int osoba::operator<(osoba const *x) const {
	return (hash < x->hash) || ((hash == x->hash) && strcmp(X,x->X)<0);
}






@* Drzewo hashujace.

Drzewo AVL z operacjami |avlNode* Insert(...)| i |avlNode* Query(...)|.

Ustalona kolejnosc wierzcholkow: |x| jest lewym synem |y| $\iff$
|(x->hash < y->hash) || ((x->hash == y->hash) && strcmp(x->X,y->X)<0) |.



@ Liczenie hash-a osoby.

@<Definicje funkcji@>=
int hashOsoba(char *x) {
	return 0;
}



@ Porownywanie osob.

|osobaCmp(x,y)| =
$\left\{\matrix{-1\hfill&x>y\hfill\cr0\hfill&x=y\hfill\cr+1\hfill&x<y\hfill}\right.$

@<Definicje funkcji@>=
int osobaCmp(osoba *x, osoba *y) {
	int v;
	if(x->hash != y->hash)
		return x->hash < y->hash?+1:-1;
	assert(x->X != NULL);
	v = strcmp(x->X,y->X);
	if(v==0)
		return v;
	return v>0?-1:+1;
}



@ Struktura drzewa.

Trzyma wskaznik do struktury |osoba|. Zawiera tez |int hash| imienia i nazwiska
(szybsze szukanie).

@<Definicje struktur@>=
struct avlNode {
        osoba *key;                     /* klucz w węźle */
        int bal;                        /* wartosc balansu (potrzebne 3 bity) */
        struct avlNode *l[2];           /* pointery do dzieci */
};



@ Inicjacja wierzcholka.

@<Definicje funkcji@>=
void avlInit(avlNode *x) {
        x->bal = 0;
        x->l[0] = x->l[1] = NULL;
	x->key = NULL;
}



@ Czyszczenie pamieci.

Czysci tez wskazywany przez |key| obiekt |osoba|.

@<Definicje funkcji@>=
void avlFree(avlNode **x) {
        if((*x)==NULL)
                return;
	if((*x)->key) {
		MEMFREE((*x)->key);
		(*x)->key = NULL;
	}
        avlFree(&((*x)->l[0]));
        avlFree(&((*x)->l[1]));
        MEMFREE(*x);
}



@ Szukanie w drzewie.

@<Definicje funkcji@>=
avlNode* avlQuery(avlNode *R, osoba *k) {
	assert(k != NULL);
        while(R && osobaCmp(R->key,k)!=0) {
                R = R->l[k < R->key];
	}
        return R;
}



@ Dodawanie do drzewa.

Algorytm top-down (dwuprzebiegowy) na drzewie AVL.
Dodaje |avlNode| wskazujacy na obiekt typu |osoba| do drzewa o ile wczesniej
dana osoba tam nie wystepowala.
Zwraca wskaznik na obiekt |avlNode| (niezaleznie czy wczesniej istnial czy nie).
Zaklada, ze dodawany obiekt ma juz policzony |hash|.


@<Definicje funkcji@>=
avlNode* avlInsert(avlNode **R, osoba *k) {
        avlNode *head, *p, *q, *r, *s, *t, *u;
        int a,d;
        if(*R == NULL) {                                        /* Przypadek specjalny:
								   puste drzewo */
                (*R) = MEMALLOC(avlNode);       /* utworz node */
                avlInit(*R);                    /* zainicjuj */
                (*R)->key = k;                  /* ustaw mu wartosc */
                return *R;
        }
        u = NULL;                               /* aby sie kompilator nie rzucal */
        head = MEMALLOC(avlNode);               /* utworzenie |HEAD| */
        avlInit(head);
        head->l[0] = *R;                                        /* A1. inicjacja */
        t = head;
        q = p = s = *R;
        while(q != NULL) {                                      /* A2. szukanie */
                if(osobaCmp(k,p->key)==0)      /* znaleziono; jest w drzewie wiec nie dodawaj */
                        return p;
                d = (p->key < k);
                q = p->l[d];                                    /* A3/A4. przejscie lewo/prawo */
                if(q == NULL) {
                        p->l[d] = u = q = MEMALLOC(avlNode);
                        avlInit(q);
                        break;
                } else if(q->bal != 0) {
                        t = p;
                        s = q;
                }
                p = q;
        }
        q->key = k;                                             /* A5. wstawianie */
        r = p = s->l[ s->key < k ];                             /* A6. poprawa wartosci balansow */
        while(p!=q) {                           /* $\forall p^\prime:$ $p^\prime$
						   jest miedzy |p| a |q| (poza |q|) */
                d = p->key < k;                 /*      wybierz kierunek */
                p->bal = 2*d - 1;               /*      popraw balans */
                p = p->l[d];                    /*      przejdz dalej */
        }
        q = s;                                  /* zapamietaj s (to bedzie nowy rodzic rotowanego
						   poddrzewa) */
        a = k < s->key?-1:1;                                    /* A7. ustawienie balansu drzewa */
        if(s->bal == 0) {                               /* A7.i - lekkie zaburzenie balansu
							   (+1 lub -1) co znaczy, ze drzewo uroslo */
                s->bal = a;
                return u;
        } else if(s->bal == -a) {                       /* A7.ii - wstawienie poprawilo balans
							   drzewa */
                s->bal = 0;
                return u;
        }                                               /* A7.iii - zaburzenie balansu
							   (+2 lub -2) */
        if(r->bal == a ) {                              /* A8. pojedyncza rotacja */
                d = a<0?0:1;                    /* wybierz kierunek */
                p = r;                          /* rotuj w lewo/prawo (a = +1/-1) wokol
						   wierzcholka S */
                s->l[d] = r->l[!d];
                r->l[!d] = s;
                s->bal = r->bal = 0;
        } else {                                        /* A9. podwojna rotacja */
                d = a<0?0:1;
                p = r->l[1-d];                  /* rotuj w prawo/lewo (a = +1/-1) wokol
						   wierzcholka R */
                r->l[!d] = p->l[d];             /* nastepne */
                p->l[d] = r;                    /* rotuj w lewo/prawo (a = +1/-1) wokol
						   wierzcholka |S| */
                s->l[d] = p->l[!d];
                p->l[!d] = s;
                s->bal = r->bal = 0;            /* |s->bal|, |r->bal| zaleza od przypadkow: 
				 (|s->bal|,|r->bal|) = $\left\{\matrix{(-a,0) & p->bal = a \hfill \cr
					(0,0) & p->bal = 0 \hfill \cr
					(0,+a) & p->bal = -a\hfill }\right.$ */
                if(p->bal == a)
                        s->bal = -a;
                else if(p->bal == -a)
                        r->bal = a;
        }
        if(head == t)
                (*R) = p;                       /* gdy rotacja zmienila korzen to operuj
						   na korzeniu */
        else
                t->l[s == t->l[1]] = p;         /* wpp popraw wskazanie od ojca P */
        MEMFREE(head);                          /* pozbycie sie tymczasowego |HEAD|-a */
        return u;                               /* zwroc wsk. do dodanego wierzcholka */
}









@* Odpowiedz na query.

Zaklepac LCA.

@<Query@>=
