\def\cee/{C}
\def\cpp/{\cee/{\tt++}}


@* Rdzen programu.

Zadaniem |maina| jest wczytanie danych wejsciowych i wywolywanie odpowiednich instrukcji
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
	while( fgets(input,INPUTLEN,stdin) != NULL ) {	/* fgets i sscanf sa "bezpieczne" */
		@<Wstepnie przetworz tekst@>@;
		if( strcmp(R,":") ) {
			@<Query@>@;
		} else {
		}
	}
	return 0;
}




@ Zmienne globalne.

Zmienna '|input|' (o dlugosci |INPUTLEN|) przechwytuje caly napis wejsciowy. Ten nastepnie jest
rozbijany na |X| (imie i nazwisko osoby X), |R| (relacja miedzy X a Y) oraz |Y|
(imie i nazwisko osoby Y). Po przetworzeniu do |X| trafia polaczone imie i nazwisko
(analogicznie |Y|).

@<Zmienne globalne@>=
char input[INPUTLEN], X[INPUTLEN], Xa[INPUTLEN], R[INPUTLEN], Y[INPUTLEN], Ya[INPUTLEN];




@ Rozbijanie tekstu w |input| na |X|, |R|, |Y|.

@<Wstepnie przetworz tekst@>=
sscanf(" %s %s %s %s %s ",X,Xa,R,Y,Ya);
strcat(X," ");	/* polacz X i Xa w jedno */
strcat(X,Xa);
strcat(Y," ");	/* polacz Y i Ya w jedno */
strcat(Y,Ya);




@* Klasa |osoba|.

Przechowuje imie i nazwisko oraz wskazniki do ojca i synow.

@<Definicje struktur@>=
class osoba {
public:
	char *X;		/* imie i nazwiski */
	int hash;		/* hash */
	osoba *p, *l, *r;	/* odpowiednio: parent, lewy, prawy */
	~osoba() {
		if(X != NULL) free(X);
	}
};



@ Porownywanie osob.

|osobaCmp(x,y)| =
$\left\{\matrix{-1\hfill&x>y\hfill\cr0\hfill&x=y\hfill\cr+1\hfill&x<y\hfill}\right.$


Priorytetem jest porownanie |hash|-y, porownanie stringow
(|strcmp(x->X,y->X)|) tylko w wypadku kolizji.

@<Definicje funkcji@>=
int osobaCmp(osoba *x, osoba *y) {
	int v;
	if(x->hash != y->hash)
		return y->hash - x->hash;
	v = strcmp(x->X,y->X);
	if(!v)
		return v;
	return v>0?-1:1;
}






@* Drzewo hashujace.

Drzewo AVL z operacjami |avlNode* Insert(...)| i |avlNode* Query(...)|.



@ Liczenie hash-a osoby.

@<Definicje funkcji@>=
int hashOsoba(osoba *x) {
	return 0;
}



@ Struktura drzewa.

Trzyma wskaznik do struktury |osoba|. Zawiera tez |int hash| imienia i nazwiska
(szybsze szukanie).

@<Definicje struktur@>=
struct avlNode {
        osoba *key;                     /* klucz w węźle */
        int bal;                        /* wartosc balansu (potrzebne 3B) */
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

Czysci tez wszystkie wskazywane obiekty |osoba|.

@<Definicje funkcji@>=
void avlFree(avlNode *x) {
        if(x==NULL)
                return;
        avlFree(x->l[0]);
        avlFree(x->l[1]);
	MEMFREE(x->key);
        MEMFREE(x);
}



@ Szukanie w drzewie.

@<Definicje funkcji@>=
avlNode* avlQuery(avlNode *R, osoba *k) {
        while(R && osobaCmp(R->key,k))
                R = R->l[OSOBA_GT(k,R->key)];
        return R;
}



@ Dodawanie do drzewa.

Algorytm top-down (dwuprzebiegowy) na drzewie AVL.
Dodaje |avlNode| wskazujacy na obiekt typu |osoba| do drzewa o ile wczesniej juz
tam nie wystepowal.
Zwraca wskaznik na obiekt |avlNode| (niezaleznie czy dodany teraz czy kiedys indziej).
Zaklada, ze dodawany obiekt ma juz policzony |hash|.


@d MEMALLOC(type) ((type*)malloc(sizeof(type)))
@d MEMFREE(obj) free(obj)
@d OSOBA_GT(x,y) (osobaCmp((x),(y))<0?1:0)
@d OSOBA_LT(x,y) (osobaCmp((x),(y))>0?1:0)
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
                d = (k > p->key);
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
        r = p = s->l[ OSOBA_GT(k,s->key) ];                     /* A6. poprawa wartosci balansow */
        while(p!=q) {                           /* kazdy wierzcholek miedzy |P| a |Q| (poza |Q|) */
                d = OSOBA_GT(k,p->key);         /*      wybierz kierunek */
                p->bal = 2*d - 1;               /*      popraw balans */
                p = p->l[d];                    /*      przejdz dalej */
        }
        q = s;                                  /* zapamietaj s (to bedzie nowy rodzic rotowanego
						   poddrzewa) */
        a = OSOBA_LT(k,s->key)?-1:1;                           /* A7. ustawienie balansu drzewa */
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
