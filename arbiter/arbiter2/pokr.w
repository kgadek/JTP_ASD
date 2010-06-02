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
	/*dbg*/printf("sprawdzam rozmiar drzewa...\n");
	/*dbg*/printf("avl size check: %d\n",avlSizeCheck(avlR));
	while( fgets(input,INPUTLEN,stdin) != NULL ) {	/* fgets i sscanf sa "bezpieczne" */
		@<Wstepnie przetworz tekst@>@;
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
avlNode *avlR = NULL;		/* korzen drzewa AVL */



@ Rozbijanie tekstu w |input| na |X|, |R|, |Y|.

@<Wstepnie przetworz tekst@>=
sscanf(input," %s %s %s %s %s ",X,Xa,R,Y,Ya);
strcat(X," ");	/* polacz X i Xa w jedno */
strcat(X,Xa);
strcat(Y," ");	/* polacz Y i Ya w jedno */
strcat(Y,Ya);



@ Ustawianie pointerow.

@<Zdobadz wskazniki do osob@>=
/*dbg*/printf("#################### %s\n",X);
/*dbg*/printf("sprawdzam rozmiar drzewa...\n");
/*dbg*/printf("avl size check: %d\n",avlSizeCheck(avlR));
xx1 = avlInsert(&avlR,X,calcHash(X))->key;
/*dbg*/assert(strcmp(xx1->X,X)==0);
/*dbg*/assert(xx1->hash == calcHash(X));
/*dbg*/printf("sprawdzam rozmiar drzewa...\n");
/*dbg*/printf("avl size check: %d\n",avlSizeCheck(avlR));
/*dbg*/printf("#################### %s\n",Y);
yy1 = avlInsert(&avlR,Y,calcHash(Y))->key;
/*dbg*/assert(strcmp(yy1->X,Y)==0);
/*dbg*/assert(yy1->hash == calcHash(Y));
/*dbg*/printf("sprawdzam rozmiar drzewa...\n");
/*dbg*/printf("avl size check: %d\n",avlSizeCheck(avlR));
/*dbg*/printf("____________________\n");


@ Kpfp.

@<Definicje funkcji@>=
int avlSizeCheck(avlNode *x) {
	if(!x)
		return 0;
	return 1+avlSizeCheck(x->l[0])+avlSizeCheck(x->l[1]);
}


@ Czyszczenie pamieci.

@<Czyszczenie pamieci@>=
/*dbg*/printf("cleaning\n");
/*dbg*/printf("sprawdzam rozmiar drzewa...\n");
/*dbg*/printf("avl size check: %d\n",avlSizeCheck(avlR));
/*dbg*/printf("clean\n");
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



@ Liczenie hash-a imienia danej osoby.

Znalezione na stronie http://www.cse.yorku.ca/~oz/hash.html.

Algorytm: $hash_i = hash_{i-1}*33 \odot x[i]$ gdzie $\odot$ oznacza XOR.

@<Definicje funkcji@>=
int calcHash(char *x) {
	int ret = 5381;
	while(*x)
		ret = ((ret << 5) + ret) ^ (*(x++));
	return ret;
}






@* Drzewo hashujace.

Drzewo AVL z operacjami |avlNode* Insert(...)| i |avlNode* Query(...)|.

Ustalona kolejnosc wierzcholkow: |x| jest lewym synem |y| $\iff$
|(x->hash < y->hash) || ((x->hash == y->hash) && strcmp(x->X,y->X)<0) |.



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

Czysci tez wskazywany przez |key| obiekt |osoba|. Destruktor |osoba::~osoba| nie powinien
niszczyc powiazanych, gdyz tym zajmuje sie ponizsza procedura.

Nie dziala poprawnie! Wywolanie rekurencyjne wywoluje "Naruszenie ochrony pamieci".

@<Definicje funkcji@>=
void avlFree(avlNode **x) {
        if(!x || !(*x))
                return;
	if((*x)->key) {
		MEMFREE((*x)->key);
		(*x)->key = NULL;
	}
	//avlFree((*x)->l);
	//avlFree((*x)->l+1);
        MEMFREE(*x);
	(*x) = NULL;
}



@ Dodawanie do drzewa.

Algorytm dodawania top-down (dwuprzebiegowy) drzewa AVL.

Przyjmuje opis osoby i, jesli danej osoby nie ma w drzewie, tworzy powiazane obiekty
|avlNode| i |osoba| bedace odpowiednikami podanej osoby.

Zwraca wskaznik do obiektu |avlNode| wskazujacego na podana osobe.

Zwrocic uwage na |strncpy()|!


@<Definicje funkcji@>=
avlNode* avlInsert(avlNode **R, char *k, int hash) {
        avlNode *head, *p, *q, *r, *s, *t, *u;
        int a,d;
        if(*R == NULL) {                                        /* Przypadek specjalny:
								   puste drzewo */
                (*R) = MEMALLOC(avlNode);       /* utworz node */
                avlInit(*R);                    /* zainicjuj */
                (*R)->key = MEMALLOC(osoba);    /* ustaw wartosci */
		a = strlen(k);
		(*R)->key->X = MEMNALLOC(char,a+1);
		strncpy((*R)->key->X,k,a+1);
		(*R)->key->X[a] = '\0';
		(*R)->key->hash = hash;
                return *R;
        }
        u = NULL;                               /* aby sie kompilator nie rzucal */
        head = MEMALLOC(avlNode);               /* utworzenie |HEAD| */
        avlInit(head);
	head->key = MEMALLOC(osoba);
	head->key->X = MEMNALLOC(char,1);
	head->key->X[0]='\0';
        head->l[0] = *R;                                   /* A1. inicjacja */
        t = head;
        q = p = s = *R;
        while(q != NULL) {                                      /* A2. szukanie */
		if(hash == p->key->hash && !strcmp(k,p->key->X)) {
			/*dbg*/printf(">%s<(%d) juz jest\n",k,hash);
			/* znaleziono; jest w drzewie wiec nie dodawaj */
			return p;
		}
		d = !((hash < p->key->hash) || ((hash == p->key->hash) && (strcmp(k,p->key->X) < 0)));
                q = p->l[d];                                    /* A3/A4. przejscie lewo/prawo */
		if(!q) {
		} else if(q->bal != 0) {
		}
                if(q == NULL) {					/* A5. wstawienie */
                        p->l[d] = u = q = MEMALLOC(avlNode);
                        avlInit(q);
			a = strlen(k);
			q->key = MEMALLOC(osoba);
			q->key->X = MEMNALLOC(char,a+1);
			strncpy(q->key->X,k,a+1);
			q->key->X[a] = '\0';
			q->key->hash = hash;
                        break;
                } else if(q->bal != 0) {
                        t = p;
                        s = q;
                }
                p = q;
        }
								/* A6. poprawa wartosci balansow */
        r = p = s->l[ !((hash < s->key->hash) ||
			((hash == s->key->hash) && (strcmp(k,s->key->X) < 0))) ];
        while(p!=q) {                           /* $\forall p^\prime:$ $p^\prime$
						   jest miedzy |p| a |q| (poza |q|) */
						/*      wybierz kierunek */
		d = !((hash < p->key->hash) || ((hash == p->key->hash) && (strcmp(k,p->key->X) < 0)));
                p->bal = 2*d - 1;               /*      popraw balans */
                p = p->l[d];                    /*      przejdz dalej */
        }
        q = s;                                  /* zapamietaj s (to bedzie nowy rodzic rotowanego
						   poddrzewa) */
        		                                /* A7. ustawienie balansu drzewa */
	a = (!((hash < p->key->hash) || ((hash == p->key->hash) && (strcmp(k,p->key->X) < 0))))?+1:-1;
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
