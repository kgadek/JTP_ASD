CC	= gcc
CFLAGS	= -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
LDFLAGS	= -O2 -lm
SRC	= b1.c b2.c b3.c b4.c
PKGNAME	= GadekKonrad-jtp1-2.tgz

clean:
	rm -f *.o b1.o b1 b2.o b2 b3.o b3 b4.o b4 $(PKGNAME) outf *~

b1: b1.c
	$(CC) $(CFLAGS) $(LDFLAGS) b1.c -o b1

b2: b2.c
	$(CC) $(CFLAGS) $(LDFLAGS) b2.c -o b2

b3: b3.c
	$(CC) $(CFLAGS) $(LDFLAGS) b3.c -o b3

b4: b4.c
	$(CC) $(CFLAGS) $(LDFLAGS) b4.c -o b4

pkg: $(SRC)
	rm -f $(PKGNAME)
	tar -zcf $(PKGNAME) $(SRC)
