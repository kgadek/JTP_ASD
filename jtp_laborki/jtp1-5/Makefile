CXX	= g++
CXXFLAGS = -W -Wall -Wshadow -Wformat -Wsequence-point -Wunused\
		-Wuninitialized -Wfloat-equal -ansi -pedantic
LDFLAGS	= -O2 -lm
SRC	= Makefile Doxyfile common.h lista.h stos.h tests.cpp\
	  doc README
PKGNAME	= GadekKonrad-jtp1-5.tgz

.PHONY: clean all pkg program punkty

clean:
	rm -f *.o tests $(PKGNAME) *~ *swp

all: tests
	doxygen

pkg: clean 
	tar -zcf $(PKGNAME) $(SRC)

# Kompilacja programu testujacego
tests: tests.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@

