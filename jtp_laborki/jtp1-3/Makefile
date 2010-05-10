CC	= gcc
CFLAGS	= -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
LDFLAGS	= -O2 -lm
SRC	= zad.c 
PKGNAME	= GadekKonrad-jtp1-3.tgz

clean:
	rm -f *.o zad $(PKGNAME) *~ *swp

zad: zad.c
	$(CC) $(CFLAGS) $(LDFLAGS) zad.c -o zad

pkg: clean $(SRC)
	tar -zcf $(PKGNAME) $(SRC)
