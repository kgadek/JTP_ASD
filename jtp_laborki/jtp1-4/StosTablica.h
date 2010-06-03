#ifndef _STOS_TABLICA
#define _STOS_TABLICA


class StosTablica {
protected:
	char *ptr;
	unsigned int size;
	unsigned int used;
public:
	StosTablica(unsigned int const _size = 100);
	StosTablica(StosTablica const &);
	virtual ~StosTablica();
	StosTablica& operator=(StosTablica const &);
	virtual void push(char);
	char pop();
	bool empty() const;
	bool full() const;
};


#endif
