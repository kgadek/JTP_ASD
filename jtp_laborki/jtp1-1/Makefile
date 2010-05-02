CC	= gcc
CFLAGS	= -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
LDFLAGS	= -O2 -lm
SRC	= b1.c b2.c b3.c
PKGNAME	= GadekKonrad-jtp1-1.tgz

clean:
	rm -f *.o b1.o b1 b2.o b2 b3.o b3 $(PKGNAME) *~

b1: b1.c
	$(CC) $(CFLAGS) $(LDFLAGS) b1.c -o b1

b2: b2.c
	$(CC) $(CFLAGS) $(LDFLAGS) b2.c -o b2

b3: b3.c
	$(CC) $(CFLAGS) $(LDFLAGS) b3.c -o b3

pkg: $(SRC)
	rm -f $(PKGNAME)
	tar -zcvf $(PKGNAME) $(SRC)
