#ifndef _STOS_TABLICA
#define _STOS_TABLICA


class StosTablica {
protected:
	char *ptr;		/* wsk. do miejsca w pamieci */
	unsigned int size;	/* maksymalna ilosc elementow */
	unsigned int used;	/* Ilosc elementow na stosie.
				   Zawsze jest spelniona nierownosc:
				   	used <= size */
public:
	StosTablica(unsigned int const _size = 100);
				/* domyslny konstruktor */
	StosTablica(StosTablica const &);
				/* konstruktor kopiujacy */
	virtual ~StosTablica();	/* destruktor */
	StosTablica& operator=(StosTablica const &);
				/* operator przypisania (kopiujacy) */
	virtual void push(char);
				/* wrzucenie na stos */
	char pop();		/* zdjecie ze stosu */
	bool empty() const;	/* stos jest pusty? */
	bool full() const;	/* stos jest pelny? */
};


#endif
